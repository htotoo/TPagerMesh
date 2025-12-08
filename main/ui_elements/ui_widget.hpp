#pragma once

#include "lvgl.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>

// --- Base Widget Class ---
class Widget {
   public:
    // 1. Generic Constructor (Creates a basic container object)
    Widget(Widget* parent = nullptr) {
        lv_obj_t* p = parent ? parent->get_lv_obj() : lv_scr_act();
        obj = lv_obj_create(p);
        remove_style_all();  // Basic widgets have no visual style by default
    }

    // 2. Destructor (Removes from screen)
    virtual ~Widget() {
        if (lv_obj_is_valid(obj)) {
            lv_obj_delete(obj);
        }
    }

    // Accessors
    lv_obj_t* get_lv_obj() const { return obj; }

    // --- Layout & Logic ---
    void set_visible(bool visible) {
        if (visible)
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }

    void set_disabled(bool disabled) {
        if (disabled)
            lv_obj_add_state(obj, LV_STATE_DISABLED);
        else
            lv_obj_remove_state(obj, LV_STATE_DISABLED);
    }

    // Size & Pos
    void set_size(int w, int h) { lv_obj_set_size(obj, w, h); }
    void set_width(int w) { lv_obj_set_width(obj, w); }
    void set_height(int h) { lv_obj_set_height(obj, h); }
    void set_pos(int x, int y) { lv_obj_set_pos(obj, x, y); }

    // Flex settings
    void set_flex_grow(uint8_t grow) { lv_obj_set_flex_grow(obj, grow); }
    void align(lv_align_t align, int x_ofs = 0, int y_ofs = 0) {
        lv_obj_align(obj, align, x_ofs, y_ofs);
    }

    // Styles
    void set_bg_color(lv_color_t color) {
        lv_obj_set_style_bg_color(obj, color, 0);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    }

    void set_border(int width, lv_color_t color) {
        lv_obj_set_style_border_width(obj, width, 0);
        lv_obj_set_style_border_color(obj, color, 0);
    }

    void set_padding(int val) {
        lv_obj_set_style_pad_all(obj, val, 0);
    }

    void add_to_group(lv_group_t* group) {
        if (group) lv_group_add_obj(group, obj);
    }

   protected:
    lv_obj_t* obj = nullptr;

    // 3. Protected Constructor for Subclasses
    // Allows subclasses (like Button) to create their specific object (lv_btn_create)
    // and pass it up, avoiding double-creation.
    Widget(lv_obj_t* _obj) : obj(_obj) {}

    void remove_style_all() { lv_obj_remove_style_all(obj); }
};

// --- Container (Layouts) ---
class Container : public Widget {
   public:
    Container(Widget* parent) : Widget(parent) {
        // Container defaults
        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    }

    // --- The Factory Method ---
    // 1. Creates C++ Object
    // 2. Enforces LVGL Parenting
    // 3. Stores pointer
    template <typename T, typename... Args>
    T* add(Args&&... args) {
        // Create the widget, passing 'this' as the parent
        auto widget = std::make_unique<T>(this, std::forward<Args>(args)...);
        T* raw_ptr = widget.get();

        // SAFETY NET: Ensure the LVGL object is actually parented to this container.
        // This fixes cases where the subclass constructor might have ignored the parent arg.
        if (lv_obj_get_parent(raw_ptr->get_lv_obj()) != this->obj) {
            lv_obj_set_parent(raw_ptr->get_lv_obj(), this->obj);
        }

        children.push_back(std::move(widget));
        return raw_ptr;
    }

    // Remove and destroy all children
    void clear() {
        children.clear();  // Destructors will call lv_obj_delete
    }

   protected:
    // Constructor for subclasses of Container (like FlexContainer)
    Container(lv_obj_t* _obj) : Widget(_obj) {}

    std::vector<std::unique_ptr<Widget>> children;
};

// --- Flex Layout ---
class FlexContainer : public Container {
   public:
    FlexContainer(Widget* parent, lv_flex_flow_t flow = LV_FLEX_FLOW_ROW)
        : Container(lv_obj_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        remove_style_all();  // Clean slate
        lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(obj, flow);
        lv_obj_set_style_pad_gap(obj, 5, 0);
    }

    void set_gap(int gap_px) { lv_obj_set_style_pad_gap(obj, gap_px, 0); }
    void set_flow(lv_flex_flow_t flow) { lv_obj_set_flex_flow(obj, flow); }
    void set_align(lv_flex_align_t main, lv_flex_align_t cross, lv_flex_align_t track) {
        lv_obj_set_flex_align(obj, main, cross, track);
    }
};

// --- Label Widget ---
class Label : public Widget {
   public:
    Label(Widget* parent, const std::string& text = "")
        : Widget(lv_label_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        lv_label_set_text(obj, text.c_str());
    }

    void set_text(const std::string& text) {
        lv_label_set_text(obj, text.c_str());
    }

    void set_text_color(lv_color_t color) {
        lv_obj_set_style_text_color(obj, color, 0);
    }
};

// --- Button Widget ---
class Button : public Widget {
   public:
    Button(Widget* parent, const std::string& text = "", std::function<void()> cb = nullptr)
        : Widget(lv_button_create(parent ? parent->get_lv_obj() : lv_scr_act())), callback(cb) {
        // Internal label for text
        label_obj = lv_label_create(obj);
        lv_label_set_text(label_obj, text.c_str());
        lv_obj_center(label_obj);

        // Bind callback
        lv_obj_set_user_data(obj, this);
        lv_obj_add_event_cb(obj, internal_event_handler, LV_EVENT_CLICKED, NULL);
    }

    void set_text(const std::string& text) {
        if (label_obj) lv_label_set_text(label_obj, text.c_str());
    }

    void set_callback(std::function<void()> cb) {
        callback = cb;
    }

   private:
    lv_obj_t* label_obj = nullptr;
    std::function<void()> callback;

    static void internal_event_handler(lv_event_t* e) {
        Button* btn = static_cast<Button*>(lv_obj_get_user_data(lv_event_get_target(e)));
        if (btn && btn->callback) {
            btn->callback();
        }
    }
};

// --- Dropdown Menu ---
class Dropdown : public Widget {
   public:
    Dropdown(Widget* parent) : Widget(nullptr) {
        lv_obj_t* par = parent ? parent->get_lv_obj() : lv_scr_act();
        obj = lv_dropdown_create(par);
        set_width(LV_PCT(100));
    }

    void set_options(const std::string& options) {
        // Format: "Option 1\nOption 2\nOption 3"
        lv_dropdown_set_options(obj, options.c_str());
    }

    void set_selected(uint16_t index) {
        lv_dropdown_set_selected(obj, index);
    }

    int get_selected() {
        return lv_dropdown_get_selected(obj);
    }

    // Get text of selected item
    std::string get_selected_str() {
        char buf[64];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        return std::string(buf);
    }
};

// --- Text Input Field ---
class TextInput : public Widget {
   public:
    TextInput(Widget* parent, const char* placeholder = "Type here...") : Widget(nullptr) {
        lv_obj_t* par = parent ? parent->get_lv_obj() : lv_scr_act();
        obj = lv_textarea_create(par);

        set_width(LV_PCT(100));
        set_height(40);  // Single line height usually
        lv_textarea_set_placeholder_text(obj, placeholder);
        lv_textarea_set_one_line(obj, true);

        // Style when focused (Visual feedback for typing)
        lv_obj_set_style_border_color(obj, lv_color_hex(0x007AFF), LV_STATE_FOCUSED);
    }

    std::string get_text() {
        return std::string(lv_textarea_get_text(obj));
    }

    void set_text(const std::string& text) {
        lv_textarea_set_text(obj, text.c_str());
    }

    // For Keypad: Add char
    void add_char(char c) {
        lv_textarea_add_char(obj, c);
    }

    // For Keypad: Backspace
    void backspace() {
        lv_textarea_del_char(obj);
    }
};

// --- Console / Log Viewer ---
class ConsoleLog : public Widget {
   public:
    ConsoleLog(Widget* parent) : Widget(nullptr) {
        lv_obj_t* par = parent ? parent->get_lv_obj() : lv_scr_act();
        obj = lv_textarea_create(par);

        set_size(LV_PCT(100), LV_PCT(100));
        lv_textarea_set_readonly(obj, true);
        lv_textarea_set_cursor_click_pos(obj, false);  // Disable cursor

        // Terminal Style
        set_bg_color(lv_color_hex(0x000000));
        lv_obj_set_style_text_color(obj, lv_color_hex(0x00FF00), 0);  // Green text
        lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, 0);   // Tiny font
    }

    void log(const std::string& text) {
        lv_textarea_add_text(obj, text.c_str());
        lv_textarea_add_char(obj, '\n');
    }

    void clear_log() {
        lv_textarea_set_text(obj, "");
    }
};

// --- Chat Message List ---
class MessageList : public FlexContainer {
   public:
    MessageList(Widget* parent) : FlexContainer(parent, LV_FLEX_FLOW_COLUMN) {
        set_width(LV_PCT(100));
        set_flex_grow(1);  // Fill space
        set_padding(5);
        set_gap(8);

        // Allow scrolling
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC);
        lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
    }

    void add_message(const std::string& text, bool is_me) {
        // 1. Create Bubble Container
        auto bubble = add<Container>(nullptr);  // Parent is 'this' via factory
        bubble->set_width(LV_SIZE_CONTENT);
        // Max width 80% of screen
        lv_obj_set_style_max_width(bubble->get_lv_obj(), lv_pct(85), 0);

        bubble->set_padding(8);
        lv_obj_set_style_radius(bubble->get_lv_obj(), 10, 0);  // Round corners

        // 2. Style based on sender
        if (is_me) {
            // My messages: Right aligned, Blue
            lv_obj_align(bubble->get_lv_obj(), LV_ALIGN_TOP_RIGHT, 0, 0);  // Alignment in flex row? No, in column
            // In a Flex Column, we use align_self or just generic object alignment?
            // LVGL Flex Column aligns children based on cross-axis.
            // We need to set "align-self" essentially.
            lv_obj_set_align(bubble->get_lv_obj(), LV_ALIGN_TOP_RIGHT);
            bubble->set_bg_color(lv_color_hex(0x007AFF));  // iOS Blue
        } else {
            // Their messages: Left aligned, Gray
            lv_obj_set_align(bubble->get_lv_obj(), LV_ALIGN_TOP_LEFT);
            bubble->set_bg_color(lv_color_hex(0x444444));
        }

        // 3. Add Text Label
        auto lbl = bubble->add<Label>(text);
        lbl->set_text_color(lv_color_hex(0xFFFFFF));
        lv_label_set_long_mode(lbl->get_lv_obj(), LV_LABEL_LONG_WRAP);  // Auto wrap text
        lv_obj_set_width(lbl->get_lv_obj(), LV_PCT(100));               // Fill bubble

        // 4. Auto Scroll to Bottom
        // We need to wait for layout update or force it
        lv_obj_update_layout(obj);
        lv_obj_scroll_to_view(bubble->get_lv_obj(), LV_ANIM_ON);
    }
};