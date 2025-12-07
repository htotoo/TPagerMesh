#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "soc/soc_caps.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_lcd_st7796.h"

#define LCD_H_RES (480)
#define LCD_V_RES (222)
#define LCD_BIT_PER_PIXEL (16)
#define LCD_DATA_WIDTH (8)

#define LEDC_BACKLIGHT_FREQ 1000  // HZ
#define LEDC_BACKLIGHT_BIT_WIDTH 8
#define LEDC_DISP_PIN 42

#define LCD_HOST SPI3_HOST

class ST7796Driver {
   public:
    bool begin();
    bool end();
    void setBrightness(uint8_t brightness_percent);
    void dispOnOff(bool on);
    void dispToggle() {
        disp_on = !disp_on;
        dispOnOff(disp_on);
    }

   private:
    bool disp_on = false;
    uint16_t brightness = 1023;  // when on, we'll use it
    esp_lcd_panel_handle_t panel_handle = nullptr;
    esp_lcd_panel_io_handle_t io_handle = nullptr;
};