idf_component_register(SRCS "font_montserrat_12_hun.c" "main.cpp" "message_store.cpp"
"font_montserrat_10_hun.c"
"drivers/I2CDevice.cpp" "drivers/DRV2605.cpp" "drivers/nmea_parser.c" "drivers/encoder.c" "drivers/DRV2605.cpp" "drivers/button.c"
"drivers/XPowersLibInterface.cpp"  "drivers/st7796.cpp" "drivers/aw9364.c" "drivers/keypad_irq.cpp" "drivers/bq27220.cpp"
REQUIRES esp_driver_sdspi esp_driver_spi fatfs spi_flash esp_lcd esp_wifi esp_driver_ledc spiffs esp_event esp_driver_uart mdns nvs_flash esp_http_server app_update EspMeshCompact
INCLUDE_DIRS "."  )
