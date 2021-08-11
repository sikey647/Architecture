
#include <thread>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <future>
using namespace std;
 
int mythread(int mypar) {
	cout << mypar << endl;
	cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << endl;
	return 5;
}

int add(int a, int b) {
    return a + b;
}

class Execute {
public:
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );  // 把函数入口和参数打包（绑定）

        std::future<RetType> future = task->get_future();

        (*task)();

        return future;
    }
};



void test() {
    int tmp = 12;
	cout << "main" << "threadid = " << std::this_thread::get_id() << endl;

	std::packaged_task<int(int)> mypt(mythread); //我们把函数mythread通过packaged_task包装起来
	std::thread t1(std::ref(mypt), 1);

    //std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果。
	std::future<int> result = mypt.get_future(); 
	cout << "wait result" << endl;
	cout << result.get() << endl;

    t1.join();
	cout << "good luck" << endl;
}

int main() {

	//test();

    Execute e;

    auto res = e.commit(add, 10, 20);

    std::cout << res.get() << std::endl;

	return 0;
}