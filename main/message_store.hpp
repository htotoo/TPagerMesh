#pragma once

#include <string>
#include <stdint.h>
#include <deque>
#include <vector>
#include <functional>
#include <ctime>

class MessageStore {
   public:
    struct MessageEntry {
        std::string sender;   // sender name or ID
        uint8_t channel;      // channel id
        bool isDirect;        // direct message or broadcast
        std::string message;  // message content
        bool isFromMe;        // whether the message is sent by the user
        std::time_t time;     // timestamp
    };

    using MessageCallback = std::function<void(const MessageEntry&)>;

    explicit MessageStore(std::size_t cacheSize = 20)
        : cacheSize_(cacheSize) {
    }

    void addListener(MessageCallback cb);

    void addMessage(MessageEntry entry);

    std::vector<MessageEntry> getHistory();

    void setCacheSize(std::size_t size);

   private:
    std::size_t cacheSize_;
    std::deque<MessageEntry> messages_;
    std::vector<MessageCallback> listeners_;
};
