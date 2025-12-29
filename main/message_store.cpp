#include "message_store.hpp"

MessageStore::MessageStore(std::size_t cacheSize)
    : cacheSize_(cacheSize) {
}

void MessageStore::addListener(MessageCallback cb) {
    listeners_.push_back(std::move(cb));
}

void MessageStore::addMessage(MessageEntry entry) {
    // entry is moved into the deque (PSRAM)
    messages_.push_back(std::move(entry));
    while (messages_.size() > cacheSize_) {
        messages_.pop_front();
    }
    MessageEntry& stored = messages_.back();
    for (auto& listener : listeners_) {
        if (listener) listener(stored);
    }
}

// Option A: Visitor Pattern (Safest, controlled scope)
void MessageStore::traverseHistory(VisitorCallback visitor) const {
    if (!visitor) return;

    for (const auto& entry : messages_) {
        bool continueIterating = visitor(entry);
        if (!continueIterating) break;
    }
}

// Option B: Standard Iterators
MessageStore::ConstIterator MessageStore::begin() const {
    return messages_.begin();
}

MessageStore::ConstIterator MessageStore::end() const {
    return messages_.end();
}

void MessageStore::setCacheSize(std::size_t size) {
    cacheSize_ = size;
    while (messages_.size() > cacheSize_) {
        messages_.pop_front();
    }
}