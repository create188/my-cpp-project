#pragma once
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

// 商品进货记录结构体
struct StockRecord {
    double price;
    int quantity;
    time_t time;
    string unit;

    StockRecord(double p, int q, time_t t, const string& u);
    string toString() const;
    static StockRecord fromString(const string& s);
};

// 销售记录结构体
struct SaleRecord {
    int quantity;
    time_t time;

    SaleRecord(int q, time_t t);
    string toString() const;
    static SaleRecord fromString(const string& s);
};