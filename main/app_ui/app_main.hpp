#include "ui_elements/ui_widget.hpp"
#include "drivers/keypad_irq.hpp"
#include "message_store.hpp"

LV_FONT_DECLARE(font_montserrat_10_hun);
LV_FONT_DECLARE(font_montserrat_12_hun);

class App_Main {
   public:
    App_Main() {}
    ~App_Main() {}
    using SendMessageCallback = std::function<void(const std::string&)>;

    void set_on_send_message(SendMessageCallback cb) {
        on_send_cb = cb;
    }

    void init(lv_indev_t* enc_indev, lv_indev_t* keypad_indev) {
        ESP_LOGI("UI", "Initializing UI...");
        static lv_style_t style_global_font;
        lv_style_init(&style_global_font);
        lv_style_set_text_font(&style_global_font, &font_montserrat_12_hun);
        lv_obj_t* screen = lv_scr_act();
        lv_obj_add_style(screen, &style_global_font, LV_PART_MAIN);
        encoder_indev = enc_indev;

        // 1. Create Groups
        group_menu = std::make_unique<Group>();
        group_app = std::make_unique<Group>();

        // 2. Root Container
        root_col = std::make_unique<FlexContainer>(nullptr, LV_FLEX_FLOW_COLUMN);
        root_col->set_size(LV_PCT(100), LV_PCT(100));
        root_col->set_bg_color(lv_color_hex(0x000000));
        root_col->set_gap(0);

        // 3. Status Bar
        status_bar = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        status_bar->set_size(LV_PCT(100), 18);
        status_bar->set_bg_color(lv_color_hex(0x000000));
        status_bar->set_align(LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        status_bar->set_padding(4);
        status_bar->set_flex_grow(0);

        // --- Status Bar Left: Title + Subtitle ---
        auto left_area = status_bar->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        left_area->set_gap(2);
        left_area->set_height(18);

        // Title
        auto title = left_area->add<Label>("TMesh");
        title->set_text_color(lv_color_hex(0xFFFFFF));
        title->set_bg_color(lv_color_hex(0x000000));

        // Dynamic Subtitle
        lbl_subtitle = left_area->add<Label>("");
        lbl_subtitle->set_text_color(lv_color_hex(0xAAAAAA));  // Grey color

        // --- Status Bar Right: Battery + Time ---
        auto right_area = status_bar->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        right_area->set_gap(8);  // Space between Battery and Time
        right_area->set_height(18);

        // Battery
        lbl_battery = right_area->add<Label>("0%");
        lbl_battery->set_text_color(lv_color_hex(0xFFFFFF));

        // Clock
        time_lbl = right_area->add<Label>("12:00");
        time_lbl->set_text_color(lv_color_hex(0xFFFFFF));

        // 4. Body Row
        body_row = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        body_row->set_width(LV_PCT(100));
        body_row->set_flex_grow(1);
        body_row->set_gap(1);

        // 5. Side Menu
        side_menu = body_row->add<FlexContainer>(LV_FLEX_FLOW_COLUMN);
        side_menu->set_width(32);
        side_menu->set_height(LV_PCT(100));
        side_menu->set_bg_color(lv_color_hex(0x222222));
        side_menu->set_padding(2);
        side_menu->set_gap(6);
        side_menu->set_default_group(group_menu.get());

        // 6. Content Area
        content_area = body_row->add<FlexContainer>(LV_FLEX_FLOW_COLUMN);
        content_area->set_height(LV_PCT(100));
        content_area->set_flex_grow(1);
        content_area->set_bg_color(lv_color_hex(0x000000));
        content_area->set_default_group(group_app.get());

        // 7. Start App
        build_menu();
        load_messaging_app();

        ESP_LOGI("UI", "UI Init Complete.");
    }

    void set_title_info(const std::string& text) {
        if (lbl_subtitle) {
            if (text.empty()) {
                lbl_subtitle->set_text("");
            } else {
                lbl_subtitle->set_text("- " + text);
            }
        }
    }

    void set_battery_status(uint8_t percent, bool charging) {
        if (lbl_battery) {
            std::string bat_txt;
            if (charging) {
                bat_txt = "Chg " + std::to_string(percent) + "%";
                lbl_battery->set_text_color(lv_color_hex(0x00FF00));  // Green when charging
            } else {
                bat_txt = std::to_string(percent) + "%";
                if (percent < 20)
                    lbl_battery->set_text_color(lv_color_hex(0xFF0000));  // Red
                else
                    lbl_battery->set_text_color(lv_color_hex(0xFFFFFF));  // White
            }
            lbl_battery->set_text(bat_txt);
        }
    }

    void set_time(const std::string& time_str) {
        if (time_lbl) {
            time_lbl->set_text(time_str);
        }
    }

    void toggle_focus_group() {
        lv_indev_t* kp = KeypadDriver::get_indev();
        lv_group_t* curr_g = lv_indev_get_group(kp);

        if (curr_g) lv_group_set_editing(curr_g, false);

        if (curr_g == group_menu->get_handle()) {
            ESP_LOGI("UI", "Focus -> APP");
            group_app->attach_to_indev(kp);
            if (encoder_indev) group_app->attach_to_indev(encoder_indev);

            side_menu->set_border(0, lv_color_hex(0x000000));
            content_area->set_border(1, lv_color_hex(0x007AFF));

            // --- FOCUS FIX ---
            // If we have a stored input widget, force focus onto it
            if (active_input_widget) {
                lv_group_focus_obj(active_input_widget->get_lv_obj());
            }

            // Force editing mode so text input works immediately
            lv_group_set_editing(group_app->get_handle(), true);

        } else {
            ESP_LOGI("UI", "Focus -> MENU");
            group_menu->attach_to_indev(kp);
            if (encoder_indev) group_menu->attach_to_indev(encoder_indev);

            side_menu->set_border(1, lv_color_hex(0x007AFF));
            content_area->set_border(0, lv_color_hex(0xFF0000));

            lv_obj_t* target = lv_group_get_obj_by_index(group_menu->get_handle(), 0);
            if (target) lv_group_focus_obj(target);
        }
    }

    void build_menu() {
        auto btn_msg = side_menu->add<Button>("M");
        btn_msg->set_size(28, 28);
        btn_msg->set_padding(0);
        btn_msg->set_callback([this]() { load_messaging_app(); });
        btn_msg->set_bg_color(lv_color_hex(0xFF0000));

        auto btn_set = side_menu->add<Button>("S");
        btn_set->set_size(28, 28);
        btn_set->set_padding(0);
        btn_set->set_callback([]() { ESP_LOGI("UI", "Settings clicked"); });
        btn_set->set_bg_color(lv_color_hex(0x0000FF));

        group_menu->attach_to_indev(KeypadDriver::get_indev());
        if (encoder_indev) group_menu->attach_to_indev(encoder_indev);
        group_menu->focus_obj(btn_msg->get_lv_obj());
    }

    void load_messaging_app() {
        // Clear previous widgets and reset pointer
        content_area->clear();
        group_app->remove_all_objs();
        active_input_widget = nullptr;
        set_title_info("Hungary");  // Demo title

        // 1. Chat History
        chat_history = content_area->add<MessageList>();
        chat_history->set_flex_grow(1);
        chat_history->set_width(LV_PCT(100));
        lv_obj_remove_flag(chat_history->get_lv_obj(), LV_OBJ_FLAG_CLICKABLE);

        // 2. Text Input
        auto input = content_area->add<TextInput>("Message...");
        input->set_width(LV_PCT(100));
        input->set_height(40);
        input->set_flex_grow(0);
        input->set_scroll_target(chat_history);
        lv_obj_set_style_border_width(input->get_lv_obj(), 2, 0);
        lv_obj_set_style_border_side(input->get_lv_obj(), LV_BORDER_SIDE_TOP, 0);

        // Manually Add to Group (explicitly)
        input->add_to_group(group_app.get());

        // Save reference for focus toggling
        active_input_widget = input;

        input->set_on_submit([this, input](std::string text) {
            if (text.empty()) return;
            // Handle send...
            if (on_send_cb) {
                on_send_cb(text);
                if (message_store) message_store->addMessage(MessageStore::MessageEntry{
                    .sender = "Me",
                    .channel = 0,
                    .isDirect = false,
                    .message = text.c_str(),
                    .isFromMe = true,
                    .time = std::time(nullptr),
                });
            }
            input->set_text("");
            lv_obj_send_event(input->get_lv_obj(), LV_EVENT_CLICKED, NULL);
        });
        input->set_on_longclick([this]() {
            ESP_LOGI("UI", "Input long-clicked");
            // should show channel selector here
        });
        // load older messages from store
        if (message_store) {
            message_store->traverseHistory([this](const MessageStore::MessageEntry& entry) {
                if (chat_history) {
                    chat_history->add_message(entry, false);
                }
                return true;  // Continue traversal
            });
        }
        lv_obj_update_layout(content_area->get_lv_obj());
        if (chat_history) {
            chat_history->scroll_to_bottom();
        }
    }

    void set_message_store(MessageStore* store) {
        if (message_store == store) return;
        message_store = store;
    }

    void on_new_message(const MessageStore::MessageEntry& msg) {
        if (chat_history) {
            chat_history->add_message(msg);
            chat_history->scroll_to_bottom();
        }
    }

   private:
    std::unique_ptr<Group> group_menu;
    std::unique_ptr<Group> group_app;
    std::unique_ptr<FlexContainer> root_col;

    FlexContainer* status_bar = nullptr;
    FlexContainer* body_row = nullptr;
    FlexContainer* side_menu = nullptr;
    FlexContainer* content_area = nullptr;

    // New labels
    Label* lbl_subtitle = nullptr;
    Label* lbl_battery = nullptr;
    Label* time_lbl = nullptr;

    MessageList* chat_history = nullptr;
    lv_indev_t* encoder_indev = nullptr;
    MessageStore* message_store = nullptr;

    // Track active input for focus handling
    TextInput* active_input_widget = nullptr;

    SendMessageCallback on_send_cb = nullptr;
};