#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "lvgl.h"

// --- Configuration ---
#define TCA8418_ADDR 0x34
#define I2C_PORT I2C_NUM_0
#define KEYPAD_IRQ_PIN GPIO_NUM_6  // User confirmed GPIO 6

class KeypadDriver {
   public:
    void begin();
    static void read_cb(lv_indev_t* indev, lv_indev_data_t* data);
    static lv_indev_t* get_indev() { return indev_keypad; }

   private:
    static void IRAM_ATTR isr_handler(void* arg);
    static void handle_interrupt_task(void* arg);

    // Debug Helpers
    void scan_i2c_bus();    // Checks if 0x34 is actually visible
    void dump_registers();  // Prints chip state to console

    static uint8_t read_byte(uint8_t reg);
    static void write_byte(uint8_t reg, uint8_t val);
    static uint32_t map_key(uint8_t key_id);

    static lv_indev_t* indev_keypad;
    static SemaphoreHandle_t irq_sem;
    static QueueHandle_t key_queue;
};