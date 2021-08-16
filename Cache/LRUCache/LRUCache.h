#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>

struct Node {
    int key;
    int value;

    Node(int _key, int _value) : key(_key), value(_value) {}
};

class LRUCache {
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);

private:
    std::list<Node> m_list;
    std::unordered_map<int, std::list<Node>::iterator> m_map;
    int m_capacity;
};

#endif