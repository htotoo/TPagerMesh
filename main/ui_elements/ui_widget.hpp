#pragma once

#include "lvgl.h"
#include "esp_log.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

static const char* UI_TAG = "UI_WIDGET";

// --- Group Wrapper (RAII) ---
class Group {
   public:
    Group() { handle = lv_group_create(); }
    virtual ~Group() {
        if (handle) {
            lv_group_delete(handle);
            handle = nullptr;
        }
    }
    lv_group_t* get_handle() const { return handle; }
    void add_obj(lv_obj_t* obj) { lv_group_add_obj(handle, obj); }
    void focus_obj(lv_obj_t* obj) { lv_group_focus_obj(obj); }
    void attach_to_indev(lv_indev_t* indev) { lv_indev_set_group(indev, handle); }
    void set_editing(bool edit) { lv_group_set_editing(handle, edit); }

   private:
    lv_group_t* handle = nullptr;
};

// --- Base Widget Class ---
class Widget {
   public:
    Widget(Widget* parent = nullptr) {
        lv_obj_t* p = parent ? parent->get_lv_obj() : lv_scr_act();
        obj = lv_obj_create(p);
        // Note: We leave default styles alone so widgets look correct
    }

    virtual ~Widget() {
        if (lv_obj_is_valid(obj)) lv_obj_delete(obj);
    }

    lv_obj_t* get_lv_obj() const { return obj; }

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

    void set_size(int w, int h) { lv_obj_set_size(obj, w, h); }
    void set_width(int w) { lv_obj_set_width(obj, w); }
    void set_height(int h) { lv_obj_set_height(obj, h); }
    void set_pos(int x, int y) { lv_obj_set_pos(obj, x, y); }
    void set_flex_grow(uint8_t grow) { lv_obj_set_flex_grow(obj, grow); }

    void align(lv_align_t align, int x_ofs = 0, int y_ofs = 0) {
        lv_obj_align(obj, align, x_ofs, y_ofs);
    }
    void set_align(lv_align_t align) { lv_obj_set_align(obj, align); }

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
    void add_to_group(Group* group) {
        if (group) lv_group_add_obj(group->get_handle(), obj);
    }

   protected:
    lv_obj_t* obj = nullptr;
    Widget(lv_obj_t* _obj) : obj(_obj) {}
    void remove_style_all() { lv_obj_remove_style_all(obj); }
};

// --- Container ---
class Container : public Widget {
   public:
    Container(Widget* parent) : Widget(parent) {
        remove_style_all();
        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    }

    template <typename T, typename... Args>
    T* add(Args&&... args) {
        auto widget = std::make_unique<T>(this, std::forward<Args>(args)...);
        T* raw_ptr = widget.get();

        if (lv_obj_get_parent(raw_ptr->get_lv_obj()) != this->obj) {
            lv_obj_set_parent(raw_ptr->get_lv_obj(), this->obj);
        }

        // CRITICAL FIX: Only add to group if the widget is interactive!
        // This prevents Labels and Bubbles from stealing focus.
        if (default_group) {
            if (lv_obj_has_flag(raw_ptr->get_lv_obj(), LV_OBJ_FLAG_CLICKABLE)) {
                raw_ptr->add_to_group(default_group);
            }
        }

        children.push_back(std::move(widget));
        return raw_ptr;
    }

    void clear() { children.clear(); }
    void set_default_group(Group* g) { default_group = g ? g->get_handle() : nullptr; }

   protected:
    Container(lv_obj_t* _obj) : Widget(_obj) { remove_style_all(); }
    std::vector<std::unique_ptr<Widget>> children;
    lv_group_t* default_group = nullptr;
};

// --- Flex Layout ---
class FlexContainer : public Container {
   public:
    FlexContainer(Widget* parent, lv_flex_flow_t flow = LV_FLEX_FLOW_ROW)
        : Container(lv_obj_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(obj, flow);
        lv_obj_set_style_pad_all(obj, 0, 0);
        lv_obj_set_style_pad_gap(obj, 0, 0);
    }
    void set_gap(int gap_px) { lv_obj_set_style_pad_gap(obj, gap_px, 0); }
    void set_flow(lv_flex_flow_t flow) { lv_obj_set_flex_flow(obj, flow); }
    void set_align(lv_flex_align_t main, lv_flex_align_t cross, lv_flex_align_t track) {
        lv_obj_set_flex_align(obj, main, cross, track);
    }
};

// --- Label ---
class Label : public Widget {
   public:
    Label(Widget* parent, const std::string& text = "")
        : Widget(lv_label_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        lv_label_set_text(obj, text.c_str());
    }
    void set_text(const std::string& text) { lv_label_set_text(obj, text.c_str()); }
    void set_text_color(lv_color_t color) { lv_obj_set_style_text_color(obj, color, 0); }
    void set_long_mode(lv_label_long_mode_t mode) { lv_label_set_long_mode(obj, mode); }
};

// --- Button ---
class Button : public Widget {
   public:
    Button(Widget* parent, const std::string& text = "", std::function<void()> cb = nullptr)
        : Widget(lv_button_create(parent ? parent->get_lv_obj() : lv_scr_act())), callback(cb) {
        label_obj = lv_label_create(obj);
        lv_label_set_text(label_obj, text.c_str());
        lv_obj_center(label_obj);

        lv_obj_set_user_data(obj, this);
        lv_obj_add_event_cb(obj, internal_event_handler, LV_EVENT_CLICKED, NULL);
    }
    void set_text(const std::string& text) {
        if (label_obj) lv_label_set_text(label_obj, text.c_str());
    }
    void set_callback(std::function<void()> cb) { callback = cb; }

   private:
    lv_obj_t* label_obj = nullptr;
    std::function<void()> callback;
    static void internal_event_handler(lv_event_t* e) {
        Button* btn = static_cast<Button*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
        if (btn && btn->callback) btn->callback();
    }
};

// --- Image Button ---
class ImageButton : public Widget {
   public:
    ImageButton(Widget* parent, std::function<void()> cb = nullptr)
        : Widget(lv_imagebutton_create(parent ? parent->get_lv_obj() : lv_scr_act())), callback(cb) {
        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_user_data(obj, this);
        lv_obj_add_event_cb(obj, internal_event_handler, LV_EVENT_CLICKED, NULL);
    }
    void set_src_all(const void* src) {
        lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, src, NULL, NULL);
        lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_PRESSED, src, NULL, NULL);
    }
    void set_callback(std::function<void()> cb) { callback = cb; }

   private:
    std::function<void()> callback;
    static void internal_event_handler(lv_event_t* e) {
        ImageButton* btn = static_cast<ImageButton*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
        if (btn && btn->callback) btn->callback();
    }
};

// --- Dropdown ---
class Dropdown : public Widget {
   public:
    Dropdown(Widget* parent)
        : Widget(lv_dropdown_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        set_width(LV_PCT(100));
    }
    void set_options(const std::string& opts) { lv_dropdown_set_options(obj, opts.c_str()); }
    int get_selected() { return lv_dropdown_get_selected(obj); }
    void set_selected(uint16_t id) { lv_dropdown_set_selected(obj, id); }
};

// --- Progress Bar ---
class ProgressBar : public Widget {
   public:
    ProgressBar(Widget* parent, int min = 0, int max = 100)
        : Widget(lv_bar_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        lv_bar_set_range(obj, min, max);
        set_size(LV_PCT(100), 10);
    }
    void set_value(int val, bool anim = true) { lv_bar_set_value(obj, val, anim ? LV_ANIM_ON : LV_ANIM_OFF); }
    void set_color(lv_color_t color) { lv_obj_set_style_bg_color(obj, color, LV_PART_INDICATOR); }
};

// --- Text Input ---
class TextInput : public Widget {
   public:
    TextInput(Widget* parent, const char* placeholder = "")
        : Widget(lv_textarea_create(parent ? parent->get_lv_obj() : lv_scr_act())) {
        set_width(LV_PCT(100));
        set_height(40);
        lv_textarea_set_placeholder_text(obj, placeholder);
        lv_textarea_set_one_line(obj, true);

        lv_obj_set_style_border_color(obj, lv_color_hex(0x007AFF), LV_STATE_FOCUSED);
        lv_obj_set_style_border_width(obj, 2, LV_STATE_FOCUSED);

        lv_obj_set_user_data(obj, this);
        lv_obj_add_event_cb(obj, internal_event_handler, LV_EVENT_READY, NULL);
    }
    void set_on_submit(std::function<void(std::string)> cb) { on_submit = cb; }
    std::string get_text() { return std::string(lv_textarea_get_text(obj)); }
    void set_text(const std::string& text) { lv_textarea_set_text(obj, text.c_str()); }

   private:
    std::function<void(std::string)> on_submit;
    static void internal_event_handler(lv_event_t* e) {
        TextInput* self = static_cast<TextInput*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
        if (self && self->on_submit) self->on_submit(self->get_text());
    }
};

// --- Console Log ---
class ConsoleLog : public Widget {
   public:
    ConsoleLog(Widget* parent, uint32_t buffer_size = 512)
        : Widget(lv_textarea_create(parent ? parent->get_lv_obj() : lv_scr_act())), max_len(buffer_size) {
        set_size(LV_PCT(100), LV_PCT(100));

        // Disable interaction so it doesn't get added to input group (checked by flag)
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        lv_textarea_set_cursor_click_pos(obj, false);

        set_bg_color(lv_color_hex(0x000000));
        lv_obj_set_style_text_color(obj, lv_color_hex(0x00FF00), 0);
        lv_obj_set_style_text_font(obj, lv_font_get_default(), 0);
    }
    void log(const std::string& text) {
        lv_textarea_add_text(obj, text.c_str());
        lv_textarea_add_char(obj, '\n');

        // Rolling buffer safety
        const char* txt = lv_textarea_get_text(obj);
        if (txt) {
            size_t len = strlen(txt);
            if (len > max_len) {
                lv_textarea_set_text(obj, txt + (len - max_len));
                lv_textarea_set_cursor_pos(obj, LV_TEXTAREA_CURSOR_LAST);
            }
        }
    }
    void clear_log() { lv_textarea_set_text(obj, ""); }

   private:
    uint32_t max_len;
};

// --- Message List ---
class MessageList : public FlexContainer {
   public:
    MessageList(Widget* parent) : FlexContainer(parent, LV_FLEX_FLOW_COLUMN) {
        set_width(LV_PCT(100));
        set_flex_grow(1);
        set_padding(5);
        set_gap(8);
        // Important: MessageList itself is NOT interactive, so it won't be focused.
        // The children (Bubbles) are containers, also not interactive.
        // This is perfect: Focus stays on the Input Box.
    }
    void add_message(const std::string& text, bool is_me) {
        auto bubble = add<Container>();
        // 1. Bubble grows with text, but stops at 85% of screen
        lv_obj_set_width(bubble->get_lv_obj(), LV_SIZE_CONTENT);
        lv_obj_set_style_max_width(bubble->get_lv_obj(), lv_pct(85), 0);

        bubble->set_padding(8);
        lv_obj_set_style_radius(bubble->get_lv_obj(), 12, 0);
        bubble->set_bg_color(is_me ? lv_color_hex(0x007AFF) : lv_color_hex(0x333333));

        if (is_me)
            lv_obj_set_align(bubble->get_lv_obj(), LV_ALIGN_TOP_RIGHT);
        else
            lv_obj_set_align(bubble->get_lv_obj(), LV_ALIGN_TOP_LEFT);

        auto lbl = bubble->add<Label>(text);
        lbl->set_text_color(lv_color_hex(0xFFFFFF));
        lbl->set_long_mode(LV_LABEL_LONG_WRAP);

        // --- BUG FIX ---
        // DELETE THIS LINE: lv_obj_set_width(lbl->get_lv_obj(), LV_PCT(100));
        // Replace with:
        lv_obj_set_width(lbl->get_lv_obj(), LV_SIZE_CONTENT);  // Let text determine width
        // ---------------

        lv_obj_update_layout(obj);
        lv_obj_scroll_to_view(bubble->get_lv_obj(), LV_ANIM_ON);
    }
};