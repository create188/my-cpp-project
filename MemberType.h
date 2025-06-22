#pragma once
#include <string>
using namespace std;

// 会员卡类型类
class MemberType {
private:
    string name;
    double discount;
public:
    MemberType(const string& n, double d);
    string getName() const;
    double getDiscount() const;
    void setDiscount(double d);
    void setName(const string& n);
};