#include "Product.h"
#include <stdexcept>
#include <sstream>
using namespace std;

// BaseProduct实现
BaseProduct::BaseProduct(const string& n, ProductType* t, double p)
    : name(n), type(t), price(p) {
}

string BaseProduct::getName() const {
    return name;
}

ProductType* BaseProduct::getType() const {
    return type;
}

void BaseProduct::setType(ProductType* t) {
    type = t;
}

double BaseProduct::getPrice() const {
    return price;
}

void BaseProduct::setPrice(double p) {
    price = p;
}

// Product实现
Product::Product(const string& n, ProductType* t, double p, const string& unit, bool byWeight)
    : BaseProduct(n, t, p), priceUnit(unit), isByWeight(byWeight),
    isPromotion(false), promotionDiscount(1.0), totalSold(0) {
}

Product::Product(const string& n, const string& typeName, double p, const string& unit, bool byWeight,
    bool promo, double promoDisc, int sold)
    : BaseProduct(n, nullptr, p), priceUnit(unit), isByWeight(byWeight),
    isPromotion(promo), promotionDiscount(promoDisc), totalSold(sold) {
}

// 复制构造函数
Product::Product(const Product& other)
    : BaseProduct(other.name, other.type, other.price),
    priceUnit(other.priceUnit),
    isByWeight(other.isByWeight),
    isPromotion(other.isPromotion),
    promotionDiscount(other.promotionDiscount),
    stockRecords(other.stockRecords),
    totalSold(other.totalSold),
    saleRecords(other.saleRecords) {
}

string Product::getPriceUnit() const {
    return priceUnit;
}

bool Product::getIsByWeight() const {
    return isByWeight;
}

void Product::setPriceUnit(const string& u) {
    priceUnit = u;
}

void Product::setIsByWeight(bool b) {
    isByWeight = b;
}

bool Product::getPromotion() const {
    return isPromotion;
}

double Product::getPromotionDiscount() const {
    return promotionDiscount;
}

void Product::setPromotion(bool promo, double discount) {
    isPromotion = promo;
    promotionDiscount = discount;
}

void Product::addStock(double inPrice, int qty, time_t t, const string& unit) {
    stockRecords.push_back(StockRecord(inPrice, qty, t, unit));
}

void Product::addStock(double inPrice, int qty, time_t t) {
    addStock(inPrice, qty, t, priceUnit);
}

int Product::getStock() const {
    int stock = 0;
    for (size_t i = 0; i < stockRecords.size(); ++i)
        stock += stockRecords[i].quantity;
    return stock;
}

void Product::sell(int qty) {
    if (qty > getStock())
        throw runtime_error("库存不足");

    int remain = qty;
    for (size_t i = 0; i < stockRecords.size(); ++i) {
        if (stockRecords[i].quantity >= remain) {
            stockRecords[i].quantity -= remain;
            break;
        }
        else {
            remain -= stockRecords[i].quantity;
            stockRecords[i].quantity = 0;
        }
    }
    totalSold += qty;
}

int Product::getTotalSold() const {
    return totalSold;
}

void Product::decreaseTotalSold(int qty) {
    totalSold = (qty > totalSold ? 0 : totalSold - qty);
}

const vector<StockRecord>& Product::getStockRecords() const {
    return stockRecords;
}

void Product::addSaleRecord(int qty, time_t t) {
    saleRecords.push_back(SaleRecord(qty, t));
}

const vector<SaleRecord>& Product::getSaleRecords() const {
    return saleRecords;
}

vector<SaleRecord>& Product::getSaleRecordsNonConst() {
    return saleRecords;
}

string Product::saleRecordsToString() const {
    ostringstream oss;
    for (size_t i = 0; i < saleRecords.size(); ++i) {
        oss << saleRecords[i].toString();
        if (i != saleRecords.size() - 1) oss << ";";
    }
    return oss.str();
}

void Product::loadSaleRecords(const string& saleStr) {
    saleRecords.clear();
    istringstream iss(saleStr);
    string rec;
    while (getline(iss, rec, ';')) {
        if (!rec.empty())
            saleRecords.push_back(SaleRecord::fromString(rec));
    }
}

void Product::save(ofstream& ofs) const {
    ofs << name << "," << (type ? type->getName() : "") << "," << price << "," << priceUnit << ","
        << isByWeight << "," << isPromotion << "," << promotionDiscount << "," << totalSold << ",";
    for (size_t i = 0; i < stockRecords.size(); ++i) {
        ofs << stockRecords[i].toString();
        if (i != stockRecords.size() - 1) ofs << ";";
    }
    ofs << ",";
    ofs << saleRecordsToString();
    ofs << endl;
}

void Product::loadStock(const string& stockStr) {
    stockRecords.clear();
    istringstream iss(stockStr);
    string rec;
    while (getline(iss, rec, ';')) {
        if (!rec.empty())
            stockRecords.push_back(StockRecord::fromString(rec));
    }
}

// 运算符重载实现
ostream& operator<<(ostream& os, const Product& p) {
    os << "商品: " << p.name << " 类型: " << (p.type ? p.type->getName() : "")
        << " 售价: " << p.price << p.priceUnit << " 库存: " << p.getStock();
    if (p.isByWeight) os << " [称重销售]";
    else os << " [按件销售]";
    if (p.isPromotion) {
        os << " [促销:" << fixed << setprecision(2) << p.promotionDiscount * 10 << "折]";
        os << " 促销价: " << fixed << setprecision(2) << (p.price * p.promotionDiscount) << p.priceUnit;
    }
    return os;
}