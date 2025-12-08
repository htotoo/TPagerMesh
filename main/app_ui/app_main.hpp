#include "ui_elements/ui_widget.hpp"

class App_Main {
   public:
    App_Main() {}
    ~App_Main() {}

    void init() {
        ESP_LOGI("UI", "Initializing UI...");

        /* // 1. Create Groups
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
         build_menu();*/

        lv_obj_t* scr = lv_scr_act();
        if (scr == nullptr) {
            ESP_LOGE("UI", "Failed to get active screen!");
            return;
        }
        // 2. Set its background color to Black
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFF00), LV_PART_MAIN);

        // --- Circle 1 (Left Half) ---
        lv_obj_t* c1 = lv_obj_create(scr);

        // Size: Half the width (420/2 = 210).
        // This fits within the 222 height comfortably.
        lv_obj_set_size(c1, 210, 210);

        // Make it a circle
        lv_obj_set_style_radius(c1, LV_RADIUS_CIRCLE, 0);

        // Color: White, Remove Border
        lv_obj_set_style_bg_color(c1, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(c1, 0, 0);

        // Position: Left Middle
        lv_obj_align(c1, LV_ALIGN_LEFT_MID, 0, 0);

        // Remove scrollbars (cleaner look)
        lv_obj_remove_flag(c1, LV_OBJ_FLAG_SCROLLABLE);

        // --- Circle 2 (Right Half) ---
        lv_obj_t* c2 = lv_obj_create(scr);

        lv_obj_set_size(c2, 210, 210);
        lv_obj_set_style_radius(c2, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_color(c2, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_width(c2, 0, 0);

        // Position: Right Middle
        lv_obj_align(c2, LV_ALIGN_RIGHT_MID, 0, 0);

        lv_obj_remove_flag(c2, LV_OBJ_FLAG_SCROLLABLE);

        // 3. Force an immediate redraw so it appears instantly
        // lv_refr_now(NULL);

        ESP_LOGI("UI", "UI Init Complete.");
    }

    void build_menu() {
        // Add simple buttons to test
        auto btn1 = side_menu->add<Button>("M");
        btn1->set_size(24, 24);
        btn1->set_callback([this]() {
            ESP_LOGI("UI", "Menu Clicked");
            // Add logic here later
        });

        group_menu->attach_to_indev(KeypadDriver::get_indev());
        group_menu->focus_obj(btn1->get_lv_obj());
    }

   private:
    std::unique_ptr<Group> group_menu;
    std::unique_ptr<Group> group_app;
    std::unique_ptr<FlexContainer> root_col;
    FlexContainer* status_bar = nullptr;
    FlexContainer* body_row = nullptr;
    FlexContainer* side_menu = nullptr;
    FlexContainer* content_area = nullptr;
};