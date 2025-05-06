#include "src/data_structures/thread_safe_queue.h"

#include <chrono>
#include <thread>
#include <vector>
#include <gtest/gtest.h>

namespace cpp_utils {
namespace data_structures {
namespace {

TEST(ThreadSafeQueueTest, BasicOperation) {
    ThreadSafeQueue<int> queue;
    
    EXPECT_TRUE(queue.Empty());
    EXPECT_EQ(0, queue.Size());
    
    queue.Push(1);
    EXPECT_FALSE(queue.Empty());
    EXPECT_EQ(1, queue.Size());
    
    queue.Push(2);
    EXPECT_EQ(2, queue.Size());
    
    auto result = queue.TryPop();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(1, *result);
    EXPECT_EQ(1, queue.Size());
    
    result = queue.TryPop();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(2, *result);
    EXPECT_EQ(0, queue.Size());
    
    result = queue.TryPop();
    EXPECT_FALSE(result.has_value());
}

TEST(ThreadSafeQueueTest, BlockingPop) {
    ThreadSafeQueue<int> queue;
    
    std::thread producer([&queue]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        queue.Push(42);
    });
    
    // This should block until the producer adds an item
    int value = queue.Pop();
    EXPECT_EQ(42, value);
    
    // Test WaitAndPop with reference version
    producer = std::thread([&queue]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        queue.Push(43);
    });
    
    int ref_value;
    queue.WaitAndPop(ref_value);
    EXPECT_EQ(43, ref_value);
    
    producer.join();
}

TEST(ThreadSafeQueueTest, PopWithTimeout) {
    ThreadSafeQueue<int> queue;
    
    // Try to pop with a timeout (should fail)
    auto result = queue.PopWithTimeout(std::chrono::milliseconds(100));
    EXPECT_FALSE(result.has_value());
    
    // Add an item and try again (should succeed)
    queue.Push(42);
    result = queue.PopWithTimeout(std::chrono::milliseconds(100));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(42, *result);
}

TEST(ThreadSafeQueueTest, MultithreadedOperations) {
    ThreadSafeQueue<int> queue;
    const int num_items = 1000;
    
    // Producer thread
    std::thread producer([&queue, num_items]() {
        for (int i = 0; i < num_items; ++i) {
            queue.Push(i);
        }
    });
    
    // Consumer threads
    const int num_consumers = 5;
    std::vector<std::thread> consumers;
    std::vector<int> sums(num_consumers, 0);
    
    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back([&queue, &sums, i]() {
            int sum = 0;
            while (true) {
                auto item = queue.TryPop();
                if (item) {
                    sum += *item;
                } else {
                    // Sleep a bit and check if there are more items
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    item = queue.TryPop();
                    if (!item) {
                        break;
                    }
                    sum += *item;
                }
            }
            sums[i] = sum;
        });
    }
    
    producer.join();
    
    // Wait for all consumers to finish
    for (auto& consumer : consumers) {
        consumer.join();
    }
    
    // Verify that all items were processed
    int total_sum = 0;
    for (int sum : sums) {
        total_sum += sum;
    }
    
    // Sum of 0 to num_items-1
    int expected_sum = (num_items - 1) * num_items / 2;
    EXPECT_EQ(expected_sum, total_sum);
}

TEST(ThreadSafeQueueTest, Clear) {
    ThreadSafeQueue<int> queue;
    
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    
    EXPECT_EQ(3, queue.Size());
    
    queue.Clear();
    
    EXPECT_TRUE(queue.Empty());
    EXPECT_EQ(0, queue.Size());
    
    auto result = queue.TryPop();
    EXPECT_FALSE(result.has_value());
}

}  // namespace
}  // namespace data_structures
}  // namespace cpp_utils
