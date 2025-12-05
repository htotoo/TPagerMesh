idf_component_register(SRCS "main.cpp" "nmea_parser.c" "encoder.c"
                      REQUIRES spi_flash esp_wifi spiffs esp_event esp_driver_uart mdns nvs_flash esp_http_server app_update EspMeshCompact
                    INCLUDE_DIRS ""  )
