#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ThreadPool() = delete;  // 默认构造函数
    ThreadPool(const ThreadPool&) = delete; // 默认拷贝构造函数
    ThreadPool& operator=(const ThreadPool&) = delete;  // 默认赋值函数
    ~ThreadPool();

    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_taskMtx;
    std::condition_variable m_taskCond;
    bool m_run;
};

#endif