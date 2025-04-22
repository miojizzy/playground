#include "src/data_structures/lru_cache.h"

#include <gtest/gtest.h>

namespace cpp_utils {
namespace data_structures {
namespace {

TEST(LRUCacheTest, BasicOperations) {
    LRUCache<int, std::string> cache(3);
    
    EXPECT_EQ(0, cache.Size());
    EXPECT_EQ(3, cache.Capacity());
    
    // Add some items
    cache.Put(1, "one");
    cache.Put(2, "two");
    
    EXPECT_EQ(2, cache.Size());
    EXPECT_TRUE(cache.Contains(1));
    EXPECT_TRUE(cache.Contains(2));
    EXPECT_FALSE(cache.Contains(3));
    
    // Get an item
    auto result = cache.Get(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ("one", *result);
    
    // Get a non-existent item
    result = cache.Get(3);
    EXPECT_FALSE(result.has_value());
}

TEST(LRUCacheTest, EvictionPolicy) {
    LRUCache<int, std::string> cache(3);
    
    // Fill the cache
    cache.Put(1, "one");
    cache.Put(2, "two");
    cache.Put(3, "three");
    
    EXPECT_EQ(3, cache.Size());
    EXPECT_TRUE(cache.Contains(1));
    EXPECT_TRUE(cache.Contains(2));
    EXPECT_TRUE(cache.Contains(3));
    
    // Access item 1 to make it most recently used
    cache.Get(1);
    
    // Add a new item to trigger eviction of least recently used (should be 2)
    cache.Put(4, "four");
    
    EXPECT_EQ(3, cache.Size());
    EXPECT_TRUE(cache.Contains(1));
    EXPECT_FALSE(cache.Contains(2));  // Evicted
    EXPECT_TRUE(cache.Contains(3));
    EXPECT_TRUE(cache.Contains(4));
    
    // Access item 3 to make it most recently used
    cache.Get(3);
    
    // Add a new item to trigger eviction of least recently used (should be 1)
    cache.Put(5, "five");
    
    EXPECT_EQ(3, cache.Size());
    EXPECT_FALSE(cache.Contains(1));  // Evicted
    EXPECT_FALSE(cache.Contains(2));  // Already evicted
    EXPECT_TRUE(cache.Contains(3));
    EXPECT_TRUE(cache.Contains(4));
    EXPECT_TRUE(cache.Contains(5));
}

TEST(LRUCacheTest, UpdateExistingItem) {
    LRUCache<int, std::string> cache(3);
    
    cache.Put(1, "one");
    cache.Put(2, "two");
    
    // Update an existing item
    cache.Put(1, "ONE");
    
    auto result = cache.Get(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ("ONE", *result);
}

TEST(LRUCacheTest, EraseItem) {
    LRUCache<int, std::string> cache(3);
    
    cache.Put(1, "one");
    cache.Put(2, "two");
    
    EXPECT_EQ(2, cache.Size());
    
    // Erase an existing item
    bool erased = cache.Erase(1);
    EXPECT_TRUE(erased);
    EXPECT_EQ(1, cache.Size());
    EXPECT_FALSE(cache.Contains(1));
    EXPECT_TRUE(cache.Contains(2));
    
    // Try to erase a non-existent item
    erased = cache.Erase(3);
    EXPECT_FALSE(erased);
    EXPECT_EQ(1, cache.Size());
}

TEST(LRUCacheTest, Clear) {
    LRUCache<int, std::string> cache(3);
    
    cache.Put(1, "one");
    cache.Put(2, "two");
    
    EXPECT_EQ(2, cache.Size());
    
    cache.Clear();
    
    EXPECT_EQ(0, cache.Size());
    EXPECT_FALSE(cache.Contains(1));
    EXPECT_FALSE(cache.Contains(2));
}

TEST(LRUCacheTest, HeavyUsage) {
    // Test with a larger number of operations
    const int cache_size = 100;
    LRUCache<int, int> cache(cache_size);
    
    // Fill the cache
    for (int i = 0; i < cache_size; ++i) {
        cache.Put(i, i * 10);
    }
    
    EXPECT_EQ(cache_size, cache.Size());
    
    // Verify all items are present
    for (int i = 0; i < cache_size; ++i) {
        EXPECT_TRUE(cache.Contains(i));
        auto result = cache.Get(i);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(i * 10, *result);
    }
    
    // Add more items to trigger evictions
    for (int i = cache_size; i < cache_size * 2; ++i) {
        cache.Put(i, i * 10);
        
        // The cache should maintain its size
        EXPECT_EQ(cache_size, cache.Size());
        
        // The earliest items should be evicted
        EXPECT_FALSE(cache.Contains(i - cache_size));
    }
}

}  // namespace
}  // namespace data_structures
}  // namespace cpp_utils
