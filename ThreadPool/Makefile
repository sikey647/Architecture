
CXX = g++
CXXFLAGS += -std=c++11

ThreadPool: ThreadPool.o main.o
	$(CXX) $^ -pthread -o $@

clean:
	rm -rf *.o ThreadPool