#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ProductType.h"
#include "Records.h"
using namespace std;

// 基础商品类（抽象基类）
class BaseProduct {
protected:
    string name;
    ProductType* type;
    double price;

public:
    BaseProduct(const string& n, ProductType* t, double p);
    virtual ~BaseProduct() = default;

    string getName() const;
    ProductType* getType() const;
    void setType(ProductType* t);
    double getPrice() const;
    void setPrice(double p);

    // 纯虚函数，子类必须实现
    virtual string getPriceUnit() const = 0;
    virtual bool getIsByWeight() const = 0;
};

// 商品类，继承自BaseProduct
class Product : public BaseProduct {
private:
    string priceUnit;
    bool isByWeight;
    bool isPromotion;
    double promotionDiscount;
    vector<StockRecord> stockRecords;
    int totalSold;
    vector<SaleRecord> saleRecords;

public:
    // 构造函数
    Product(const string& n, ProductType* t, double p, const string& unit, bool byWeight);
    Product(const string& n, const string& typeName, double p, const string& unit, bool byWeight,
        bool promo = false, double promoDisc = 1.0, int sold = 0);

    // 复制构造函数
    Product(const Product& other);

    // 析构函数
    ~Product() override = default;

    // 覆盖基类的虚函数
    string getPriceUnit() const override;
    bool getIsByWeight() const override;

    // 设置方法
    void setPriceUnit(const string& u);
    void setIsByWeight(bool b);
    bool getPromotion() const;
    double getPromotionDiscount() const;
    void setPromotion(bool promo, double discount = 1.0);

    // 库存管理
    void addStock(double inPrice, int qty, time_t t, const string& unit);  // 函数重载
    void addStock(double inPrice, int qty, time_t t);  // 函数重载
    int getStock() const;
    void sell(int qty);
    int getTotalSold() const;
    void decreaseTotalSold(int qty);

    // 记录管理
    const vector<StockRecord>& getStockRecords() const;
    void addSaleRecord(int qty, time_t t);
    const vector<SaleRecord>& getSaleRecords() const;
    vector<SaleRecord>& getSaleRecordsNonConst();
    string saleRecordsToString() const;
    void loadSaleRecords(const string& saleStr);

    // 文件操作
    void save(ofstream& ofs) const;
    void loadStock(const string& stockStr);

    // 友元函数
    friend ostream& operator<<(ostream& os, const Product& p);
};

// 运算符重载
ostream& operator<<(ostream& os, const Product& p);