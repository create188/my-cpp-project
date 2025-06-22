#pragma once
#include <vector>
#include <string>
using namespace std;

// 管理模板类
template<typename T>
class Manager {
private:
    vector<T*> items;

public:
    // 析构函数
    ~Manager() {
        for (size_t i = 0; i < items.size(); ++i)
            delete items[i];
    }

    void add(T* item) {
        items.push_back(item);
    }

    void remove(const string& name) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i]->getName() == name) {
                delete items[i];
                items.erase(items.begin() + i);
                break;
            }
        }
    }

    T* find(const string& name) {
        for (size_t i = 0; i < items.size(); ++i)
            if (items[i]->getName() == name) return items[i];
        return nullptr;
    }

    vector<T*>& getAll() {
        return items;
    }
};