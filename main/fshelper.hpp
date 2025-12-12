#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"

#define MOUNT_POINT "/sdcard"

#define SD_SPI_DMA_CHAN SPI_DMA_CH_AUTO
#define SD_PIN_NUM_MISO GPIO_NUM_33
#define SD_PIN_NUM_MOSI GPIO_NUM_34
#define SD_PIN_NUM_CLK GPIO_NUM_35
#define SD_PIN_NUM_CS GPIO_NUM_21

static const char mount_point[] = MOUNT_POINT;
static sdmmc_card_t* card;
bool mount_sdcard() {
    esp_err_t ret;
    // 1. Configuration for mounting
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};
    ESP_LOGI("SDCARD", "Initializing SD card via SPI");
    // 2. Initialize the SPI Bus
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = SD_PIN_NUM_MOSI,
        .miso_io_num = SD_PIN_NUM_MISO,
        .sclk_io_num = SD_PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 8880,
    };
    ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SD_SPI_DMA_CHAN);

    // 3. Initialize the SD SPI Host Interface
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI2_HOST;  // Must match the SPI host initialized above
    // 4. Configure the specific Slot (CS pin)
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = SD_PIN_NUM_CS;
    slot_config.host_id = SPI2_HOST;
    // 5. Mount the Filesystem
    // Note: We use esp_vfs_fat_sdspi_mount here, NOT sdmmc_mount
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE("SDCARD", "Failed to mount filesystem. Check wiring.");
        } else {
            ESP_LOGE("SDCARD", "Failed to initialize the card (%s).", esp_err_to_name(ret));
        }
        return false;
    }
    ESP_LOGI("SDCARD", "Filesystem mounted via SPI");
    return true;
}

void unmount_sdcard() {
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI("SDCARD", "Card unmounted");
}