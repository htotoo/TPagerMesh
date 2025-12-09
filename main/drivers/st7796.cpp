#include "st7796.hpp"
static const char* TAG = "st7796";
lv_display_t* ST7796Driver::disp = nullptr;

static void lv_tick_task(void* arg) {
    lv_tick_inc(5);  // Tell LVGL that 2 milliseconds have passed
}
void start_lvgl_tick() {
    const esp_timer_create_args_t lv_tick_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick"};
    esp_timer_handle_t lv_tick_timer;
    esp_timer_create(&lv_tick_timer_args, &lv_tick_timer);
    // Fire every 2ms
    esp_timer_start_periodic(lv_tick_timer, 5000);
}

bool ST7796Driver::begin() {
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .mosi_io_num = 34,
        .miso_io_num = 33,
        .sclk_io_num = 35,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_H_RES * LCD_BUFFER_LINES * sizeof(uint16_t),  // transfer 80 lines of pixels (assume pixel is RGB565) at most in one SPI transaction
    };
    spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = 38,
        .dc_gpio_num = 37,
        .spi_mode = 0,
        .pclk_hz = 10 * 1000 * 1000,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));
    panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16,
    };
    // Create LCD panel handle for ST7796, with the SPI IO device handle
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7796(io_handle, &panel_config, &panel_handle));
    esp_lcd_panel_reset(panel_handle);

    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    esp_lcd_panel_invert_color(panel_handle, false);
    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_mirror(panel_handle, true, true);
    esp_lcd_panel_set_gap(panel_handle, 0, 49);
    esp_lcd_panel_disp_on_off(panel_handle, true);
    // init backlight using LEDC
    init_backlight();
    init_lvgl_display();
    // start_lvgl_tick();
    lv_timer_handler();
    return true;
}

bool ST7796Driver::end() {
    if (panel_handle) esp_lcd_panel_del(panel_handle);
    panel_handle = nullptr;
    if (io_handle) esp_lcd_panel_io_del(io_handle);
    io_handle = nullptr;
    return true;
}

void ST7796Driver::dispOnOff(bool on) {
    disp_on = on;
    if (panel_handle)
        esp_lcd_panel_disp_on_off(panel_handle, on);
    aw9364_set_brightness_pct(aw9364_dev_hdl, on ? brightness : 0, 100);
}

void ST7796Driver::setBrightness(uint8_t brightness_percent) {
    if (brightness_percent > 100)
        brightness = 100;
    else
        brightness = brightness_percent;
    if ((brightness > 6) != disp_on) {
        dispOnOff(brightness > 6);
    } else {
        aw9364_set_brightness_pct(aw9364_dev_hdl, brightness, 100);
    }
}

bool ST7796Driver::notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t* edata, void* user_ctx) {
    lv_display_flush_ready(disp);  // Tell LVGL the driver is ready for the next chunk
    return false;
}

void ST7796Driver::my_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map) {
    // Retrieve your esp_lcd handle from the user_data (we'll set this later)
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);
    // Send pixels to the display driver
    // x1, y1, x2, y2, raw_pixel_data
    int x_start = area->x1;
    int x_end = area->x2 + 1;  // esp_lcd uses exclusive end coordinate
    int y_start = area->y1;
    int y_end = area->y2 + 1;

    esp_lcd_panel_draw_bitmap(panel_handle, x_start, y_start, x_end, y_end, px_map);
}

void ST7796Driver::init_lvgl_display() {
    // 1. Initialize LVGL core
    lv_init();

    // 2. Register the "Done" callback with your ESP_LCD driver
    // This allows the DMA to tell LVGL when it's finished sending pixels
    const esp_lcd_panel_io_callbacks_t cbs = {
        .on_color_trans_done = notify_lvgl_flush_ready,
    };
    // IMPORTANT: You typically register this *during* your IO creation.
    // If you already created the IO handle without this callback, you might need to
    // modify your existing ST7796 init code to include this callback structure.
    esp_lcd_panel_io_register_event_callbacks(io_handle, &cbs, disp);

    // 3. Create the LVGL Display Object
    // Adjust resolution to match your screen
    uint32_t w = LCD_V_RES;
    uint32_t h = LCD_H_RES;
    disp = lv_display_create(w, h);

    // 4. Create Draw Buffers
    // LVGL 9 needs a buffer to render into. 1/10th of screen is standard.
    // We use heap_caps_malloc to put it in DMA-capable RAM (Internal or PSRAM)
    size_t buf_size = w * LCD_BUFFER_LINES * sizeof(uint16_t);  // 20 lines high
    void* buf1 = heap_caps_malloc(buf_size, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
    void* buf2 = NULL;  // Set this to a second buffer for double-buffering (smoother animation)

    // 5. Configure the Display
    lv_display_set_buffers(disp, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, my_flush_cb);

    // Store the panel handle in the display object so the flush_cb can find it
    lv_display_set_user_data(disp, (void*)panel_handle);

    // 6. Be sure to update the "user_ctx" for the callback we set in step 2
    // We need 'notify_lvgl_flush_ready' to know which 'disp' to notify.
    // (This part depends on how your specific esp_lcd IO driver stores context,
    // often simpler to use a global variable for 'disp' if this gets too complex).
    lv_obj_t* c1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(c1, 20, 20);
    lv_obj_set_style_radius(c1, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(c1, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(c1, 0, 0);
    lv_obj_align(c1, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_remove_flag(c1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* c2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(c2, 20, 20);
    lv_obj_set_style_radius(c2, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(c2, lv_color_hex(0x0FFF0F), 0);
    lv_obj_set_style_border_width(c2, 0, 0);
    lv_obj_align(c2, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_remove_flag(c2, LV_OBJ_FLAG_SCROLLABLE);
}

void ST7796Driver::init_backlight() {
    ESP_LOGI(TAG, "Configuring LCD Brightness...");
    // Setup LEDC peripheral for PWM backlight control
    const ledc_channel_config_t lcd_backlight_channel = {
        .gpio_num = LEDC_DISP_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0};
    const ledc_timer_config_t lcd_backlight_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_1,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_LOGI(TAG, "initialize aw9364");
    esp_err_t err = aw9364_init(&lcd_backlight_channel, &lcd_backlight_timer, &aw9364_dev_hdl);
    ESP_ERROR_CHECK(err);
}