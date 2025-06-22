#include "Member.h"
using namespace std;

Member::Member(const string& n, const string& p, MemberType* t)
    : name(n), phone(p), type(t), totalSpent(0) {
}

// 复制构造函数实现
Member::Member(const Member& other)
    : name(other.name), phone(other.phone), type(other.type), totalSpent(other.totalSpent) {
}

string Member::getName() const {
    return name;
}

string Member::getPhone() const {
    return phone;
}

MemberType* Member::getType() const {
    return type;
}

void Member::setType(MemberType* t) {
    type = t;
}

double Member::getTotalSpent() const {
    return totalSpent;
}

void Member::addSpent(double amount) {
    totalSpent += amount;
}

void Member::setTotalSpent(double amount) {
    totalSpent = amount;
}