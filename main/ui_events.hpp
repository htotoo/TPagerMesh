#pragma once

enum class UIEventType {
    NEW_MESSAGE,
};

struct UIEvent {
    UIEventType type;
    union {
        MessageStore::MessageEntry* msg_ptr;  // Pointer to avoid copying large objects in the queue
    } data;
};