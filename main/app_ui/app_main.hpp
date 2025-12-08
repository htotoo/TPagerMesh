#include "ui_elements/ui_widget.hpp"
#include "drivers/keypad_irq.hpp"  // Ensure this is included for KeypadDriver

class App_Main {
   public:
    App_Main() {}
    ~App_Main() {}

    // Pass the encoder driver handle here so we can manage it
    void init(lv_indev_t* enc_indev) {
        encoder_indev = enc_indev;

        ESP_LOGI("UI", "Initializing UI...");

        // 1. Create Groups
        group_menu = std::make_unique<Group>();
        group_app = std::make_unique<Group>();

        // 2. Root Container (Red background for debugging!)
        root_col = std::make_unique<FlexContainer>(nullptr, LV_FLEX_FLOW_COLUMN);
        root_col->set_size(LV_PCT(100), LV_PCT(100));
        root_col->set_bg_color(lv_color_hex(0xFF0000));  // RED DEBUG

        // 3. Status Bar
        status_bar = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        status_bar->set_size(LV_PCT(100), 20);
        status_bar->set_bg_color(lv_color_hex(0x202020));  // Dark Gray

        auto time_lbl = status_bar->add<Label>("12:00");
        time_lbl->set_text_color(lv_color_hex(0xFFFFFF));
        status_bar->set_align(LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        // 4. Body Row
        body_row = root_col->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        body_row->set_width(LV_PCT(100));
        body_row->set_flex_grow(1);

        // 5. Side Menu
        side_menu = body_row->add<FlexContainer>(LV_FLEX_FLOW_COLUMN);
        side_menu->set_width(30);
        side_menu->set_height(LV_PCT(100));
        side_menu->set_bg_color(lv_color_hex(0x404040));  // Lighter Gray
        side_menu->set_default_group(group_menu.get());

        // 6. Content Area
        content_area = body_row->add<FlexContainer>(LV_FLEX_FLOW_COLUMN);
        content_area->set_height(LV_PCT(100));
        content_area->set_flex_grow(1);
        content_area->set_bg_color(lv_color_hex(0x000000));  // Black
        content_area->set_default_group(group_app.get());

        // 7. Populate
        build_menu();
        load_messaging_app();

        // 8. Register Global Key Event for Group Switching
        // FIX: Use captureless lambda and pass 'this' as user_data
        lv_indev_add_event_cb(KeypadDriver::get_indev(), [](lv_event_t* e) {
            App_Main* self = (App_Main*)lv_event_get_user_data(e);
            uint32_t key = lv_indev_get_key(lv_indev_get_act());
            
            // ID 21 is mapped to LV_KEY_NEXT in keypad driver
            if (key == LV_KEY_NEXT) { 
                self->toggle_focus_group();
            } }, LV_EVENT_KEY, this);

        ESP_LOGI("UI", "UI Init Complete.");
    }

    void toggle_focus_group() {
        lv_indev_t* kp = KeypadDriver::get_indev();
        lv_group_t* curr = lv_indev_get_group(kp);

        // Safety check for encoder
        if (!encoder_indev) ESP_LOGE("UI", "Encoder Indev is NULL! Check init()");

        if (curr == group_menu->get_handle()) {
            ESP_LOGI("UI", "Switching Focus -> APP");

            // 1. Assign Inputs
            group_app->attach_to_indev(kp);
            if (encoder_indev) group_app->attach_to_indev(encoder_indev);

            // 2. Visuals
            side_menu->set_border(0, lv_color_hex(0x000000));
            content_area->set_border(2, lv_color_hex(0x007AFF));

            // 3. FORCE FOCUS (Crucial Fix)
            // If the group has widgets, focus the first one (usually input or console)
            // We use lv_group_get_obj_by_index to find a valid target
            lv_obj_t* target = lv_group_get_obj_by_index(group_app->get_handle(), 0);
            if (target) lv_group_focus_obj(target);

        } else {
            ESP_LOGI("UI", "Switching Focus -> MENU");

            // 1. Assign Inputs
            group_menu->attach_to_indev(kp);
            if (encoder_indev) group_menu->attach_to_indev(encoder_indev);

            // 2. Visuals
            side_menu->set_border(2, lv_color_hex(0x007AFF));
            content_area->set_border(0, lv_color_hex(0x000000));

            // 3. FORCE FOCUS (Crucial Fix)
            // Focus the first button in the menu (e.g. "M")
            lv_obj_t* target = lv_group_get_obj_by_index(group_menu->get_handle(), 0);
            if (target) lv_group_focus_obj(target);
        }
    }

    void build_menu() {
        auto btn_msg = side_menu->add<Button>("M");
        btn_msg->set_size(16, 16);
        btn_msg->set_padding(0);
        btn_msg->set_callback([this]() {
            load_messaging_app();
        });

        auto btn_set = side_menu->add<Button>("S");
        btn_set->set_size(16, 16);
        btn_set->set_padding(0);
        btn_set->set_callback([]() {
            ESP_LOGI("UI", "Settings clicked");
        });

        // Startup Focus -> Menu
        group_menu->attach_to_indev(KeypadDriver::get_indev());
        if (encoder_indev) group_menu->attach_to_indev(encoder_indev);

        group_menu->focus_obj(btn_msg->get_lv_obj());
    }

    void load_messaging_app() {
        content_area->clear();

        // Auto-switch focus to App when loading it
        group_app->attach_to_indev(KeypadDriver::get_indev());
        if (encoder_indev) group_app->attach_to_indev(encoder_indev);

        // Header
        auto top_bar = content_area->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        top_bar->set_width(LV_PCT(100));
        top_bar->set_height(20);
        top_bar->set_bg_color(lv_color_hex(0x000055));
        top_bar->set_align(LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        top_bar->add<Label>("Messaging");

        // Console
        auto console = content_area->add<ConsoleLog>(1024);
        console->set_width(LV_PCT(100));
        console->set_flex_grow(1);
        console->log("Ready.");

        // Input
        auto input_row = content_area->add<FlexContainer>(LV_FLEX_FLOW_ROW);
        input_row->set_width(LV_PCT(100));
        input_row->set_height(30);
        input_row->set_padding(2);

        auto input = input_row->add<TextInput>("Type...");
        input->set_flex_grow(1);

        input->set_on_submit([console, input](std::string text) {
            if (text.empty()) return;
            console->log("[Me] " + text);
            input->set_text("");
        });

        group_app->focus_obj(input->get_lv_obj());
    }

   private:
    std::unique_ptr<Group> group_menu;
    std::unique_ptr<Group> group_app;
    std::unique_ptr<FlexContainer> root_col;

    FlexContainer* status_bar = nullptr;
    FlexContainer* body_row = nullptr;
    FlexContainer* side_menu = nullptr;
    FlexContainer* content_area = nullptr;

    lv_indev_t* encoder_indev = nullptr;
};