idf_component_register(SRCS "main.cpp" 
"drivers/I2CDevice.cpp" "drivers/DRV2605.cpp" "drivers/nmea_parser.c" "drivers/encoder.c" "drivers/DRV2605.cpp" "drivers/button.c"
"drivers/XPowersLibInterface.cpp" 
REQUIRES spi_flash esp_wifi spiffs esp_event esp_driver_uart mdns nvs_flash esp_http_server app_update EspMeshCompact
INCLUDE_DIRS "."  )
