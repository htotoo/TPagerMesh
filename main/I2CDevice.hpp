#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <driver/i2c.h>
#include <string.h>
#include "esp_log.h"

#define I2C_CLK_SPEED_DEFAULT 400000
#define I2CDEV_MAX_STRETCH_TIME 0x0000001FU

class I2CDevice {
   public:
    I2CDevice(uint8_t address, uint32_t speed = I2C_CLK_SPEED_DEFAULT);
    ~I2CDevice();

    bool begin();
    esp_err_t probe(bool read_operation);
    bool write(const uint8_t* data, size_t length);
    bool write(const uint8_t* reg, size_t reg_length, const uint8_t* data, size_t length);
    bool write_then_read(const uint8_t* write_data, size_t write_length, uint8_t* read_data, size_t read_length);
    bool read(const uint8_t* reg, size_t reg_length, const uint8_t* data, size_t length);

   private:
    esp_err_t i2c_setup_port();
    static bool cfg_equal(const i2c_config_t* a, const i2c_config_t* b);
    uint8_t _address;
    i2c_port_t port = I2C_NUM_0;
    i2c_config_t cfg;
    gpio_num_t sda_gpio = (gpio_num_t)3;
    gpio_num_t scl_gpio = (gpio_num_t)2;
    uint32_t clk_speed = I2C_CLK_SPEED_DEFAULT;
    uint32_t timeout_ticks = 0;

    typedef struct
    {
        SemaphoreHandle_t lock;
        i2c_config_t config;
        bool installed;
    } i2c_port_state_t;
    static i2c_port_state_t states[I2C_NUM_MAX];
};