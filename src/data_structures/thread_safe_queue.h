/**
 * @file thread_safe_queue.h
 * @brief A thread-safe queue implementation.
 */

#ifndef CPP_UTILS_LIB_SRC_DATA_STRUCTURES_THREAD_SAFE_QUEUE_H_
#define CPP_UTILS_LIB_SRC_DATA_STRUCTURES_THREAD_SAFE_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

namespace cpp_utils {
namespace data_structures {

/**
 * @brief A thread-safe queue implementation for producer-consumer patterns.
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class ThreadSafeQueue {
public:
    /**
     * @brief Constructs an empty queue.
     */
    ThreadSafeQueue() = default;

    /**
     * @brief Copy constructor is deleted to prevent accidental copying.
     */
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;

    /**
     * @brief Assignment operator is deleted to prevent accidental copying.
     */
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    /**
     * @brief Adds an element to the queue.
     * @param value The value to add.
     */
    void Push(T value) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
        }
        condition_.notify_one();
    }

    /**
     * @brief Tries to pop an element from the queue without blocking.
     * @return An optional containing the element if the queue is not empty, or std::nullopt otherwise.
     */
    std::optional<T> TryPop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        
        return PopUnlocked();
    }

    /**
     * @brief Pops an element from the queue, blocking if the queue is empty.
     * @return The element.
     */
    T Pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this]() { return !queue_.empty(); });
        return PopUnlocked();
    }

    /**
     * @brief Pops an element from the queue, blocking if the queue is empty up to a timeout.
     * @param timeout The maximum time to wait.
     * @return An optional containing the element if one was available, or std::nullopt otherwise.
     */
    template <typename Rep, typename Period>
    std::optional<T> PopWithTimeout(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!condition_.wait_for(lock, timeout, [this]() { return !queue_.empty(); })) {
            return std::nullopt;
        }
        
        return PopUnlocked();
    }

    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool Empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    /**
     * @brief Gets the size of the queue.
     * @return The number of elements in the queue.
     */
    size_t Size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    /**
     * @brief Clears all elements from the queue.
     */
    void Clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::queue<T> empty;
        std::swap(queue_, empty);
    }

private:
    // Helper method to pop an element from the queue (assumes lock is held).
    T PopUnlocked() {
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

}  // namespace data_structures
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_DATA_STRUCTURES_THREAD_SAFE_QUEUE_H_
