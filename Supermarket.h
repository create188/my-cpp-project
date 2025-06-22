#pragma once
#include "Manager.h"
#include "ProductType.h"
#include "Product.h"
#include "MemberType.h"
#include "Member.h"
using namespace std;

// 自定义异常类
class SupermarketException : public exception {
private:
    string message;
public:
    SupermarketException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// 超市系统主类
class Supermarket {
private:
    Manager<ProductType> productTypeMgr;
    Manager<Product> productMgr;
    Manager<MemberType> memberTypeMgr;
    Manager<Member> memberMgr;

    MemberType* silverType;
    MemberType* goldType;
    MemberType* diamondType;

public:
    Supermarket();
    void menu();
    void addProduct();
    void addMember();
    void addProductType();
    void addMemberType();
    void modifyProduct();
    void updateProduct();
    void modifyMember();
    void deleteProduct();
    void deleteMember();
    void setPromotion();
    void stockProduct();
    void sellProduct();
    void returnProduct();
    void queryProduct();
    void queryMember();
    void statistics();
    void help();

    void saveProducts();
    void loadProducts();
    void saveMembers();
    void loadMembers();
};