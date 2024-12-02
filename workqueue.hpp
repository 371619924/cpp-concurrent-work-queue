#ifndef WORKQUEUE_HPP
#define WORKQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class WorkQueue
{
private:
    std::queue<T> data;       // Queue to store the data
    std::mutex lock;          // Mutex for synchronization
    std::condition_variable notify;  // Condition variable for notification

public:
    // Default constructor
    WorkQueue() = default;

    // Move constructor
    WorkQueue(WorkQueue&& other) noexcept
    {
        std::lock_guard<std::mutex> guard(other.lock);  // Lock the source queue's mutex to ensure safe data transfer
        data = std::move(other.data);  // Move the data from the source queue
    }

    // Move assignment operator
    WorkQueue& operator=(WorkQueue&& other) noexcept
    {
        if (this != &other)  // Prevent self-assignment
        {
            std::lock_guard<std::mutex> guard(other.lock);  // Lock the source queue's mutex to ensure safe data transfer
            data = std::move(other.data);  // Move the data from the source queue
        }
        return *this;
    }

    // Copy constructor
    WorkQueue( WorkQueue& other)
    {
        std::lock_guard<std::mutex> guard(other.lock);  // Lock the source queue's mutex to ensure safe data copying
        data = other.data;  // Perform deep copy of the data
    }

    // Copy assignment operator
    WorkQueue& operator=( WorkQueue& other)
    {
        if (this != &other)  // Prevent self-assignment
        {
            std::lock_guard<std::mutex> guard(other.lock);  // Lock the source queue's mutex to ensure safe data copying
            data = other.data;  // Perform deep copy of the data
        }
        return *this;
    }

    // Add an element to the queue
    void put(T& element)
    {
        bool wasempty = false;
        {
            std::unique_lock<std::mutex> l(lock);
            wasempty = data.empty();
            data.push(element);  // Push the element into the queue
        }
        if (wasempty)
            notify.notify_all();  // Notify all waiting threads that the queue is no longer empty
    }

    // Get an element from the queue
    T get()
    {
        std::unique_lock<std::mutex> l(lock);
        while (data.empty())  // Wait until the queue is not empty
        {
            notify.wait(l);
        }
        auto ret = data.front();  // Get the front element
        data.pop();  // Remove the front element
        return ret;  // Return the element
    }

    // Destructor 
    ~WorkQueue() = default;
};

#endif
