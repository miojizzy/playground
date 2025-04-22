/**
 * @file data_structures_example.cc
 * @brief Examples showcasing the data structure components.
 */

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "src/data_structures/thread_safe_queue.h"
#include "src/data_structures/lru_cache.h"

void thread_safe_queue_example() {
    std::cout << "Thread-Safe Queue Example" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    cpp_utils::data_structures::ThreadSafeQueue<int> queue;
    
    // Producer thread
    std::thread producer([&queue]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Producer: Pushing " << i << std::endl;
            queue.Push(i);
        }
    });
    
    // Consumer thread
    std::thread consumer([&queue]() {
        for (int i = 0; i < 5; ++i) {
            int value = queue.Pop();
            std::cout << "Consumer: Popped " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }
    });
    
    producer.join();
    consumer.join();
    
    // Timeout example
    std::cout << "\nTrying to pop with timeout (should fail):" << std::endl;
    auto result = queue.PopWithTimeout(std::chrono::milliseconds(500));
    std::cout << "Result: " << (result ? std::to_string(*result) : "timeout") << std::endl;
    
    // Push and try again
    std::cout << "\nPushing 42 and trying again:" << std::endl;
    queue.Push(42);
    result = queue.PopWithTimeout(std::chrono::milliseconds(500));
    std::cout << "Result: " << (result ? std::to_string(*result) : "timeout") << std::endl;
    
    std::cout << std::endl;
}

void lru_cache_example() {
    std::cout << "LRU Cache Example" << std::endl;
    std::cout << "----------------" << std::endl;
    
    cpp_utils::data_structures::LRUCache<std::string, std::string> cache(3);
    
    // Add some items
    cache.Put("key1", "value1");
    cache.Put("key2", "value2");
    cache.Put("key3", "value3");
    
    std::cout << "Cache after adding 3 items:" << std::endl;
    std::cout << "Size: " << cache.Size() << std::endl;
    std::cout << "Contains key1: " << (cache.Contains("key1") ? "yes" : "no") << std::endl;
    std::cout << "Contains key2: " << (cache.Contains("key2") ? "yes" : "no") << std::endl;
    std::cout << "Contains key3: " << (cache.Contains("key3") ? "yes" : "no") << std::endl;
    
    // Access key1 to make it most recently used
    auto value = cache.Get("key1");
    std::cout << "\nAccessed key1, value: " << (value ? *value : "not found") << std::endl;
    
    // Add another item to evict the least recently used (key2)
    cache.Put("key4", "value4");
    
    std::cout << "\nCache after adding key4:" << std::endl;
    std::cout << "Size: " << cache.Size() << std::endl;
    std::cout << "Contains key1: " << (cache.Contains("key1") ? "yes" : "no") << std::endl;
    std::cout << "Contains key2: " << (cache.Contains("key2") ? "yes" : "no") << std::endl;
    std::cout << "Contains key3: " << (cache.Contains("key3") ? "yes" : "no") << std::endl;
    std::cout << "Contains key4: " << (cache.Contains("key4") ? "yes" : "no") << std::endl;
    
    // Update an existing key
    cache.Put("key3", "updated-value3");
    value = cache.Get("key3");
    std::cout << "\nUpdated key3, new value: " << (value ? *value : "not found") << std::endl;
    
    // Erase a key
    bool erased = cache.Erase("key1");
    std::cout << "\nErased key1: " << (erased ? "yes" : "no") << std::endl;
    std::cout << "Size after erase: " << cache.Size() << std::endl;
    
    // Clear the cache
    cache.Clear();
    std::cout << "\nCleared cache, size: " << cache.Size() << std::endl;
}

int main() {
    std::cout << "Data Structures Examples" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;
    
    thread_safe_queue_example();
    lru_cache_example();
    
    return 0;
}
