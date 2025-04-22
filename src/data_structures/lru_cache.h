/**
 * @file lru_cache.h
 * @brief An LRU (Least Recently Used) cache implementation.
 */

#ifndef CPP_UTILS_LIB_SRC_DATA_STRUCTURES_LRU_CACHE_H_
#define CPP_UTILS_LIB_SRC_DATA_STRUCTURES_LRU_CACHE_H_

#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

namespace cpp_utils {
namespace data_structures {

/**
 * @brief A Least Recently Used (LRU) cache implementation.
 * @tparam Key The type of keys.
 * @tparam Value The type of values.
 */
template <typename Key, typename Value>
class LRUCache {
public:
    /**
     * @brief Constructs an LRU cache with a specified capacity.
     * @param capacity The maximum number of elements in the cache.
     */
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    /**
     * @brief Puts a key-value pair in the cache.
     * 
     * If the key already exists, its value is updated and it becomes
     * the most recently used item. If the cache is full, the least
     * recently used item is evicted.
     * 
     * @param key The key.
     * @param value The value.
     */
    void Put(const Key& key, Value value) {
        auto it = cache_map_.find(key);
        if (it != cache_map_.end()) {
            // Key exists, update value and move to front of list
            usage_list_.erase(it->second.list_iterator);
            usage_list_.push_front(key);
            it->second.value = std::move(value);
            it->second.list_iterator = usage_list_.begin();
        } else {
            // Key doesn't exist, add new entry
            // If cache is full, remove least recently used item
            if (cache_map_.size() >= capacity_) {
                // Remove the least recently used element
                const Key& lru_key = usage_list_.back();
                cache_map_.erase(lru_key);
                usage_list_.pop_back();
            }
            
            // Add new item
            usage_list_.push_front(key);
            CacheEntry entry{std::move(value), usage_list_.begin()};
            cache_map_[key] = std::move(entry);
        }
    }

    /**
     * @brief Gets a value from the cache.
     * 
     * If the key exists, it becomes the most recently used item.
     * 
     * @param key The key to look up.
     * @return An optional containing the value if it exists, or std::nullopt otherwise.
     */
    std::optional<Value> Get(const Key& key) {
        auto it = cache_map_.find(key);
        if (it == cache_map_.end()) {
            return std::nullopt;
        }
        
        // Move this key to the front of the list (most recently used)
        usage_list_.erase(it->second.list_iterator);
        usage_list_.push_front(key);
        it->second.list_iterator = usage_list_.begin();
        
        return it->second.value;
    }

    /**
     * @brief Checks if a key exists in the cache.
     * @param key The key to check.
     * @return True if the key exists, false otherwise.
     */
    bool Contains(const Key& key) const {
        return cache_map_.find(key) != cache_map_.end();
    }

    /**
     * @brief Removes a key-value pair from the cache.
     * @param key The key to remove.
     * @return True if the key was removed, false if it didn't exist.
     */
    bool Erase(const Key& key) {
        auto it = cache_map_.find(key);
        if (it == cache_map_.end()) {
            return false;
        }
        
        usage_list_.erase(it->second.list_iterator);
        cache_map_.erase(it);
        return true;
    }

    /**
     * @brief Gets the current size of the cache.
     * @return The number of elements in the cache.
     */
    size_t Size() const {
        return cache_map_.size();
    }

    /**
     * @brief Gets the capacity of the cache.
     * @return The maximum number of elements the cache can hold.
     */
    size_t Capacity() const {
        return capacity_;
    }

    /**
     * @brief Clears all elements from the cache.
     */
    void Clear() {
        cache_map_.clear();
        usage_list_.clear();
    }

private:
    struct CacheEntry {
        Value value;
        typename std::list<Key>::iterator list_iterator;
    };

    size_t capacity_;
    std::list<Key> usage_list_;  // Most recently used items at the front
    std::unordered_map<Key, CacheEntry> cache_map_;
};

}  // namespace data_structures
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_DATA_STRUCTURES_LRU_CACHE_H_
