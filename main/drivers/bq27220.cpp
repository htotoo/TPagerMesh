#include "bq27220.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "BQ27220";

// Data Memory Addresses (Subclass 82 State)
// Design Capacity is at Offset 10 (0x0A) -> Physical Address 0x929F
#define DM_DESIGN_CAPACITY_ADDR 0x929F
#define DM_FCC_ADDR 0x929D

BQ27220::BQ27220(uint8_t address) : I2CDevice(address, 40000) {
}

bool BQ27220::init() {
    ESP_LOGI(TAG, "Initializing BQ27220...");

    uint16_t devType = getDeviceType();

    if (devType == 0x0220) {
        ESP_LOGI(TAG, "Found BQ27220 (ID: 0x%04X)", devType);
        return true;
    }

    // If ID is still weird, try Unsealing in case it's locked
    ESP_LOGW(TAG, "Unexpected ID: 0x%04X. Trying Unseal...", devType);
    unseal();
    vTaskDelay(pdMS_TO_TICKS(100));

    devType = getDeviceType();
    if (devType != 0) {
        ESP_LOGI(TAG, "Recovered ID: 0x%04X", devType);
        return true;
    }

    ESP_LOGE(TAG, "BQ27220 init failed.");
    return false;
}

// --- Telemetry ---

uint16_t BQ27220::getVoltage() {
    uint16_t val = 0;
    readWord(REG_VOLT, val);
    return val;
}

int16_t BQ27220::getCurrent() {
    uint16_t val = 0;
    readWord(REG_CURRENT, val);
    return (int16_t)val;
}

uint16_t BQ27220::getSOC() {
    uint16_t val = 0;
    readWord(REG_SOC, val);
    return val;
}

uint16_t BQ27220::getRemainingCapacity() {
    uint16_t val = 0;
    readWord(REG_RM, val);
    return val;
}

uint16_t BQ27220::getFullChargeCapacity() {
    uint16_t val = 0;
    readWord(REG_FCC, val);
    return val;
}

float BQ27220::getTemperature() {
    uint16_t val = 0;
    if (readWord(REG_TEMP, val)) {
        return ((float)val / 10.0f) - 273.15f;
    }
    return 0.0f;
}

uint16_t BQ27220::getDeviceType() {
    uint16_t val = 0;
    // We try twice in case the first one is ignored due to sleep
    if (!executeControl(SUB_DEVICE_TYPE, val)) {
        vTaskDelay(pdMS_TO_TICKS(10));
        executeControl(SUB_DEVICE_TYPE, val);
    }
    return val;
}

// --- Configuration ---

bool BQ27220::setDesignCapacity(uint16_t capacity_mah) {
    ESP_LOGI(TAG, "Setting Design Capacity to %d mAh...", capacity_mah);

    if (!unseal()) return false;
    if (!enterConfigUpdate()) return false;

    // Data must be Big Endian for Data Memory
    uint8_t data[2];
    data[0] = (capacity_mah >> 8) & 0xFF;
    data[1] = (capacity_mah & 0xFF);

    bool success = writeDataMemory(DM_DESIGN_CAPACITY_ADDR, data, 2);

    if (success)
        ESP_LOGI(TAG, "Design Capacity Updated");
    else
        ESP_LOGE(TAG, "Design Capacity Write Failed");

    exitConfigUpdate();
    return success;
}

bool BQ27220::setFullChargeCapacity(uint16_t capacity_mah) {
    ESP_LOGI(TAG, "Setting FCC to %d mAh...", capacity_mah);

    if (!unseal()) return false;
    if (!enterConfigUpdate()) return false;

    uint8_t data[2];
    data[0] = (capacity_mah >> 8) & 0xFF;
    data[1] = (capacity_mah & 0xFF);

    bool success = writeDataMemory(DM_FCC_ADDR, data, 2);

    exitConfigUpdate();
    return success;
}

// --- Helpers ---

bool BQ27220::unseal() {
    uint16_t dummy;
    executeControl(KEY_UNSEAL_1, dummy);
    executeControl(KEY_UNSEAL_2, dummy);
    return true;
}

bool BQ27220::enterConfigUpdate() {
    uint16_t dummy;
    if (!executeControl(SUB_ENTER_CFG, dummy)) return false;

    // Wait for mode switch (Datasheet implies this can take time)
    vTaskDelay(pdMS_TO_TICKS(100));
    return true;
}

bool BQ27220::exitConfigUpdate() {
    uint16_t dummy;
    if (!executeControl(SUB_EXIT_CFG, dummy)) return false;
    vTaskDelay(pdMS_TO_TICKS(100));
    return true;
}

bool BQ27220::writeDataMemory(uint16_t address, uint8_t* data, uint8_t len) {
    // 1. Write Address and Data to MAC (0x3E)
    uint8_t buffer[34];
    buffer[0] = address & 0xFF;         // Addr LSB
    buffer[1] = (address >> 8) & 0xFF;  // Addr MSB
    memcpy(&buffer[2], data, len);

    uint8_t reg_mac = REG_MAC_DATA;
    if (!this->write(&reg_mac, 1, buffer, len + 2)) return false;

    // 2. Write Checksum to 0x60
    uint8_t checksum = 0;
    for (int i = 0; i < len + 2; i++) checksum += buffer[i];
    checksum = 0xFF - checksum;

    uint8_t reg_cs = REG_MAC_CKSUM;
    if (!this->write(&reg_cs, 1, &checksum, 1)) return false;

    // 3. Write Length to 0x61
    uint8_t total_len = len + 4;  // Addr(2) + Data(len) + CS(1) + Len(1) ?
    // Actually, BQ27220 usually expects Length = (Data + Address) + 2
    total_len = (len + 2) + 2;

    uint8_t reg_len = REG_MAC_LEN;
    if (!this->write(&reg_len, 1, &total_len, 1)) return false;

    vTaskDelay(pdMS_TO_TICKS(50));  // Flash write time
    return true;
}

bool BQ27220::executeControl(uint16_t subcommand, uint16_t& result) {
    uint8_t data[2];
    data[0] = subcommand & 0xFF;
    data[1] = (subcommand >> 8) & 0xFF;

    uint8_t reg = REG_CNTL;
    if (!this->write(&reg, 1, data, 2)) return false;

    // Mandatory delay for subcommand processing
    vTaskDelay(pdMS_TO_TICKS(5));

    return readWord(REG_CNTL, result);
}

bool BQ27220::readWord(uint8_t reg, uint16_t& value) {
    uint8_t data[2] = {0};
    uint8_t r = reg;
    if (this->read(&r, 1, data, 2)) {
        value = (data[1] << 8) | data[0];
        return true;
    }
    return false;
}

bool BQ27220::writeWord(uint8_t reg, uint16_t value) {
    uint8_t data[2];
    data[0] = value & 0xFF;
    data[1] = (value >> 8) & 0xFF;
    uint8_t r = reg;
    return this->write(&r, 1, data, 2);
}