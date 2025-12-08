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
        if (event != 0) ESP_LOGI(TAG, " -> Drained: %d", event);
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

    // DEBUG: Check if pin is HIGH (Ready) or LOW (Stuck)
    int pin_state = gpio_get_level(KEYPAD_IRQ_PIN);
    ESP_LOGI(TAG, "IRQ Pin Initial State: %d (Should be 1)", pin_state);
    if (pin_state == 0) {
        ESP_LOGE(TAG, "WARNING: IRQ Pin is LOW! Interrupts may fail. Check INT_STAT: 0x%02X", read_byte(REG_INT_STAT));
    }

    gpio_install_isr_service(0);
    gpio_isr_handler_add(KEYPAD_IRQ_PIN, isr_handler, NULL);

    xTaskCreate(handle_interrupt_task, "keypad_task", 4096, NULL, 10, NULL);

    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, read_cb);

    // Configure Long Press (1.5 Seconds)
    lv_indev_set_long_press_time(indev_keypad, 1500);

    ESP_LOGI(TAG, "Keypad Ready.");
}

void KeypadDriver::handle_interrupt_task(void* arg) {
    while (1) {
        if (xSemaphoreTake(irq_sem, portMAX_DELAY)) {
            // ESP_LOGI(TAG, "IRQ Fired"); // Uncomment if you suspect ISR isn't running

            uint8_t status = read_byte(REG_INT_STAT);
            if (status & 0x01) {
                uint8_t key_event = read_byte(REG_KEY_EVENT_A);

                while (key_event != 0) {
                    // Logic: Bit 7 is 1 for PRESS
                    bool is_press = (key_event & 0x80) != 0;
                    uint8_t key_id = key_event & 0x7F;

                    if (is_press) {
                        uint32_t key_code = map_key(key_id);

                        // Action 1: Queue for Typing
                        if (key_code != 0) {
                            xQueueSend(key_queue, &key_code, 0);
                            ESP_LOGI(TAG, "PRESS: '%c' (ID=%d)", (char)key_code, key_id);
                        } else {
                            // If key_code is 0 (e.g. FN/Shift), we still log it
                            ESP_LOGI(TAG, "MODIFIER/UNMAPPED (ID=%d)", key_id);
                        }

                        // Action 2: Track "Held" state for Long Press
                        current_held_key = key_code;

                    } else {
                        // Key Released
                        ESP_LOGI(TAG, "RELEASE (ID=%d)", key_id);
                        if (current_held_key != 0) {  // Only clear if we were tracking something
                            current_held_key = 0;
                        }
                    }

                    // Read next event
                    key_event = read_byte(REG_KEY_EVENT_A);
                }
                write_byte(REG_INT_STAT, 0xFF);
            }
        }
    }
}

// Map Hardware ID -> Array Index
int KeypadDriver::get_key_index(uint8_t key_id) {
    // Row 1: Q(1) .. P(10)
    if (key_id >= 1 && key_id <= 10) return key_id - 1;

    // Row 2: A(11) .. L(19)
    if (key_id >= 11 && key_id <= 19) return key_id - 1;

    // Enter (20)
    if (key_id == 20) return 19;

    // Row 3: User Map (Z=22... M=28)
    if (key_id >= 22 && key_id <= 28) return key_id - 1;  // Maps 22->21 (Z)

    // Special
    if (key_id == ID_BACKSPACE) return 30;  // BSP
    if (key_id == ID_SPACE) return 31;      // Space

    return -1;
}

uint32_t KeypadDriver::map_key(uint8_t key_id) {
    // 1. Modifiers
    if (key_id == ID_SHIFT) {
        // Toggle Lower(0) <-> Upper(1)
        if (key_stage == 1)
            key_stage = 0;
        else
            key_stage = 1;
        ESP_LOGI(TAG, "Stage Changed: %s", key_stage ? "UPPER" : "lower");
        return 0;
    }

    if (key_id == ID_FN) {
        // Toggle Num(2) <-> Lower(0)
        if (key_stage == 2)
            key_stage = 0;
        else
            key_stage = 2;
        ESP_LOGI(TAG, "Stage Changed: %s", (key_stage == 2) ? "NUMERIC" : "lower");
        return 0;
    }

    // 2. Standard Map
    int idx = get_key_index(key_id);
    if (idx < 0 || idx >= KEYMAP_ROWS) return 0;

    uint32_t code = TLoraPagerTapMap[idx][key_stage];

    // Fallback to lowercase if current stage is empty
    if (code == 0 && key_stage != 0) {
        code = TLoraPagerTapMap[idx][0];
    }
    return code;
}

void KeypadDriver::read_cb(lv_indev_t* indev, lv_indev_data_t* data) {
    uint32_t key_out;

    // 1. Check Queue (Fast Typing)
    if (xQueueReceive(key_queue, &key_out, 0) == pdTRUE) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = key_out;
        last_sent_key = key_out;

        // If queue has more, read again immediately
        if (uxQueueMessagesWaiting(key_queue) > 0) {
            data->continue_reading = true;
        } else {
            data->continue_reading = false;
        }
    }
    // 2. Check Held State (Long Press Logic)
    else if (current_held_key != 0 && current_held_key == last_sent_key) {
        // User is holding the key. Keep reporting PRESSED.
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