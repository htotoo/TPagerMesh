#pragma once

#include "I2CDevice.hpp"

#define BQ27220_I2C_ADDRESS 0x55

class BQ27220 : public I2CDevice {
   public:
    BQ27220(uint8_t address = BQ27220_I2C_ADDRESS);

    /**
     * @brief Initialize the sensor.
     * Forces I2C to 100kHz to comply with BQ27220 timing specs.
     */
    bool init();

    // --- Telemetry Data ---
    uint16_t getVoltage();
    int16_t getCurrent();
    uint16_t getSOC();
    uint16_t getRemainingCapacity();
    uint16_t getFullChargeCapacity();
    float getTemperature();
    uint16_t getDeviceType();

    // --- Configuration ---

    /**
     * @brief Set the Design Capacity (Updates Data Memory).
     * @param capacity_mah The nominal capacity in mAh
     */
    bool setDesignCapacity(uint16_t capacity_mah);

    /**
     * @brief Force update the Full Charge Capacity.
     * @param capacity_mah The new actual capacity in mAh
     */
    bool setFullChargeCapacity(uint16_t capacity_mah);

   protected:
    bool readWord(uint8_t reg, uint16_t& value);
    bool writeWord(uint8_t reg, uint16_t value);
    bool executeControl(uint16_t subcommand, uint16_t& result);

    // Config & Security
    bool unseal();
    bool enterConfigUpdate();
    bool exitConfigUpdate();
    bool writeDataMemory(uint16_t address, uint8_t* data, uint8_t len);

    static const uint8_t REG_CNTL = 0x00;
    static const uint8_t REG_TEMP = 0x06;
    static const uint8_t REG_VOLT = 0x08;
    static const uint8_t REG_FLAGS = 0x0A;
    static const uint8_t REG_CURRENT = 0x0C;
    static const uint8_t REG_RM = 0x10;
    static const uint8_t REG_FCC = 0x12;
    static const uint8_t REG_SOC = 0x2C;

    // MAC Registers for Data Memory Access
    static const uint8_t REG_MAC_DATA = 0x3E;  // AltManufacturerAccess / MACData
    static const uint8_t REG_MAC_CKSUM = 0x60;
    static const uint8_t REG_MAC_LEN = 0x61;

    static const uint16_t SUB_DEVICE_TYPE = 0x0001;
    static const uint16_t SUB_ENTER_CFG = 0x0090;
    static const uint16_t SUB_EXIT_CFG = 0x0091;
    static const uint16_t SUB_SEAL = 0x0030;

    static const uint16_t KEY_UNSEAL_1 = 0x0414;  // Default TI Unseal Keys
    static const uint16_t KEY_UNSEAL_2 = 0x3672;
};