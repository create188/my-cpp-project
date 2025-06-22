#include "ProductType.h"
using namespace std;

ProductType::ProductType(const string& n) : name(n) {}

string ProductType::getName() const {
    return name;
}

void ProductType::setName(const string& n) {
    name = n;
}