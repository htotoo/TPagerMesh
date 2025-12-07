#include "keypad_irq.hpp"
#include "esp_log.h"

static const char* TAG = "KeypadDebug";

lv_indev_t* KeypadDriver::indev_keypad = nullptr;
SemaphoreHandle_t KeypadDriver::irq_sem = NULL;
QueueHandle_t KeypadDriver::key_queue = NULL;

// Registers
#define REG_CFG 0x01
#define REG_INT_STAT 0x02
#define REG_KEY_LCK_EC 0x03
#define REG_KEY_EVENT_A 0x04
#define REG_KP_GPIO1 0x1D
#define REG_KP_GPIO2 0x1E
#define REG_KP_GPIO3 0x1F

// ISR: Keep minimal
void IRAM_ATTR KeypadDriver::isr_handler(void* arg) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(irq_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
}

void KeypadDriver::begin() {
    ESP_LOGI(TAG, "Starting Keypad Init...");

    // 1. Verify I2C Connection
    scan_i2c_bus();

    // 2. Create OS resources
    irq_sem = xSemaphoreCreateBinary();
    key_queue = xQueueCreate(20, sizeof(uint32_t));

    // 3. Configure Chip Registers FIRST
    // (We do this before GPIO init to ensure the line is High)

    // Enable Matrix
    write_byte(REG_KP_GPIO1, 0xFF);
    write_byte(REG_KP_GPIO2, 0xFF);
    write_byte(REG_KP_GPIO3, 0x03);

    // Enable Interrupts
    uint8_t cfg = read_byte(REG_CFG);
    write_byte(REG_CFG, cfg | 0x01);

    // --- CRITICAL FIX: DRAIN THE SWAMP ---
    // Read events until the chip returns 0. This empties the FIFO.
    ESP_LOGW(TAG, "Draining stuck events...");
    uint8_t event;
    int safety = 0;
    do {
        event = read_byte(REG_KEY_EVENT_A);
        if (event != 0) {
            ESP_LOGW(TAG, " -> Drained stuck event: 0x%02X", event);
        }
        safety++;
    } while (event != 0 && safety < 20);

    // Clear Interrupt Flag explicitly
    write_byte(REG_INT_STAT, 0xFF);
    // -------------------------------------

    // 4. Configure GPIO
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL << KEYPAD_IRQ_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    // 5. CHECK PIN STATE
    // The pin MUST be 1 (High) now. If it is 0, the wiring is wrong or chip is still stuck.
    int pin_state = gpio_get_level(KEYPAD_IRQ_PIN);
    if (pin_state == 0) {
        ESP_LOGE(TAG, "CRITICAL ERROR: IRQ Pin is LOW! Interrupts will not work.");
        ESP_LOGE(TAG, "1. Check wiring (Is it really GPIO %d?)", KEYPAD_IRQ_PIN);
        ESP_LOGE(TAG, "2. Check INT_STAT again: 0x%02X", read_byte(REG_INT_STAT));
    } else {
        ESP_LOGI(TAG, "IRQ Pin state is HIGH (Good). Ready for trigger.");
    }

    gpio_install_isr_service(0);
    gpio_isr_handler_add(KEYPAD_IRQ_PIN, isr_handler, NULL);

    xTaskCreate(handle_interrupt_task, "keypad_task", 4096, NULL, 10, NULL);

    // Register LVGL
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, read_cb);

    ESP_LOGI(TAG, "Keypad Init Done.");
}

void KeypadDriver::scan_i2c_bus() {
    ESP_LOGI(TAG, "Scanning I2C Bus for Keypad (0x34)...");
    uint8_t dummy;
    esp_err_t err = i2c_master_write_read_device(I2C_PORT, TCA8418_ADDR, &dummy, 0, &dummy, 0, pdMS_TO_TICKS(50));
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "SUCCESS: Device found at 0x34!");
    } else {
        ESP_LOGE(TAG, "FAILURE: No device at 0x34. Check wiring/power! Err: %s", esp_err_to_name(err));
        // Scan full bus to help user find it
        for (int i = 1; i < 127; i++) {
            if (i2c_master_write_read_device(I2C_PORT, i, &dummy, 0, &dummy, 0, pdMS_TO_TICKS(10)) == ESP_OK) {
                ESP_LOGW(TAG, "Found unknown device at 0x%02X", i);
            }
        }
    }
}

void KeypadDriver::dump_registers() {
    ESP_LOGI(TAG, "--- Register Dump ---");
    ESP_LOGI(TAG, "CFG (0x01): 0x%02X", read_byte(REG_CFG));
    ESP_LOGI(TAG, "INT_STAT (0x02): 0x%02X", read_byte(REG_INT_STAT));
    ESP_LOGI(TAG, "KEY_EVENT_A (0x04): 0x%02X", read_byte(REG_KEY_EVENT_A));
    ESP_LOGI(TAG, "GPIO_DAT_STAT1 (0x11): 0x%02X", read_byte(0x11));  // Check if any key is physically stuck
}

void KeypadDriver::handle_interrupt_task(void* arg) {
    while (1) {
        if (xSemaphoreTake(irq_sem, portMAX_DELAY)) {
            // Log that ISR happened
            ESP_LOGI(TAG, "IRQ Triggered! Reading status...");

            uint8_t status = read_byte(REG_INT_STAT);
            ESP_LOGI(TAG, "INT_STAT: 0x%02X", status);

            if (status & 0x01) {  // Key Event
                uint8_t key_event = read_byte(REG_KEY_EVENT_A);
                int safety_limit = 20;  // Prevent infinite loops

                while (key_event != 0 && safety_limit-- > 0) {
                    bool is_press = (key_event & 0x80) == 0;
                    uint8_t key_id = key_event & 0x7F;

                    ESP_LOGI(TAG, "Event: ID=%d, Press=%d", key_id, is_press);

                    if (is_press) {
                        uint32_t key_code = map_key(key_id);
                        if (key_code != 0) {
                            xQueueSend(key_queue, &key_code, 0);
                            ESP_LOGI(TAG, " -> Mapped to: '%c' (%d)", (char)key_code, (int)key_code);
                        } else {
                            ESP_LOGW(TAG, " -> UNMAPPED KEY ID: %d", key_id);
                        }
                    }
                    key_event = read_byte(REG_KEY_EVENT_A);
                }

                // Clear Interrupt
                write_byte(REG_INT_STAT, 0xFF);  // Write 1s to clear all flags
                ESP_LOGI(TAG, "Interrupt Cleared. INT Pin should go HIGH.");
            } else {
                ESP_LOGW(TAG, "IRQ fired but INT_STAT bit 0 was not set!");
                // Clear anyway to be safe
                write_byte(REG_INT_STAT, 0xFF);
            }
        }
    }
}

void KeypadDriver::read_cb(lv_indev_t* indev, lv_indev_data_t* data) {
    uint32_t key_out;
    if (xQueueReceive(key_queue, &key_out, 0) == pdTRUE) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = key_out;
        if (uxQueueMessagesWaiting(key_queue) > 0) {
            data->continue_reading = true;
        } else {
            data->continue_reading = false;
        }
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
        data->continue_reading = false;
    }
}

// Low-level with Error Checking
void KeypadDriver::write_byte(uint8_t reg, uint8_t val) {
    uint8_t data[] = {reg, val};
    esp_err_t err = i2c_master_write_to_device(I2C_PORT, TCA8418_ADDR, data, 2, pdMS_TO_TICKS(50));
    if (err != ESP_OK) ESP_LOGE(TAG, "I2C Write Failed (Reg 0x%02X): %s", reg, esp_err_to_name(err));
}

uint8_t KeypadDriver::read_byte(uint8_t reg) {
    uint8_t val = 0;
    esp_err_t err = i2c_master_write_read_device(I2C_PORT, TCA8418_ADDR, &reg, 1, &val, 1, pdMS_TO_TICKS(50));
    if (err != ESP_OK) ESP_LOGE(TAG, "I2C Read Failed (Reg 0x%02X): %s", reg, esp_err_to_name(err));
    return val;
}

uint32_t KeypadDriver::map_key(uint8_t key_id) {
    // Basic Map - Monitor logs to find your specific IDs
    switch (key_id) {
        case 50:
            return LV_KEY_ENTER;
        case 1:
            return 'q';
        case 11:
            return 'w';
        case 21:
            return 'e';
        default:
            return 0;
    }
}