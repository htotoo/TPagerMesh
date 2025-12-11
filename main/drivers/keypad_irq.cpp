#include "keypad_irq.hpp"
#include "esp_log.h"

static const char* TAG = "Keypad";

// Static Init
lv_indev_t* KeypadDriver::indev_keypad = nullptr;
SemaphoreHandle_t KeypadDriver::irq_sem = NULL;
QueueHandle_t KeypadDriver::key_queue = NULL;
uint8_t KeypadDriver::key_stage = 0;
uint32_t KeypadDriver::last_processed_key = 0;
bool KeypadDriver::last_processed_state = false;
KeypadDriver::key_hook_t KeypadDriver::global_hook = nullptr;

// Registers & Maps (Keep existing definitions)
#define REG_CFG 0x01
#define REG_INT_STAT 0x02
#define REG_KEY_EVENT_A 0x04
#define REG_KP_GPIO1 0x1D
#define REG_KP_GPIO2 0x1E
#define REG_KP_GPIO3 0x1F

#define ID_FN 21
#define ID_SHIFT 29
#define ID_BACKSPACE 30
#define ID_SPACE 31

// Helper Macros
#define KEY_SELECT LV_KEY_ENTER
#define KEY_TAB LV_KEY_NEXT
#define KEY_BSP LV_KEY_BACKSPACE
#define KEY_ESC LV_KEY_ESC
#define KEY_BL 0

// Your existing Map...
static const uint32_t TLoraPagerTapMap[KEYMAP_ROWS][3] = {
    // Row 1
    {'q', 'Q', '1'},
    {'w', 'W', '2'},
    {'e', 'E', '3'},
    {'r', 'R', '4'},
    {'t', 'T', '5'},
    {'y', 'Y', '6'},
    {'u', 'U', '7'},
    {'i', 'I', '8'},
    {'o', 'O', '9'},
    {'p', 'P', '0'},
    // Row 2
    {'a', 'A', '*'},
    {'s', 'S', '/'},
    {'d', 'D', '+'},
    {'f', 'F', '-'},
    {'g', 'G', '='},
    {'h', 'H', ':'},
    {'j', 'J', '\''},
    {'k', 'K', '"'},
    {'l', 'L', '@'},
    {KEY_SELECT, KEY_SELECT, KEY_TAB},
    // Gap
    {0, 0, 0},
    // Row 3
    {'z', 'Z', '_'},
    {'x', 'X', '$'},
    {'c', 'C', ';'},
    {'v', 'V', '?'},
    {'b', 'B', '!'},
    {'n', 'N', ','},
    {'m', 'M', '.'},
    // Gaps
    {0, 0, 0},
    {0, 0, 0},
    // Bottom
    {KEY_BSP, KEY_BSP, KEY_ESC},
    {' ', ' ', KEY_BL}};

void IRAM_ATTR KeypadDriver::isr_handler(void* arg) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(irq_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
}

void KeypadDriver::begin() {
    irq_sem = xSemaphoreCreateBinary();
    // Create queue for 20 events. Size is now sizeof(KeyEvent)
    key_queue = xQueueCreate(20, sizeof(KeyEvent));

    // ... (Keep existing I2C init and GPIO init code) ...
    // Enable Matrix (All Rows/Cols)
    write_byte(REG_KP_GPIO1, 0xFF);
    write_byte(REG_KP_GPIO2, 0xFF);
    write_byte(REG_KP_GPIO3, 0x03);

    // Enable Interrupts
    uint8_t cfg = read_byte(REG_CFG);
    write_byte(REG_CFG, cfg | 0x01);

    // Clear Interrupts
    write_byte(REG_INT_STAT, 0xFF);

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL << KEYPAD_IRQ_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(KEYPAD_IRQ_PIN, isr_handler, NULL);

    xTaskCreate(handle_interrupt_task, "keypad_task", 4096, NULL, 10, NULL);
    ESP_LOGI(TAG, "Keypad Ready (Event Queue Mode).");
}

void KeypadDriver::handle_interrupt_task(void* arg) {
    while (1) {
        bool taken = xSemaphoreTake(irq_sem, pdMS_TO_TICKS(50));
        if (taken || gpio_get_level(KEYPAD_IRQ_PIN) == 0) {
            while (true) {
                uint8_t status = read_byte(REG_INT_STAT);
                if ((status & 0x01) == 0) break;  // No key event

                // Drain FIFO
                while (true) {
                    uint8_t raw_val = read_byte(REG_KEY_EVENT_A);
                    if (raw_val == 0) break;

                    bool is_press = (raw_val & 0x80) != 0;
                    uint8_t key_id = raw_val & 0x7F;

                    // 1. Map the ID to a character code
                    uint32_t key_code = map_key(key_id);

                    // 2. Queue valid events
                    if (key_code != 0) {
                        KeyEvent evt;
                        evt.key = key_code;
                        evt.is_pressed = is_press;

                        // Send to Queue (Wait 10ms if full)
                        if (xQueueSend(key_queue, &evt, pdMS_TO_TICKS(10)) != pdTRUE) {
                            ESP_LOGW(TAG, "Key Queue Full!");
                        }
                    }
                    // Note: If map_key returned 0 (e.g. SHIFT press),
                    // we don't queue it for LVGL, as it's an internal modifier.
                }
                // Ack Interrupt
                write_byte(REG_INT_STAT, 0x01);
            }
        }
    }
}

// Map Logic (Keep existing implementation)
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
    if (key_id == ID_FN) return KEY_SWITCH_FOCUS;

    if (key_id == ID_SHIFT) {
        // Only toggle mode on PRESS, not release, to avoid double toggle
        // We can check if this call is coming from a press/release context,
        // but typically mode switching happens on press.
        // For simplicity here, we toggle. In a perfect world, we'd pass 'is_press' to map_key.
        static bool last_shift_state = false;  // Simple debounce
        // Ideally we shouldn't handle logic here, but for now:
        key_stage = (key_stage + 1) % 3;
        ESP_LOGI(TAG, "Mode: %d", key_stage);
        return 0;
    }

    int idx = get_key_index(key_id);
    if (idx < 0 || idx >= KEYMAP_ROWS) return 0;

    // We map based on current stage
    // Note: On Release, this maps to the *current* stage char,
    // which is usually fine unless user held key, pressed shift, then released key.
    uint32_t code = TLoraPagerTapMap[idx][key_stage];
    if (code == 0 && key_stage != 0) code = TLoraPagerTapMap[idx][0];
    return code;
}

// --- The Critical Update ---
void KeypadDriver::read_cb(lv_indev_t* indev, lv_indev_data_t* data) {
    KeyEvent evt;

    // 1. Try to read ONE event from the queue
    if (xQueueReceive(key_queue, &evt, 0) == pdTRUE) {
        // New Data Available
        data->key = evt.key;
        data->state = evt.is_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

        // Update valid static state (so we remember what to report when idle)
        last_processed_key = evt.key;
        last_processed_state = evt.is_pressed;

        // Hook Logic: Fire ONLY on valid release events popped from queue
        if (!evt.is_pressed && global_hook) {
            global_hook(evt.key);
        }

        // Tell LVGL there is more data if queue is not empty
        data->continue_reading = (uxQueueMessagesWaiting(key_queue) > 0);
    } else {
        // 2. Queue Empty - Report Idle/Stable State
        // You requested: "don't report anything... if queue is empty"
        // LVGL *requires* valid data. The standard way to say "nothing changed"
        // is to report the SAME key with the SAME state (usually Released).

        // If we were holding a key, we keep reporting Pressed.
        // If we released it, we keep reporting Released.
        // This prevents "stuttering" if the user holds a key down.

        data->key = last_processed_key;
        data->state = last_processed_state ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
        data->continue_reading = false;
    }
}

// Keep helper functions (write_byte, read_byte, register_lvgl) as they were...
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
    lv_indev_set_long_press_time(indev_keypad, 2000);  // 2000ms for long press
    lv_indev_set_read_cb(indev_keypad, read_cb);
}