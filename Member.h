#pragma once
#include <string>
#include "MemberType.h"
using namespace std;

// 会员卡类
class Member {
private:
    string name;
    string phone;
    MemberType* type;
    double totalSpent;

public:
    Member(const string& n, const string& p, MemberType* t);

    // 复制构造函数
    Member(const Member& other);

    string getName() const;
    string getPhone() const;
    MemberType* getType() const;
    void setType(MemberType* t);
    double getTotalSpent() const;
    void addSpent(double amount);
    void setTotalSpent(double amount);
};