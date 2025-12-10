#include "message_store.hpp"

void MessageStore::addListener(MessageCallback cb) {
    listeners_.push_back(std::move(cb));
}

void MessageStore::addMessage(MessageEntry entry) {
    messages_.push_back(std::move(entry));
    while (messages_.size() > cacheSize_) {
        messages_.pop_front();
    }
    const MessageEntry& stored = messages_.back();
    for (auto& listener : listeners_) {
        if (listener) listener(stored);
    }
}

std::vector<MessageStore::MessageEntry> MessageStore::getHistory() {
    return {messages_.begin(), messages_.end()};
}

void MessageStore::setCacheSize(std::size_t size) {
    cacheSize_ = size;
    while (messages_.size() > cacheSize_) {
        messages_.pop_front();
    }
}
