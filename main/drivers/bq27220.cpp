#include "bq27220.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "BQ27220";

BQ27220::BQ27220(uint8_t address) : I2CDevice(address) {
    // Constructor just passes address to parent
}

bool BQ27220::init() {
    ESP_LOGI(TAG, "Initializing BQ27220...");

    // Basic probe to see if device ACKs
    if (!this->begin()) {
        ESP_LOGE(TAG, "I2C Probe failed");
        return false;
    }

    // Optional: Verify Device ID
    uint16_t devType = getDeviceType();
    if (devType == 0) {
        ESP_LOGW(TAG, "Device ID read failed or returned 0");
    } else {
        ESP_LOGI(TAG, "Found BQ27220 (ID: 0x%04X)", devType);
    }

    return true;
}

// --- Telemetry Getters ---

uint16_t BQ27220::getVoltage() {
    uint16_t val = 0;
    readWord(REG_VOLT, val);
    return val;  // Unit: mV
}

int16_t BQ27220::getCurrent() {
    uint16_t val = 0;
    readWord(REG_CURRENT, val);
    return (int16_t)val;  // Unit: mA (Signed)
}

uint16_t BQ27220::getSOC() {
    uint16_t val = 0;
    readWord(REG_SOC, val);
    return val;  // Unit: %
}

uint16_t BQ27220::getRemainingCapacity() {
    uint16_t val = 0;
    readWord(REG_RM, val);
    return val;  // Unit: mAh
}

uint16_t BQ27220::getFullChargeCapacity() {
    uint16_t val = 0;
    readWord(REG_FCC, val);
    return val;  // Unit: mAh
}

float BQ27220::getTemperature() {
    uint16_t val = 0;
    if (readWord(REG_TEMP, val)) {
        // Register is in 0.1 deg K. Convert to C.
        // C = (K / 10) - 273.15
        return ((float)val / 10.0f) - 273.15f;
    }
    return 0.0f;
}

uint16_t BQ27220::getDeviceType() {
    uint16_t val = 0;
    executeControl(SUB_DEVICE_TYPE, val);
    return val;
}

// --- Capacity Configuration ---

bool BQ27220::setDesignCapacity(uint16_t capacity_mah) {
    ESP_LOGI(TAG, "Setting Design Capacity to %d mAh...", capacity_mah);

    // 1. Enter Configuration Mode
    if (!enterConfigMode()) return false;

    // 2. Try to write to the DesignCapacity register (0x3C)
    // Note: On some BQ27220 firmwares, this register is directly writable in Config Mode.
    // If this fails, a full Data Memory block write implementation is required (complex).
    bool success = writeWord(REG_DESIGN_CAP, capacity_mah);

    if (success) {
        ESP_LOGI(TAG, "Written to Design Capacity (0x3C).");
    } else {
        ESP_LOGW(TAG, "Failed to write Design Capacity. Extended Data Memory access may be required.");
    }

    // 3. Exit Config Mode
    exitConfigMode();
    return success;
}

bool BQ27220::setFullChargeCapacity(uint16_t capacity_mah) {
    ESP_LOGI(TAG, "Forcing FCC to %d mAh...", capacity_mah);

    // Enter Config Mode to allow writing to protected registers
    if (!enterConfigMode()) return false;

    // Attempt to overwrite the Learned FCC (REG_FCC = 0x12)
    bool success = writeWord(REG_FCC, capacity_mah);

    exitConfigMode();

    if (success) {
        ESP_LOGI(TAG, "FCC updated successfully.");
    } else {
        ESP_LOGE(TAG, "Failed to update FCC.");
    }
    return success;
}

// --- Private Helpers ---

bool BQ27220::enterConfigMode() {
    uint16_t flags = 0;

    // Send ENTER_CFG subcommand
    if (!executeControl(SUB_ENTER_CFG, flags)) return false;

    // Wait for the gauge to process the command
    vTaskDelay(pdMS_TO_TICKS(10));
    return true;
}

bool BQ27220::exitConfigMode() {
    uint16_t flags = 0;

    // Send EXIT_CFG subcommand
    if (!executeControl(SUB_EXIT_CFG, flags)) return false;

    // Wait for the gauge to process the command
    vTaskDelay(pdMS_TO_TICKS(10));
    return true;
}

bool BQ27220::readWord(uint8_t reg, uint16_t& value) {
    uint8_t data[2] = {0};

    // Copy reg to local variable to safely pass its address
    uint8_t r = reg;

    if (this->read(&r, 1, data, 2)) {
        // TI Fuel Gauges are Little Endian (Low byte first)
        value = (data[1] << 8) | data[0];
        return true;
    }

    ESP_LOGE(TAG, "Failed to read register 0x%02X", reg);
    return false;
}

bool BQ27220::writeWord(uint8_t reg, uint16_t value) {
    uint8_t data[2];
    data[0] = value & 0xFF;         // LSB
    data[1] = (value >> 8) & 0xFF;  // MSB

    // Copy reg to local variable to safely pass its address
    uint8_t r = reg;

    if (!this->write(&r, 1, data, 2)) {
        ESP_LOGE(TAG, "Failed to write register 0x%02X", reg);
        return false;
    }
    return true;
}

bool BQ27220::executeControl(uint16_t subcommand, uint16_t& result) {
    // 1. Prepare data to write (Little Endian subcommand)
    uint8_t data[2];
    data[0] = subcommand & 0xFF;         // LSB
    data[1] = (subcommand >> 8) & 0xFF;  // MSB

    // Use local copy of the Control Register address
    uint8_t reg = REG_CNTL;

    if (!this->write(&reg, 1, data, 2)) {
        ESP_LOGE(TAG, "Failed to write Control Subcommand 0x%04X", subcommand);
        return false;
    }

    // 2. Read back result from Register 0x00 (REG_CNTL)
    // Some subcommands (like RESET or ENTER_CFG) don't return data,
    // but reading confirms the bus is still alive.
    return readWord(REG_CNTL, result);
}