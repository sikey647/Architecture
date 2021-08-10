
CXX = g++
CXXFLAGS += -std=c++11 -pthread

ThreadPool: ThreadPool.o main.o
	$(CXX) $^ -o $@

clean:
	rm -rf *.o ThreadPool