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

    int get(int key) {
        auto itr = m_map.find(key);
        if (itr == m_map.end()) {
            return -1;
        }

        auto nodeItr = itr->second;
        int value = nodeItr->value;
        m_list.erase(nodeItr);
        m_list.emplace_front(key, value);
        m_map[key] = m_list.begin();
        return value;

        return -1;
    }

    void put(int key, int value) {
        auto itr = m_map.find(key);
        if (itr != m_map.end()) { // 存在
            // 更新
            auto nodeItr = itr->second;
            m_list.erase(nodeItr);
            m_list.emplace_front(key, value);
            m_map[key] = m_list.begin();
        } else { // 不存在
            if (m_list.size() >= m_capacity) { // 无空间
                auto& backNode = m_list.back();
                m_map.erase(backNode.key);
                m_list.pop_back();
            } 
            m_list.emplace_front(key, value);
            m_map[key] = m_list.begin();
            m_capacity++;
        }
    }

private:
    std::list<Node> m_list;
    std::unordered_map<int, std::list<Node>::iterator> m_map;
    int m_capacity;
};

#endif