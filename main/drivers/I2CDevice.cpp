#include "I2CDevice.hpp"
static const char* TAG = "i2cdev";
I2CDevice::i2c_port_state_t I2CDevice::states[I2C_NUM_MAX] = {};

I2CDevice::I2CDevice(uint8_t address, uint32_t speed) : _address(address), clk_speed(speed) {
    cfg.mode = I2C_MODE_MASTER;
    cfg.sda_io_num = sda_gpio;
    cfg.scl_io_num = scl_gpio;
    cfg.sda_pullup_en = GPIO_PULLUP_ENABLE;
    cfg.scl_pullup_en = GPIO_PULLUP_ENABLE;
    cfg.master.clk_speed = clk_speed;
    cfg.clk_flags = 0;
}

I2CDevice::~I2CDevice() {}

bool I2CDevice::begin() {
    esp_err_t err = probe(true);
    return (err == ESP_OK);
}

esp_err_t I2CDevice::i2c_setup_port() {
    if (port >= I2C_NUM_MAX)
        return ESP_ERR_INVALID_ARG;
    esp_err_t res;
    if (!cfg_equal(&cfg, &states[port].config) || !states[port].installed) {
        i2c_config_t temp;
        memcpy(&temp, &cfg, sizeof(i2c_config_t));
        temp.mode = I2C_MODE_MASTER;
        // Driver reinstallation
        if (states[port].installed) {
            i2c_driver_delete(port);
            states[port].installed = false;
        }
        // See https://github.com/espressif/esp-idf/issues/10163
        if ((res = i2c_driver_install(port, temp.mode, 0, 0, 0)) != ESP_OK)
            return res;
        if ((res = i2c_param_config(port, &temp)) != ESP_OK)
            return res;

        states[port].installed = true;

        memcpy(&states[port].config, &temp, sizeof(i2c_config_t));
    }
    int t;
    if ((res = i2c_get_timeout(port, &t)) != ESP_OK)
        return res;
    // Timeout cannot be 0
    uint32_t ticks = timeout_ticks ? timeout_ticks : I2CDEV_MAX_STRETCH_TIME;
    if ((ticks != t) && (res = i2c_set_timeout(port, ticks)) != ESP_OK)
        return res;
    return ESP_OK;
}

esp_err_t I2CDevice::probe(bool read_operation) {
    esp_err_t res = i2c_setup_port();
    if (res == ESP_OK) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, _address << 1 | (read_operation ? 1 : 0), true);
        i2c_master_stop(cmd);
        uint32_t ticks = timeout_ticks ? timeout_ticks : I2CDEV_MAX_STRETCH_TIME;
        res = i2c_master_cmd_begin(port, cmd, ticks);
        i2c_cmd_link_delete(cmd);
    }
    return res;
}

bool I2CDevice::write(const uint8_t* data, size_t length) {
    return write(nullptr, 0, data, length);
}

bool I2CDevice::write(const uint8_t* reg, size_t reg_length, const uint8_t* data, size_t length) {
    esp_err_t res = i2c_setup_port();
    if (res == ESP_OK) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, _address << 1, true);
        if (reg && reg_length)
            i2c_master_write(cmd, reg, reg_length, true);
        i2c_master_write(cmd, data, length, true);
        i2c_master_stop(cmd);
        uint32_t ticks = timeout_ticks ? timeout_ticks : I2CDEV_MAX_STRETCH_TIME;
        res = i2c_master_cmd_begin(port, cmd, ticks);
        if (res != ESP_OK)
            ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", _address, port, res, esp_err_to_name(res));
        i2c_cmd_link_delete(cmd);
    }
    return res == ESP_OK;
}

bool I2CDevice::write_then_read(const uint8_t* write_data, size_t write_length, uint8_t* read_data, size_t read_length) {
    esp_err_t res = i2c_setup_port();
    if (res == ESP_OK) {
        uint32_t ticks = timeout_ticks ? timeout_ticks : I2CDEV_MAX_STRETCH_TIME;
        res = i2c_master_write_read_device(port, _address, write_data, write_length, read_data, read_length, ticks);
        if (res != ESP_OK)
            ESP_LOGE(TAG, "Could not write/read to/from device [0x%02x at %d]: %d (%s)", _address, port, res, esp_err_to_name(res));
    }
    return res == ESP_OK;
}

bool I2CDevice::read(const uint8_t* reg, size_t reg_length, const uint8_t* data, size_t length) {
    if (!data || !length)
        return false;
    esp_err_t res = i2c_setup_port();
    if (res == ESP_OK) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        if (reg && reg_length) {
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, _address << 1, true);
            i2c_master_write(cmd, reg, reg_length, true);
        }
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (_address << 1) | 1, true);
        i2c_master_read(cmd, (uint8_t*)data, length, I2C_MASTER_LAST_NACK);
        i2c_master_stop(cmd);
        uint32_t ticks = timeout_ticks ? timeout_ticks : I2CDEV_MAX_STRETCH_TIME;
        res = i2c_master_cmd_begin(port, cmd, ticks);
        if (res != ESP_OK)
            ESP_LOGE(TAG, "Could not read from device [0x%02x at %d]: %d (%s)", _address, port, res, esp_err_to_name(res));
        i2c_cmd_link_delete(cmd);
    }
    return res == ESP_OK;
}

inline bool I2CDevice::cfg_equal(const i2c_config_t* a, const i2c_config_t* b) {
    return a->scl_io_num == b->scl_io_num && a->sda_io_num == b->sda_io_num && a->master.clk_speed == b->master.clk_speed && a->scl_pullup_en == b->scl_pullup_en && a->sda_pullup_en == b->sda_pullup_en;
}