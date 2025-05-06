/**
 * @file lru_cache_example.cc
 * @brief Examples showcasing the LRU Cache data structure.
 */

#include <iostream>
#include <string>

#include "src/data_structures/lru_cache.h"

namespace cpp_utils {
namespace examples {

void RunLRUCacheExample() {
  std::cout << "LRU Cache Examples" << std::endl;
  std::cout << "=================" << std::endl;
  
  // Create a cache with capacity 3
  data_structures::LRUCache<std::string, int> cache(3);
  std::cout << "Created LRU Cache with capacity 3" << std::endl;
  
  // Add some items
  cache.Put("one", 1);
  cache.Put("two", 2);
  cache.Put("three", 3);
  
  std::cout << "After adding three items:" << std::endl;
  std::cout << "Contains 'one': " << (cache.Contains("one") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
  
  // Add a fourth item, which should evict the least recently used item (one)
  cache.Put("four", 4);
  
  std::cout << "\nAfter adding 'four':" << std::endl;
  std::cout << "Contains 'one': " << (cache.Contains("one") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'four': " << (cache.Contains("four") ? "yes" : "no") << std::endl;
  
  // Access an item, which should update its position in the LRU order
  auto val = cache.Get("two");
  if (val) {
    std::cout << "\nGot 'two': " << *val << std::endl;
  }
  
  // Add a fifth item, which should evict the least recently used item (now three)
  cache.Put("five", 5);
  
  std::cout << "\nAfter accessing 'two' and adding 'five':" << std::endl;
  std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'four': " << (cache.Contains("four") ? "yes" : "no") << std::endl;
  std::cout << "Contains 'five': " << (cache.Contains("five") ? "yes" : "no") << std::endl;
  
  // Demonstrate updating an existing key
  cache.Put("four", 44);
  auto updated_val = cache.Get("four");
  std::cout << "\nUpdated 'four' value: " << (updated_val ? std::to_string(*updated_val) : "not found") << std::endl;
  
  // Use with different types
  data_structures::LRUCache<int, std::string> int_cache(2);
  int_cache.Put(1, "One");
  int_cache.Put(2, "Two");
  
  std::cout << "\nInteger key cache:" << std::endl;
  std::cout << "Key 1 maps to: " << (int_cache.Get(1) ? *int_cache.Get(1) : "not found") << std::endl;
  std::cout << "Key 2 maps to: " << (int_cache.Get(2) ? *int_cache.Get(2) : "not found") << std::endl;
  
  int_cache.Put(3, "Three");  // Should evict key 1
  std::cout << "After adding key 3, key 1 is " << (int_cache.Contains(1) ? "present" : "evicted") << std::endl;
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils