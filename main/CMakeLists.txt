idf_component_register(SRCS "I2CDevice.cpp" "DRV2605.cpp" "main.cpp" "nmea_parser.c" "encoder.c" "button.c" "I2CDevice.cpp" "DRV2605.cpp"
                      REQUIRES spi_flash esp_wifi spiffs esp_event esp_driver_uart mdns nvs_flash esp_http_server app_update EspMeshCompact
                    INCLUDE_DIRS ""  )
