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
#define KEYPAD_IRQ_PIN GPIO_NUM_6

// Map Definitions
#define KEYMAP_ROWS 32
#define KEYMAP_COLS 3

class KeypadDriver {
   public:
    void begin();

    // LVGL Callback
    static void read_cb(lv_indev_t* indev, lv_indev_data_t* data);

    // Accessor for main.cpp
    static lv_indev_t* get_indev() { return indev_keypad; }

    void register_lvgl();

   private:
    static void IRAM_ATTR isr_handler(void* arg);
    static void handle_interrupt_task(void* arg);
    static void write_byte(uint8_t reg, uint8_t val);
    static uint8_t read_byte(uint8_t reg);

    // Mapping Logic
    static uint32_t map_key(uint8_t key_id);
    static int get_key_index(uint8_t key_id);

    static lv_indev_t* indev_keypad;
    static SemaphoreHandle_t irq_sem;
    static QueueHandle_t key_queue;

    // Logic State
    static uint8_t key_stage;          // 0=Lower, 1=Upper, 2=Num
    static uint32_t current_held_key;  // The key currently physically held down
    static uint32_t last_sent_key;     // The last key reported to LVGL
};