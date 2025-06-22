#include "Records.h"
#include <cstdlib>
using namespace std;

StockRecord::StockRecord(double p, int q, time_t t, const string& u)
    : price(p), quantity(q), time(t), unit(u) {
}

string StockRecord::toString() const {
    ostringstream oss;
    oss << price << "|" << quantity << "|" << time << "|" << unit;
    return oss.str();
}

StockRecord StockRecord::fromString(const string& s) {
    istringstream iss(s);
    string token;
    double price = 0;
    int quantity = 0;
    time_t t = 0;
    string unit;
    getline(iss, token, '|'); price = atof(token.c_str());
    getline(iss, token, '|'); quantity = atoi(token.c_str());
    getline(iss, token, '|'); t = atol(token.c_str());
    getline(iss, unit, '|');
    return StockRecord(price, quantity, t, unit);
}

SaleRecord::SaleRecord(int q, time_t t) : quantity(q), time(t) {}

string SaleRecord::toString() const {
    ostringstream oss;
    oss << quantity << "|" << time;
    return oss.str();
}

SaleRecord SaleRecord::fromString(const string& s) {
    istringstream iss(s);
    string token;
    int quantity = 0;
    time_t t = 0;
    getline(iss, token, '|'); quantity = atoi(token.c_str());
    getline(iss, token, '|'); t = atol(token.c_str());
    return SaleRecord(quantity, t);
}