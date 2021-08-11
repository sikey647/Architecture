#include <iostream>
#include "ThreadPool.h"

int f(int x) {
    return x;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    ThreadPool pool(4);
    
    // auto res = pool.commit([](int x) {
    //     return x;
    // }, 10);

    std::future<int> res = pool.commit(add, 10, 20);

    std::cout << res.get() << std::endl;

    return 0;
}

