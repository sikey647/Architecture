#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads) 
    : m_run(true) {
    for (size_t i = 0; i < threads; ++i) {
        m_workers.emplace_back([this]{
            while (true) {
                std::unique_lock<std::mutex> lock(m_taskMtx);
                m_taskCond.wait(lock, [this]{
                    // 工作停止 或者 队列中有任务
                    return !this->m_run || !this->m_tasks.empty();
                });
                
                // 工作停止 并且 队列中无任务
                if (!this->m_run && m_tasks.empty()) {
                    return ;
                }

                std::function<void()> task = std::move(this->m_tasks.front());
                this->m_tasks.pop();
                lock.unlock();
                
                // 执行任务
                task();
            }
        });
    }    
}

template<class F, class... Args>
auto ThreadPool::commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
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

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(m_taskMtx);
    m_run = false;
    lock.unlock();
    m_taskCond.notify_all();

    for (std::thread& worker : m_workers) {
        worker.join();
    }
}