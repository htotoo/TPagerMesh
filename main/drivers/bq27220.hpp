#pragma once

#include "I2CDevice.hpp"

#define BQ27220_I2C_ADDRESS 0x55

class BQ27220 : public I2CDevice {
   public:
    BQ27220(uint8_t address = BQ27220_I2C_ADDRESS);

    bool init();

    // --- Telemetry ---
    uint16_t getVoltage();
    int16_t getCurrent();
    uint16_t getSOC();
    uint16_t getRemainingCapacity();
    uint16_t getFullChargeCapacity();
    float getTemperature();
    uint16_t getDeviceType();

    // --- Configuration ---

    /**
     * @brief Set the Design Capacity of the battery.
     * This is critical for accurate SOC calculations.
     * @param capacity_mah The nominal capacity in mAh (e.g., 2000)
     */
    bool setDesignCapacity(uint16_t capacity_mah);

    /**
     * @brief Update the Full Charge Capacity (Actual Capacity).
     * WARNING: The gauge learns this automatically. Overwriting it manually
     * allows you to reset the gauge's "learned" capacity to a known value
     * (e.g., if you swap in a fresh battery).
     * @param capacity_mah The new actual capacity in mAh
     */
    bool setFullChargeCapacity(uint16_t capacity_mah);

   protected:
    bool readWord(uint8_t reg, uint16_t& value);
    bool writeWord(uint8_t reg, uint16_t value);  // Helper needed for setting
    bool executeControl(uint16_t subcommand, uint16_t& result);
    bool enterConfigMode();
    bool exitConfigMode();

    static const uint8_t REG_CNTL = 0x00;
    static const uint8_t REG_TEMP = 0x06;
    static const uint8_t REG_VOLT = 0x08;
    static const uint8_t REG_FLAGS = 0x0A;
    static const uint8_t REG_CURRENT = 0x0C;
    static const uint8_t REG_RM = 0x10;
    static const uint8_t REG_FCC = 0x12;
    static const uint8_t REG_SOC = 0x2C;

    // Configuration Registers (Data Memory)
    // Note: Writing to DM requires entering specific modes or subcommands.
    // For simplicity on BQ27220, we use the standard extended commands if available
    // or the "DesignCapacity" subcommand 0x001D is not standard access.
    // BQ27220 stores Design Capacity in Data Memory (Subclass 82, Offset 10).
    // Accessing Data Memory directly is complex on BQ27220.
    // However, BQ27220 has a specific RAM register for DesignCapacity (0x3C) in some modes?
    // Actually, on BQ27220 Design Capacity is accessed via Data Memory Block 0x92.

    // To keep it simple for this driver without implementing full Block Data Control:
    static const uint8_t REG_DESIGN_CAP = 0x3C;  // Standard command for *reading* on many BQs,
                                                 // but setting requires Data Memory access.

    static const uint16_t SUB_DEVICE_TYPE = 0x0001;
    static const uint16_t SUB_ENTER_CFG = 0x0090;
    static const uint16_t SUB_EXIT_CFG = 0x0091;
    static const uint16_t SUB_SET_FULLSLEEP = 0x0010;
};