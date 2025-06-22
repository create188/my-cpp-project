#pragma once
#include <string>
using namespace std;

// 商品类型类
class ProductType {
private:
    string name;
public:
    ProductType(const string& n);
    string getName() const;
    void setName(const string& n);
};