#pragma once

#include <string>
#include <stdint.h>
#include <deque>
#include <vector>
#include <functional>
#include <ctime>
#include <memory>
#include <cstdlib>  // <--- ADDED: for std::abort()
#include "esp_heap_caps.h"

// --- 1. Custom PSRAM Allocator ---
template <typename T>
struct PsramAllocator {
    using value_type = T;

    PsramAllocator() noexcept {}
    template <typename U>
    PsramAllocator(const PsramAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        // Try PSRAM first
        void* ptr = heap_caps_malloc(n * sizeof(T), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

        // Fallback to internal RAM if PSRAM fails/full
        if (!ptr) {
            ptr = heap_caps_malloc(n * sizeof(T), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        }

        // --- FIX: Don't throw exceptions if -fno-exceptions is set ---
        if (!ptr) {
            // In a no-exception environment, OOM (Out Of Memory) is fatal.
            // We abort execution rather than crashing randomly later on null dereference.
            std::abort();
        }
        // -------------------------------------------------------------

        return static_cast<T*>(ptr);
    }

    void deallocate(T* p, std::size_t) noexcept {
        heap_caps_free(p);
    }

    // Friend operators for allocator comparison
    template <typename U>
    friend bool operator==(const PsramAllocator&, const PsramAllocator<U>&) noexcept {
        return true;
    }

    template <typename U>
    friend bool operator!=(const PsramAllocator&, const PsramAllocator<U>&) noexcept {
        return false;
    }
};

// --- 2. Define PSRAM-aware String ---
using PsramString = std::basic_string<char, std::char_traits<char>, PsramAllocator<char>>;

class MessageStore {
   public:
    struct MessageEntry {
        PsramString sender;
        uint8_t channel;
        bool isDirect;
        PsramString message;
        bool isFromMe;
        std::time_t time;
    };

    using MessageCallback = std::function<void(const MessageEntry&)>;
    using VisitorCallback = std::function<bool(const MessageEntry&)>;
    using PsramDeque = std::deque<MessageEntry, PsramAllocator<MessageEntry>>;
    using ConstIterator = PsramDeque::const_iterator;

    explicit MessageStore(std::size_t cacheSize = 20);

    void addListener(MessageCallback cb);
    void addMessage(MessageEntry entry);
    void traverseHistory(VisitorCallback visitor) const;

    ConstIterator begin() const;
    ConstIterator end() const;

    void setCacheSize(std::size_t size);

   private:
    std::size_t cacheSize_;
    PsramDeque messages_;
    std::vector<MessageCallback> listeners_;
};