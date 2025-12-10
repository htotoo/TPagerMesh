#pragma once

#include "lvgl.h"
#include "esp_log.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include "message_store.hpp"

LV_FONT_DECLARE(font_montserrat_10_hun);
LV_FONT_DECLARE(font_montserrat_12_hun);

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
        set_height(LV_PCT(100));  // The list itself fills the screen
        set_padding(10);

        // Critical: Set the gap between distinct chat bubbles
        lv_obj_set_style_pad_row(obj, 8, 0);

        // Ensure scrollbar doesn't overlap text
        lv_obj_set_style_pad_right(obj, 4, LV_PART_SCROLLBAR);
    }

    void add_message(const MessageStore::MessageEntry& msg) {
        // --- 1. CALCULATE WIDTHS ---
        // Get screen width safely to calculate constraints
        int32_t screen_width = lv_display_get_horizontal_resolution(NULL);
        if (screen_width <= 0) screen_width = 320;

        // Bubble max width is 80% of screen (standard for chat apps)
        int32_t max_bubble_width = screen_width * 0.80;

        // Inner padding of the bubble (left + right)
        int32_t bubble_padding = 16;
        int32_t max_text_width = max_bubble_width - bubble_padding;

        // --- 2. CREATE BUBBLE CONTAINER ---
        auto bubble = add<Container>();
        lv_obj_t* bubble_obj = bubble->get_lv_obj();

        // LAYOUT: Vertical column (Sender -> Message -> Time)
        lv_obj_set_layout(bubble_obj, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(bubble_obj, LV_FLEX_FLOW_COLUMN);

        // HEIGHT FIX: Strictly fit content!
        lv_obj_set_height(bubble_obj, LV_SIZE_CONTENT);
        lv_obj_set_width(bubble_obj, LV_SIZE_CONTENT);
        lv_obj_set_style_max_width(bubble_obj, max_bubble_width, 0);

        // Styling
        bubble->set_padding(8);                      // Internal padding 8px
        lv_obj_set_style_radius(bubble_obj, 12, 0);  // Nice rounded corners

        bool is_me = msg.isFromMe;

        // --- 3. COLORS & ALIGNMENT ---
        if (is_me) {
            // My messages: Right aligned, Blue
            lv_obj_set_align(bubble_obj, LV_ALIGN_TOP_RIGHT);

            // Gradient-like Blue (Solid for now, but distinct)
            bubble->set_bg_color(lv_color_hex(0x007AFF));  // Apple Blue
            lv_obj_set_style_text_color(bubble_obj, lv_color_hex(0xFFFFFF), 0);
        } else {
            // Others: Left aligned, Light Gray
            lv_obj_set_align(bubble_obj, LV_ALIGN_TOP_LEFT);

            bubble->set_bg_color(lv_color_hex(0xE9E9EB));  // Light Gray
            lv_obj_set_style_text_color(bubble_obj, lv_color_hex(0x000000), 0);
        }

        // --- 4. SENDER NAME (Only for others) ---
        // We don't need to see our own name
        if (!is_me) {
            auto sender_lbl = bubble->add<Label>(msg.sender);
            lv_obj_t* sender_obj = sender_lbl->get_lv_obj();

            lv_obj_set_style_text_font(sender_obj, &font_montserrat_10_hun, 0);

            // Make sender name a distinct color (e.g., Orange or Dark Gray)
            lv_obj_set_style_text_color(sender_obj, lv_color_hex(0x888888), 0);

            lv_obj_set_width(sender_obj, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_bottom(sender_obj, 2, 0);  // Tiny gap below name
        }

        // --- 5. MESSAGE TEXT ---
        auto body_lbl = bubble->add<Label>(msg.message);
        lv_obj_t* body_obj = body_lbl->get_lv_obj();

        lv_obj_set_style_text_font(body_obj, &font_montserrat_12_hun, 0);
        lv_label_set_long_mode(body_obj, LV_LABEL_LONG_WRAP);

        // SIZE FIX: Content width, but capped at max pixels
        lv_obj_set_width(body_obj, LV_SIZE_CONTENT);
        lv_obj_set_style_max_width(body_obj, max_text_width, 0);

        // Ensure text color is set correctly based on background
        if (is_me) {
            lv_obj_set_style_text_color(body_obj, lv_color_hex(0xFFFFFF), 0);
        } else {
            lv_obj_set_style_text_color(body_obj, lv_color_hex(0x000000), 0);
        }

        // --- 6. TIME STAMP (Bottom Right) ---
        // Format time
        char time_buf[16];
        struct tm tm_info;
        localtime_r(&msg.time, &tm_info);
        strftime(time_buf, sizeof(time_buf), "%H:%M", &tm_info);

        auto time_lbl = bubble->add<Label>(time_buf);
        lv_obj_t* time_obj = time_lbl->get_lv_obj();

        lv_obj_set_style_text_font(time_obj, &font_montserrat_10_hun, 0);
        lv_obj_set_width(time_obj, LV_SIZE_CONTENT);

        // Align time to the right of the bubble
        lv_obj_set_align(time_obj, LV_ALIGN_BOTTOM_RIGHT);

        // Make it aligned to the right within the flex column
        lv_obj_set_style_align(time_obj, LV_ALIGN_BOTTOM_RIGHT, 0);  // Fallback alignment
        lv_obj_set_align(time_obj, LV_ALIGN_BOTTOM_RIGHT);

        // Important: In a Column flex, items align left by default.
        // We force this specific item to align "End" (Right).
        lv_obj_set_flex_align(bubble_obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_style_align(time_obj, LV_ALIGN_BOTTOM_RIGHT, 0);  // Try to force it right

        // Hack for Flex Column to push Time to right:
        // We set the "Self Alignment" of the time object
        lv_obj_set_align(time_obj, LV_ALIGN_BOTTOM_RIGHT);
        // Note: In LVGL Flex, align_self isn't always exposed simply,
        // so we often rely on the parent.
        // If it stays on left, we can wrap it in a container, but let's try this:
        lv_obj_set_style_text_align(time_obj, LV_TEXT_ALIGN_RIGHT, 0);

        // Opacity/Color for Time
        if (is_me) {
            // White text, but transparent
            lv_obj_set_style_text_color(time_obj, lv_color_hex(0xFFFFFF), 0);
            lv_obj_set_style_text_opa(time_obj, LV_OPA_70, 0);
        } else {
            // Grey text
            lv_obj_set_style_text_color(time_obj, lv_color_hex(0x8A8A8E), 0);
        }

        // Add a little padding top to separate time from text
        lv_obj_set_style_pad_top(time_obj, 2, 0);
        // Force the Time label to align to the right side of the bubble container
        lv_obj_set_align(time_obj, LV_ALIGN_BOTTOM_RIGHT);

        // --- 7. FINALIZE ---
        lv_obj_update_layout(obj);
        lv_obj_scroll_to_view(bubble_obj, LV_ANIM_ON);
    }
};