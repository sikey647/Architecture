#include <iostream>
#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);
    
    auto res = pool.commit([](int x) {
        return x;
    }, 10);

    std::cout << res.get() << std::endl;
}

