#pragma once
#include <functional>
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
#define KEY_SWITCH_FOCUS 0x80
#define KEYMAP_ROWS 32
#define KEYMAP_COLS 3

class KeypadDriver {
   public:
    void begin();
    void register_lvgl();
    static lv_indev_t* get_indev() { return indev_keypad; }

    // Callback for LVGL
    static void read_cb(lv_indev_t* indev, lv_indev_data_t* data);

    // Global hook for System Keys (Focus switch, etc)
    typedef std::function<void(uint32_t)> key_hook_t;
    static void set_global_key_hook(key_hook_t hook) { global_hook = hook; }

   private:
    // New Data Structure for Event Queue
    struct KeyEvent {
        uint32_t key;
        bool is_pressed;
    };

    static void IRAM_ATTR isr_handler(void* arg);
    static void handle_interrupt_task(void* arg);
    static void write_byte(uint8_t reg, uint8_t val);
    static uint8_t read_byte(uint8_t reg);

    // Logic
    static uint32_t map_key(uint8_t key_id);
    static int get_key_index(uint8_t key_id);

    static lv_indev_t* indev_keypad;
    static SemaphoreHandle_t irq_sem;
    static QueueHandle_t key_queue;  // Now holds KeyEvent struct
    static key_hook_t global_hook;

    static uint8_t key_stage;
    static uint32_t last_processed_key;  // Used to keep state stable when queue is empty
    static bool last_processed_state;    // Used to keep state stable when queue is empty
};