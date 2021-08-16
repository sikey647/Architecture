#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <list>
#include <unordered_map>

class Node {
    int key;
    int value;
    int freq;

    Node(int _key, int _value, int _freq) : key(_key), value(_value), freq(_freq) {}
};

class LFUCache {
public:
    LFUCache(int capacity);
    int get(int key);
    void put(int key, int value);

private:
    // key: 频次, value: 数据链表
    std::unordered_map<int, std::list<Node>> m_freqMap;
    // key: key, value: 数据指针
    std::unordered_map<int, std::list<Node>::iterator> m_keyMap;
    // 保存最小频次
    int m_minFreq;
    int m_capacity;
};

#endif
