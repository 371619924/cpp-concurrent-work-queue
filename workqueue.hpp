#ifndef WORKQUEUE_HPP
#define WORKQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class WorkQueue
{
private:
    std::queue<T> data;       // 存储数据的队列
    std::mutex lock;          // 用于同步的互斥锁
    std::condition_variable notify;  // 用于通知的条件变量

public:
    // 默认构造函数
    WorkQueue() = default;

    // 移动构造函数
    WorkQueue(WorkQueue&& other) noexcept
    {
        std::lock_guard<std::mutex> guard(other.lock);  // 锁定源队列的互斥锁，确保数据安全转移
        data = std::move(other.data);  // 移动队列的数据
    }

    // 移动赋值操作符
    WorkQueue& operator=(WorkQueue&& other) noexcept
    {
        if (this != &other)  // 防止自赋值
        {
            std::lock_guard<std::mutex> guard(other.lock);  // 锁定源队列的互斥锁，确保数据安全转移
            data = std::move(other.data);  // 移动队列的数据
        }
        return *this;
    }

    // 复制构造函数
    WorkQueue( WorkQueue& other)
    {
        std::lock_guard<std::mutex> guard(other.lock);  // 锁定源队列的互斥锁，确保数据安全复制
        data = other.data;  // 执行深度复制
    }

    // 复制赋值操作符
    WorkQueue& operator=( WorkQueue& other)
    {
        if (this != &other)  // 防止自赋值
        {
            std::lock_guard<std::mutex> guard(other.lock);  // 锁定源队列的互斥锁，确保数据安全复制
            data = other.data;  // 执行深度复制
        }
        return *this;
    }

    // 向队列中添加元素
    void put(T& element)
    {
        bool wasempty = false;
        {
            std::unique_lock<std::mutex>l(lock);
            wasempty = data.empty();
            data.push(element);
        }
        if (wasempty)
            notify.notify_all();
    }

    // 从队列中获取元素
    T get()
    {
        std::unique_lock<std::mutex>l(lock);
        while (data.empty())
        {
            notify.wait(l);
        }
        auto ret = data.front();
        data.pop();
        return ret;
    }

    // 析构函数（如果没有特别的清理需求，可以默认使用）
    ~WorkQueue() = default;
};

#endif
