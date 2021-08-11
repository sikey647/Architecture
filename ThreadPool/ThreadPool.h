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
    // ThreadPool() = delete;  // 默认构造函数
    // ThreadPool(const ThreadPool&) = delete; // 默认拷贝构造函数
    // ThreadPool& operator=(const ThreadPool&) = delete;  // 默认赋值函数
    ~ThreadPool();

    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );  // 把函数入口和参数打包（绑定）

        std::future<RetType> future = task->get_future();

        std::unique_lock<std::mutex> lock(m_taskMtx);
        if (!m_run) {
            throw std::runtime_error("commit on stopped ThreadPool.");
        }
        m_tasks.emplace([task](){
            (*task)();
        });
        lock.unlock();

        m_taskCond.notify_one();

        return future;
    }

private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_taskMtx;
    std::condition_variable m_taskCond;
    bool m_run;
};

#endif