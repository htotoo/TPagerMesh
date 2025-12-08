#include "keypad_irq.hpp"
#include "esp_log.h"

static const char* TAG = "Keypad";

// Static Member Init
lv_indev_t* KeypadDriver::indev_keypad = nullptr;
SemaphoreHandle_t KeypadDriver::irq_sem = NULL;
QueueHandle_t KeypadDriver::key_queue = NULL;
uint8_t KeypadDriver::key_stage = 0;
uint32_t KeypadDriver::current_held_key = 0;
uint32_t KeypadDriver::last_sent_key = 0;

// Registers
#define REG_CFG 0x01
#define REG_INT_STAT 0x02
#define REG_KEY_EVENT_A 0x04
#define REG_KP_GPIO1 0x1D
#define REG_KP_GPIO2 0x1E
#define REG_KP_GPIO3 0x1F

// Hardware IDs
#define ID_FN 21
#define ID_Z 22
#define ID_SHIFT 29
#define ID_BACKSPACE 30
#define ID_SPACE 31

// LVGL Keys
#define KEY_SELECT LV_KEY_ENTER
#define KEY_TAB LV_KEY_NEXT
#define KEY_BSP LV_KEY_BACKSPACE
#define KEY_ESC LV_KEY_ESC
#define KEY_BL 0

// --- 3-Stage Map ---
static const uint32_t TLoraPagerTapMap[KEYMAP_ROWS][3] = {
    // Row 1
    {'q', 'Q', '1'},  // 0
    {'w', 'W', '2'},  // 1
    {'e', 'E', '3'},
    {'r', 'R', '4'},
    {'t', 'T', '5'},
    {'y', 'Y', '6'},
    {'u', 'U', '7'},
    {'i', 'I', '8'},
    {'o', 'O', '9'},
    {'p', 'P', '0'},  // 9

    // Row 2
    {'a', 'A', '*'},  // 10
    {'s', 'S', '/'},
    {'d', 'D', '+'},
    {'f', 'F', '-'},
    {'g', 'G', '='},
    {'h', 'H', ':'},
    {'j', 'J', '\''},
    {'k', 'K', '"'},
    {'l', 'L', '@'},                    // 18
    {KEY_SELECT, KEY_SELECT, KEY_TAB},  // 19 (Enter)

    // Gap / FN
    {0, 0, 0},  // 20

    // Row 3
    {'z', 'Z', '_'},  // 21 (Mapped from ID 22)
    {'x', 'X', '$'},
    {'c', 'C', ';'},
    {'v', 'V', '?'},
    {'b', 'B', '!'},
    {'n', 'N', ','},
    {'m', 'M', '.'},  // 27

    // Gap
    {0, 0, 0},  // 28
    {0, 0, 0},  // 29 (Shift Placeholder)

    // Bottom
    {KEY_BSP, KEY_BSP, KEY_ESC},  // 30
    {' ', ' ', KEY_BL}            // 31
};

void IRAM_ATTR KeypadDriver::isr_handler(void* arg) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(irq_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
}

void KeypadDriver::begin() {
    ESP_LOGI(TAG, "Starting Keypad Init...");
    irq_sem = xSemaphoreCreateBinary();
    key_queue = xQueueCreate(20, sizeof(uint32_t));

    // 1. Configure Chip
    // Enable Matrix (All Rows/Cols)
    write_byte(REG_KP_GPIO1, 0xFF);
    write_byte(REG_KP_GPIO2, 0xFF);
    write_byte(REG_KP_GPIO3, 0x03);

    // Enable Interrupts
    uint8_t cfg = read_byte(REG_CFG);
    write_byte(REG_CFG, cfg | 0x01);

    // Drain Stuck Events
    ESP_LOGI(TAG, "Draining existing events...");
    uint8_t event;
    int safety = 0;
    do {
        event = read_byte(REG_KEY_EVENT_A);
        safety++;
    } while (event != 0 && safety < 20);
    write_byte(REG_INT_STAT, 0xFF);

    // 2. Configure GPIO
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL << KEYPAD_IRQ_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(KEYPAD_IRQ_PIN, isr_handler, NULL);

    xTaskCreate(handle_interrupt_task, "keypad_task", 4096, NULL, 10, NULL);

    ESP_LOGI(TAG, "Keypad Ready.");
}

void KeypadDriver::handle_interrupt_task(void* arg) {
    while (1) {
        // FIX 1: Add a timeout (50ms). If IRQ line gets stuck LOW, we wake up and check anyway.
        // This prevents the "stuck keyboard" issue if an edge is missed.
        bool taken = xSemaphoreTake(irq_sem, pdMS_TO_TICKS(50));

        // Check Pin State: If Semaphore taken OR Pin is physically LOW (Active)
        if (taken || gpio_get_level(KEYPAD_IRQ_PIN) == 0) {
            // Loop until the INT_STAT register says we are clean
            while (true) {
                uint8_t status = read_byte(REG_INT_STAT);

                // If Key Event (Bit 0) is NOT set, we are done draining
                if ((status & 0x01) == 0) {
                    break;
                }

                // Drain FIFO completely
                while (true) {
                    uint8_t key_event = read_byte(REG_KEY_EVENT_A);
                    if (key_event == 0) break;  // FIFO Empty

                    bool is_press = (key_event & 0x80) != 0;
                    uint8_t key_id = key_event & 0x7F;

                    if (is_press) {
                        // Only map and queue on PRESS
                        uint32_t key_code = map_key(key_id);
                        if (key_code != 0) {
                            xQueueSend(key_queue, &key_code, 0);
                            ESP_LOGI(TAG, "PRESS: %d", key_id);
                        }
                        current_held_key = key_code;
                    } else {
                        // FIX 2: Do NOT call map_key on release (prevents side effects like double-shift)
                        // Just clear the hold state
                        current_held_key = 0;
                    }
                }

                // Ack Interrupt (Write 1 to clear)
                write_byte(REG_INT_STAT, 0x01);
            }
        }
    }
}

// Map Hardware ID -> Array Index
int KeypadDriver::get_key_index(uint8_t key_id) {
    if (key_id >= 1 && key_id <= 10) return key_id - 1;
    if (key_id >= 11 && key_id <= 19) return key_id - 1;
    if (key_id == 20) return 19;
    if (key_id >= 22 && key_id <= 28) return key_id - 1;
    if (key_id == ID_BACKSPACE) return 30;
    if (key_id == ID_SPACE) return 31;
    return -1;
}

uint32_t KeypadDriver::map_key(uint8_t key_id) {
    // 1. Group Switcher (FN Key - ID 21)
    if (key_id == ID_FN) {
        return LV_KEY_NEXT;  // Tab to switch groups
    }

    // 2. Mode Switcher (SHIFT Key - ID 29)
    if (key_id == ID_SHIFT) {
        key_stage = (key_stage + 1) % 3;
        ESP_LOGI(TAG, "Mode: %d", key_stage);
        return 0;  // State change only
    }

    // 3. Standard Map
    int idx = get_key_index(key_id);
    if (idx < 0 || idx >= KEYMAP_ROWS) return 0;

    uint32_t code = TLoraPagerTapMap[idx][key_stage];

    // Fallback
    if (code == 0 && key_stage != 0) {
        code = TLoraPagerTapMap[idx][0];
    }
    return code;
}

void KeypadDriver::read_cb(lv_indev_t* indev, lv_indev_data_t* data) {
    uint32_t key_out;

    // 1. Check Queue
    if (xQueueReceive(key_queue, &key_out, 0) == pdTRUE) {
        // Intercept Tab/Next here if you want to handle it manually in main
        // But for now we send it to LVGL so it triggers the event listener

        data->state = LV_INDEV_STATE_PRESSED;
        data->key = key_out;
        last_sent_key = key_out;
        data->continue_reading = (uxQueueMessagesWaiting(key_queue) > 0);
    }
    // 2. Held State (Only if queue is empty)
    else if (current_held_key != 0 && current_held_key == last_sent_key) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = last_sent_key;
        data->continue_reading = false;
    }
    // 3. Release
    else {
        data->state = LV_INDEV_STATE_RELEASED;
        data->continue_reading = false;
    }
}

void KeypadDriver::write_byte(uint8_t reg, uint8_t val) {
    uint8_t data[] = {reg, val};
    i2c_master_write_to_device(I2C_PORT, TCA8418_ADDR, data, 2, pdMS_TO_TICKS(50));
}

uint8_t KeypadDriver::read_byte(uint8_t reg) {
    uint8_t val = 0;
    i2c_master_write_read_device(I2C_PORT, TCA8418_ADDR, &reg, 1, &val, 1, pdMS_TO_TICKS(50));
    return val;
}

void KeypadDriver::register_lvgl() {
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, read_cb);

    // Configure Long Press (1.5 Seconds)
    lv_indev_set_long_press_time(indev_keypad, 1500);
}