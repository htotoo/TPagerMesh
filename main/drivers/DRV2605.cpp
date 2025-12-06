
#include "DRV2605.hpp"

DRV2605::DRV2605() {}

bool DRV2605::begin() {
    if (i2c_dev)
        delete i2c_dev;
    i2c_dev = new I2CDevice(DRV2605_ADDR);
    return init();
}

bool DRV2605::init() {
    if (!i2c_dev->begin())
        return false;
    writeRegister8(DRV2605_REG_MODE, 0x00);  // out of standby

    writeRegister8(DRV2605_REG_RTPIN, 0x00);  // no real-time-playback

    writeRegister8(DRV2605_REG_WAVESEQ1, 1);  // strong click
    writeRegister8(DRV2605_REG_WAVESEQ2, 0);  // end sequence

    writeRegister8(DRV2605_REG_OVERDRIVE, 0);  // no overdrive

    writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
    writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
    writeRegister8(DRV2605_REG_BREAK, 0);
    writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);
    // turn off N_ERM_LRA
    writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
    // turn on ERM_OPEN_LOOP
    writeRegister8(DRV2605_REG_CONTROL3, readRegister8(DRV2605_REG_CONTROL3) | 0x20);

    return true;
}

void DRV2605::setWaveform(uint8_t slot, uint8_t w) {
    writeRegister8(DRV2605_REG_WAVESEQ1 + slot, w);
}

void DRV2605::selectLibrary(uint8_t lib) {
    writeRegister8(DRV2605_REG_LIBRARY, lib);
}

void DRV2605::go() {
    writeRegister8(DRV2605_REG_GO, 1);
}

void DRV2605::stop() {
    writeRegister8(DRV2605_REG_GO, 0);
}

void DRV2605::setMode(uint8_t mode) {
    writeRegister8(DRV2605_REG_MODE, mode);
}

void DRV2605::setRealtimeValue(uint8_t rtp) {
    writeRegister8(DRV2605_REG_RTPIN, rtp);
}

uint8_t DRV2605::readRegister8(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    i2c_dev->write_then_read(buffer, 1, buffer, 1);
    return buffer[0];
}

void DRV2605::writeRegister8(uint8_t reg, uint8_t val) {
    uint8_t buffer[2] = {reg, val};
    i2c_dev->write(buffer, 2);
}

void DRV2605::useERM() {
    writeRegister8(DRV2605_REG_FEEDBACK,
                   readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
}

void DRV2605::useLRA() {
    writeRegister8(DRV2605_REG_FEEDBACK,
                   readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
}