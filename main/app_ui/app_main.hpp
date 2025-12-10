#include "ui_elements/ui_widget.hpp"
#include "drivers/keypad_irq.hpp"
#include "message_store.hpp"

LV_FONT_DECLARE(font_montserrat_10_hun);
LV_FONT_DECLARE(font_montserrat_12_hun);

class App_Main {
   public:
    App_Main() {}
    ~App_Main() {}

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

        // 2. Root Container (Clean Dark Background)
        root_col = std::make_unique<FlexContainer>(nullptr, LV_FLEX_FLOW_COLUMN);
        root_col->set_size(LV_PCT(100), LV_PCT(100));
        root_col->set_bg_color(lv_color_hex(0x000000));
        root_col->set_gap(0);

        // 3. Status Bar (Top, 18px, Dark Gray)
        status_bar = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        status_bar->set_size(LV_PCT(100), 18);
        status_bar->set_bg_color(lv_color_hex(0x000000));

        status_bar->set_align(LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        status_bar->set_padding(4);

        // Title
        auto title = status_bar->add<Label>("TMesh");
        title->set_bg_color(lv_color_hex(0x000000));

        // Clock
        auto time_lbl = status_bar->add<Label>("12:00");

        // 4. Body Row (Holds Menu + Content)
        body_row = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        body_row->set_width(LV_PCT(100));
        body_row->set_flex_grow(1);
        body_row->set_gap(1);  // 1px separator line effect via background

        // 5. Side Menu (Left, 32px)
        side_menu = body_row->add<FlexContainer>(LV_FLEX_FLOW_COLUMN);
        side_menu->set_width(32);
        side_menu->set_height(LV_PCT(100));
        side_menu->set_bg_color(lv_color_hex(0x222222));
        side_menu->set_padding(2);
        side_menu->set_gap(6);
        side_menu->set_default_group(group_menu.get());

        // 6. Content Area (Right, fills rest)
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

    void toggle_focus_group() {
        lv_indev_t* kp = KeypadDriver::get_indev();
        lv_group_t* curr_g = lv_indev_get_group(kp);

        // Reset editing state on the old group before switching
        if (curr_g) lv_group_set_editing(curr_g, false);

        if (curr_g == group_menu->get_handle()) {
            ESP_LOGI("UI", "Focus -> APP");

            // 1. Attach Input Device to App Group
            group_app->attach_to_indev(kp);
            if (encoder_indev) group_app->attach_to_indev(encoder_indev);

            // 2. Visuals
            side_menu->set_border(0, lv_color_hex(0x000000));
            content_area->set_border(1, lv_color_hex(0x007AFF));

            // 3. FORCE EDIT MODE
            lv_group_set_editing(group_app->get_handle(), true);

        } else {
            ESP_LOGI("UI", "Focus -> MENU");

            // 1. Attach Input Device to Menu Group
            group_menu->attach_to_indev(kp);
            if (encoder_indev) group_menu->attach_to_indev(encoder_indev);

            // 2. Visuals
            side_menu->set_border(1, lv_color_hex(0x007AFF));
            content_area->set_border(0, lv_color_hex(0xFF0000));

            // 3. Reset focus to first button
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

        // Initial State
        group_menu->attach_to_indev(KeypadDriver::get_indev());
        if (encoder_indev) group_menu->attach_to_indev(encoder_indev);
        group_menu->focus_obj(btn_msg->get_lv_obj());
    }

    void load_messaging_app() {
        content_area->clear();

        // 1. Chat History List (Fills all remaining space)
        chat_history = content_area->add<MessageList>();
        chat_history->set_flex_grow(1);
        chat_history->set_width(LV_PCT(100));

        // CRITICAL FIX: Disable clicking on the list itself so it is skipped by navigation
        lv_obj_remove_flag(chat_history->get_lv_obj(), LV_OBJ_FLAG_CLICKABLE);

        // Add dummy data
        // chat_history->add_message("Welcome to TMesh!", false);
        // chat_history->add_message("System Online.", false);

        // 2. Text Input (Directly in content_area, aligned to bottom)
        auto input = content_area->add<TextInput>("Message...");
        input->set_width(LV_PCT(100));
        input->set_height(40);    // Fixed height for input area
        input->set_flex_grow(0);  // Do not grow, stay fixed

        // Style: Add a top border to separate it from chat
        lv_obj_set_style_border_width(input->get_lv_obj(), 2, 0);
        lv_obj_set_style_border_side(input->get_lv_obj(), LV_BORDER_SIDE_TOP, 0);

        // --- CRITICAL FIX: Manually Add to Group ---
        // Since content_area might have mixed children, we ensure input is 100% in the group.
        input->add_to_group(group_app.get());

        // Send Callback
        input->set_on_submit([this, input](std::string text) {
            if (text.empty()) return;
            // if (chat_history) chat_history->add_message(text, true);
            input->set_text("");

            // Keep focus on input after sending
            // (Optional, LVGL often keeps it anyway, but this is safe)
            lv_obj_send_event(input->get_lv_obj(), LV_EVENT_CLICKED, NULL);
        });
    }

    void set_message_store(MessageStore* store) {
        message_store = store;
        if (message_store) {
            message_store->addListener([this](const MessageStore::MessageEntry& entry) {
                if (chat_history) {
                    chat_history->add_message(entry);
                }
            });
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

    // Keep reference to chat history to add messages dynamically
    MessageList* chat_history = nullptr;
    lv_indev_t* encoder_indev = nullptr;

    // helpers
    MessageStore* message_store = nullptr;
};