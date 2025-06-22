#include "MemberType.h"
using namespace std;

MemberType::MemberType(const string& n, double d) : name(n), discount(d) {}

string MemberType::getName() const {
    return name;
}

double MemberType::getDiscount() const {
    return discount;
}

void MemberType::setDiscount(double d) {
    discount = d;
}

void MemberType::setName(const string& n) {
    name = n;
}