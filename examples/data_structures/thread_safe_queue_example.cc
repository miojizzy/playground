/**
 * @file thread_safe_queue_example.cc
 * @brief Examples showcasing the Thread-Safe Queue data structure.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>

#include "src/data_structures/thread_safe_queue.h"

namespace cpp_utils {
namespace examples {

void RunThreadSafeQueueExample() {
  std::cout << "Thread-Safe Queue Examples" << std::endl;
  std::cout << "=========================" << std::endl;
  
  // Create a thread-safe queue of integers
  data_structures::ThreadSafeQueue<int> queue;
  
  std::cout << "Created a thread-safe queue" << std::endl;
  std::cout << "Queue is " << (queue.Empty() ? "empty" : "not empty") << std::endl;
  
  // Simple push/pop operations
  std::cout << "\nSimple push/pop operations:" << std::endl;
  queue.Push(10);
  queue.Push(20);
  queue.Push(30);
  
  std::cout << "Pushed 3 items, queue size: " << queue.Size() << std::endl;
  
  int val;
  if (queue.TryPop(val)) {
    std::cout << "Popped: " << val << std::endl;
  }
  
  std::cout << "After popping 1 item, queue size: " << queue.Size() << std::endl;
  
  // Demonstrate blocking pop with timeout
  std::cout << "\nDemonstrating blocking pop with timeout:" << std::endl;
  
  // Pop existing items
  while (queue.Size() > 0) {
    if (queue.TryPop(val)) {
      std::cout << "Popped: " << val << std::endl;
    }
  }
  
  std::cout << "Queue is now empty" << std::endl;
  
  // Try a timed wait for 500ms
  std::cout << "Waiting for an item with a 500ms timeout..." << std::endl;
  bool got_item = queue.WaitAndPop(val, std::chrono::milliseconds(500));
  std::cout << "WaitAndPop returned: " << (got_item ? "got an item" : "timed out") << std::endl;
  
  // Multithreaded example
  std::cout << "\nMultithreaded example:" << std::endl;
  
  // Clear any remaining items
  queue.Clear();
  
  const int num_producers = 3;
  const int num_items_per_producer = 5;
  std::atomic<int> items_consumed(0);
  
  // Create a consumer thread
  std::thread consumer([&queue, &items_consumed]() {
    int value;
    int expected_items = num_producers * num_items_per_producer;
    
    while (items_consumed < expected_items) {
      if (queue.WaitAndPop(value, std::chrono::seconds(1))) {
        std::cout << "Consumer got: " << value << std::endl;
        items_consumed++;
      }
    }
    
    std::cout << "Consumer finished, consumed " << items_consumed << " items" << std::endl;
  });
  
  // Create producer threads
  std::vector<std::thread> producers;
  for (int p = 0; p < num_producers; ++p) {
    producers.push_back(std::thread([&queue, p]() {
      for (int i = 0; i < num_items_per_producer; ++i) {
        int value = p * 100 + i;
        queue.Push(value);
        std::cout << "Producer " << p << " pushed: " << value << std::endl;
        
        // Sleep a bit to make the output more readable
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
    }));
  }
  
  // Join all threads
  for (auto& t : producers) {
    t.join();
  }
  consumer.join();
  
  std::cout << "\nAll threads completed" << std::endl;
  std::cout << "Final queue size: " << queue.Size() << std::endl;
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils