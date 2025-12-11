/*
pins: https://github.com/Xinyuan-LilyGO/LilyGoLib/blob/master/docs/hardware/lilygo-t-lora-pager.md#-powermanage-channel

kb: meshtastic\firmware\src\input\TCA8418KeyboardBase.cpp

// TODOS:
- fix xpowerslib i2c init error (shows error, but works. need to migrate it to i2cdev class)

*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "mykey.hpp"

#include "esp_random.h"
#include "MtCompact.hpp"
#include "drivers/nmea_parser.h"
#include "drivers/encoder.h"
#include "drivers/button.h"
#include "drivers/DRV2605.hpp"
#include "drivers/XPowersLib.h"
#include "drivers/st7796.hpp"
#include "drivers/keypad_irq.hpp"
#include "esp_timer.h"

#include "message_store.hpp"
#include "app_ui/app_main.hpp"

App_Main app_main_ui;

ST7796Driver lcd;
XPowersPPM PPM;
KeypadDriver keypad;
MessageStore message_store;

#define RE_A_GPIO 40
#define RE_B_GPIO 41
#define RE_BTN_GPIO 7

static QueueHandle_t event_queue_re;
static rotary_encoder_t re;
struct {
    int32_t diff;           // Rotary turns
    bool physical_holding;  // Is the button currently held down?
    bool latched_press;     // Did a press happen since last poll?
} lvgl_encoder_state = {0, false, false};

button_t btn_power;

// #define CLIENTROLEALERT 1

// https://cdn.shopify.com/s/files/1/0617/7190/7253/files/T-LoRa-Pager.jpg?v=1748930071

static const char* TAG = "MeshBaba";
static const char* ssid = "MeshBaba";
static const char* password = "1234Mesh";

extern "C" {
void app_main();
}

Radio_PINS radio_pins = {
    /* sck*/ 35,
    /* miso*/ 33,
    /* mosi*/ 34,
    /* cs*/ 36,
    /* irq*/ 14,
    /* rst*/ 47,
    /* gpio*/ 48};  // T_pager.
LoraConfig lora_config = {
    /*.frequency = */ 869.525,   // config
    /*.bandwidth = */ 250,       // config
    /*.spreading_factor = */ 9,  // config
    /*.coding_rate = */ 5,       // config
    /*.sync_word = */ 0x2b,
    /*.preamble_length = */ 16,
    /*.output_power = */ 22,  // config
    /*.tcxo_voltage = */ 3.0,
    /*.use_regulator_ldo = */ true,
};  // default LoRa configuration for EU MFFAST 868
MtCompact mtCompact;

/**
 * @brief GPS Event Handler
 *
 * @param event_handler_arg handler specific arguments
 * @param event_base event base, here is fixed to ESP_NMEA_EVENT
 * @param event_id event id
 * @param event_data event specific arguments
 */
static void gps_event_handler(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    gps_t* gps = NULL;
    switch (event_id) {
        case GPS_UPDATE:
            gps = (gps_t*)event_data;
            /* print information parsed from GPS statements */
            // todo save it
            /* ESP_LOGI(TAG,
                      "%d/%d/%d %d:%d:%d => \r\n"
                      "\t\t\t\t\t\tlatitude   = %.05f°N\r\n"
                      "\t\t\t\t\t\tlongitude = %.05f°E\r\n"
                      "\t\t\t\t\t\taltitude   = %.02fm\r\n"
                      "\t\t\t\t\t\tspeed      = %fm/s",
                      gps->date.year + YEAR_BASE, gps->date.month, gps->date.day,
                      gps->tim.hour + TIME_ZONE, gps->tim.minute, gps->tim.second,
                      gps->latitude, gps->longitude, gps->altitude, gps->speed);*/
            break;
        case GPS_UNKNOWN:
            /* print unknown statements */
            ESP_LOGW(TAG, "Unknown statement:%s", (char*)event_data);
            break;
        default:
            break;
    }
}

bool needsPongReply(std::string& msg) {
    std::string lower_msg = msg;
    for (char& c : lower_msg) {
        c = tolower(c);
    }
    return (lower_msg.rfind("ping", 0) == 0 ||
            lower_msg.rfind("test", 0) == 0 ||
            lower_msg.rfind("teszt", 0) == 0);
}

bool needsSeqReply(std::string& msg) {
    std::string lower_msg = msg;
    for (char& c : lower_msg) {
        c = tolower(c);
    }
    return (lower_msg.rfind("seq ", 0) == 0);
}

void on_button(button_t* btn, button_state_t state) {
    // ESP_LOGI(TAG, "%s button %d", btn == &btn_power ? "Power btn" : "Unk", (int)state);
    if (btn == &btn_power) {
        switch (state) {
            case BUTTON_CLICKED:
                ESP_LOGI(TAG, "Power button clicked");
                lcd.dispToggle();
                break;
            case BUTTON_PRESSED_LONG:
                ESP_LOGI(TAG, "Power button long pressed");
                // todo poweroff
                PPM.shutdown();
                break;
            default:
                break;
        }
    }
}

void encoder_read_cb(lv_indev_t* indev, lv_indev_data_t* data) {
    // 1. Report Encoder Diff
    data->enc_diff = lvgl_encoder_state.diff;
    lvgl_encoder_state.diff = 0;
    if (lvgl_encoder_state.latched_press) {
        data->state = LV_INDEV_STATE_PRESSED;
        lvgl_encoder_state.latched_press = false;
    } else {
        if (lvgl_encoder_state.physical_holding) {
            data->state = LV_INDEV_STATE_PRESSED;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }
}

void updateTime() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%H:%M", &timeinfo);
    app_main_ui.set_time(strftime_buf);
}

void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {};
    strcpy((char*)wifi_config.ap.ssid, ssid);
    wifi_config.ap.ssid_len = strlen(ssid);
    strcpy((char*)wifi_config.ap.password, password);
    wifi_config.ap.max_connection = 4;
    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    if (strlen(password) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "WiFi AP initialized. SSID: %s, Password: %s", ssid, password);

    // GPS initialization
    nmea_parser_config_t config = NMEA_PARSER_CONFIG_DEFAULT();
    /* init NMEA parser library */
    nmea_parser_handle_t nmea_hdl = nmea_parser_init(&config);
    /* register event handler for NMEA parser library */
    nmea_parser_add_handler(nmea_hdl, gps_event_handler, NULL);
    ESP_LOGI(TAG, "Loading radio config.");

    // rotary encoder init
    event_queue_re = xQueueCreate(5, sizeof(rotary_encoder_event_t));
    // Setup rotary encoder library
    ESP_ERROR_CHECK(rotary_encoder_init(event_queue_re));
    // Add one encoder
    memset(&re, 0, sizeof(rotary_encoder_t));
    re.pin_a = (gpio_num_t)RE_A_GPIO;
    re.pin_b = (gpio_num_t)RE_B_GPIO;
    re.pin_btn = (gpio_num_t)RE_BTN_GPIO;
    ESP_ERROR_CHECK(rotary_encoder_add(&re));

    // button init
    btn_power.gpio = (gpio_num_t)0;
    btn_power.pressed_level = 0;
    btn_power.internal_pull = true;
    btn_power.autorepeat = false;
    btn_power.callback = on_button;
    ESP_ERROR_CHECK(button_init(&btn_power));

    DRV2605 haptic;
    // haptic init
    bool has_haptic = haptic.begin();
    if (has_haptic) {
        ESP_LOGI(TAG, "Haptic driver found.");
        haptic.selectLibrary(1);
        haptic.setMode(DRV2605_MODE_INTTRIG);
        haptic.setWaveform(0, 1);  // play effect
        haptic.setWaveform(1, 0);  // end waveform
        // play the effect!
        haptic.go();
    } else {
        ESP_LOGW(TAG, "Haptic driver not found.");
    }

    // power
    if (PPM.begin(I2C_NUM_0, 0x6B, 3, 2)) {
        ESP_LOGI(TAG, "Power driver initialized.");
    } else {
        ESP_LOGW(TAG, "Power driver not found.");
    }
    if (PPM.init()) {
        ESP_LOGI(TAG, "Power driver init success.");
    } else {
        ESP_LOGW(TAG, "Power driver init failed.");
    }

    ESP_LOGI(TAG, "Initializing Keypad...");
    keypad.begin();

    // LCD init
    lcd.begin();
    lcd.setBrightness(100);  // this also turns on the display

    // mt init
    mtCompact.loadNodeDb();
    mtCompact.setOkToMqtt(true);
    ESP_LOGI(TAG, "Radio initializing...");
    mtCompact.RadioInit(RadioType::LR1121, radio_pins, lora_config);
    ESP_LOGI(TAG, "Radio initialized.");
    mtCompact.setAutoFullNode(true);  // we don't want to be a full node
    mtCompact.setSendHopLimit(7);     // max hop limit
    mtCompact.setStealthMode(false);  // stealth mode, we don't
    mtCompact.setSendEnabled(true);   // we want to send packets
    mtCompact.setDebugMode(true);     // enable debug output
    mtCompact.setOnNodeInfoMessage([](MCT_Header& header, MCT_NodeInfo& nodeinfo, bool needReply, bool newNode) {
        if (nodeinfo.role == 0 && newNode) {
#ifdef CLIENTROLEALERT
            std::string sender = nodeinfo.short_name;
            std::string reply = sender + "! Kerlek gondold at, hogy biztosan CLIENT role kell-e neked. https://meshtastic.creativo.hu";
            mtCompact.sendTextMessage(reply, header.srcnode, 0, MCT_MESSAGE_TYPE_TEXT, 0, 0, false, 0);
            ESP_LOGI(TAG, "Sent role change suggestion to %s", sender.c_str());
#endif
        }
    });

    mtCompact.setOnMessage([](MCT_Header& header, MCT_TextMessage& message) {
        MCT_NodeInfo* nodeinfo = mtCompact.nodeinfo_db.get(header.srcnode);
        std::string sender;
        if (nodeinfo) {
            sender = nodeinfo->short_name;
        } else {
            char hexbuf[11];
            snprintf(hexbuf, sizeof(hexbuf), "0x%08" PRIx32, header.srcnode);
            sender = hexbuf;
        }
        uint32_t replyto = 0xffffffff;
        uint8_t chan = header.chan_hash;
        if (header.dstnode == 0xffffffff) {
            ESP_LOGI(TAG, "Broadcast message from %s: %s", sender.c_str(), message.text.c_str());
            replyto = 0xffffffff;
        } else {
            ESP_LOGI(TAG, "Direct message from %s: %s", sender.c_str(), message.text.c_str());
            replyto = header.srcnode;
            chan = 0;
        }
        if (needsPongReply(message.text)) {
            std::string reply = "Pong! ";
            int8_t hops = header.hop_start - header.hop_limit;
            if (hops > 0) {
                reply += " (hops: " + std::to_string(hops) + ")";
            } else {
                char rssi_buf[16], snr_buf[16];
                snprintf(rssi_buf, sizeof(rssi_buf), "%.1f", header.rssi);
                snprintf(snr_buf, sizeof(snr_buf), "%.1f", header.snr);
                reply += " (rssi: " + std::string(rssi_buf) + " dBm, snr: " + std::string(snr_buf) + " dB)";
            }
            mtCompact.sendTextMessage(reply, replyto, chan, MCT_MESSAGE_TYPE_TEXT, 0, header.packet_id, replyto == 0xffffffff, 0);
            ESP_LOGI(TAG, "Sent pong reply to %s", sender.c_str());
        }
        if (needsSeqReply(message.text)) {
            std::string reply = sender + "! Kerlek ne csinalj csomag tesztet publik csatornan. Mindneki latja!";
            mtCompact.sendTextMessage(reply, replyto, chan, MCT_MESSAGE_TYPE_TEXT, 0, header.packet_id, false, 0);
            ESP_LOGI(TAG, "Sent seq reply to %s", sender.c_str());
        }
        MessageStore::MessageEntry msg_entry = {
            .sender = sender,
            .channel = chan,
            .isDirect = (header.dstnode != 0xffffffff),
            .message = message.text,
            .isFromMe = false,
            .time = time(NULL)};
        message_store.addMessage(msg_entry);
    });

    std::string short_name = "Info";                                                                     // short name
    std::string long_name = "Hungarian Info Node";                                                       // long name
    MtCompactHelpers::NodeInfoBuilder(mtCompact.getMyNodeInfo(), 0xabbababa, short_name, long_name, 1);  // random nodeinfo
    mtCompact.getMyNodeInfo()->role = 1;
    uint8_t my_p_key[32] = MYKEY;
    memcpy(mtCompact.getMyNodeInfo()->private_key, my_p_key, 32);
    MtCompactHelpers::RegenerateOrGeneratePrivateKey(*mtCompact.getMyNodeInfo());
    mtCompact.setPrimaryChanByHash(31);
    MtCompactHelpers::PositionBuilder(mtCompact.my_position, 47.486, 19.078, 100);
    uint32_t timer = 0;  // 0.1 second timer
    mtCompact.sendMyNodeInfo();
    mtCompact.sendMyNodeInfo();

    rotary_encoder_event_t e;
    lv_indev_t* encoder_indev = lv_indev_create();
    lv_indev_set_type(encoder_indev, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(encoder_indev, encoder_read_cb);

    keypad.register_lvgl();
    keypad.set_global_key_hook([](uint32_t key) {
        ESP_LOGI(TAG, "Key pressed: 0x%08" PRIx32, key);
        if (key == KEY_SWITCH_FOCUS) {
            app_main_ui.toggle_focus_group();
        }
    });
    app_main_ui.init(encoder_indev, keypad.get_indev());
    app_main_ui.set_message_store(&message_store);
    app_main_ui.set_on_send_message([](const std::string& msg) {
        ESP_LOGI(TAG, "Sending message: %s", msg.c_str());
        mtCompact.sendTextMessage(msg, 0xffffffff, 256);
    });
    while (1) {
        timer++;
        if (timer % (30 * 60 * 100) == 0) {
            mtCompact.sendMyNodeInfo();
        }
        if (mtCompact.nodeinfo_db.needsSave()) {
            // mtCompact.saveNodeDb();
            mtCompact.nodeinfo_db.clearChangedFlag();
        }

        if (timer % (10 * 100) == 0) {
            app_main_ui.set_battery_status(99, true);  // todo real battery
            updateTime();
        }
        if (xQueueReceive(event_queue_re, &e, pdMS_TO_TICKS(0))) {
            switch (e.type) {
                case RE_ET_BTN_PRESSED:
                    ESP_LOGI(TAG, "Button pressed");
                    lvgl_encoder_state.physical_holding = true;
                    lvgl_encoder_state.latched_press = true;
                    break;
                case RE_ET_BTN_RELEASED:
                    ESP_LOGI(TAG, "Button released");
                    lvgl_encoder_state.physical_holding = false;
                    break;
                case RE_ET_BTN_CLICKED:
                    ESP_LOGI(TAG, "Button clicked");
                    break;
                case RE_ET_BTN_LONG_PRESSED:
                    ESP_LOGI(TAG, "Looooong pressed button");
                    break;
                case RE_ET_CHANGED:
                    lvgl_encoder_state.diff += e.diff;
                    ESP_LOGI(TAG, "Value = %" PRIi32, lvgl_encoder_state.diff);
                    break;
                default:
                    break;
            }
        }
        lv_tick_inc(10);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));  // wait 10 milliseconds
    }
}
