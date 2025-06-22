#include "Supermarket.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

Supermarket::Supermarket() {
    silverType = new MemberType("白银会员", 0.88);
    goldType = new MemberType("黄金会员", 0.8);
    diamondType = new MemberType("钻石会员", 0.7);

    memberTypeMgr.add(silverType);
    memberTypeMgr.add(goldType);
    memberTypeMgr.add(diamondType);

    productTypeMgr.add(new ProductType("食品"));
    productTypeMgr.add(new ProductType("日用品"));
    productTypeMgr.add(new ProductType("水果"));
    productTypeMgr.add(new ProductType("蔬菜"));
    productTypeMgr.add(new ProductType("五谷杂粮"));
    productTypeMgr.add(new ProductType("饮料"));
    productTypeMgr.add(new ProductType("调料"));
    productTypeMgr.add(new ProductType("海鲜"));
    productTypeMgr.add(new ProductType("熟食"));
    productTypeMgr.add(new ProductType("零食"));
    productTypeMgr.add(new ProductType("化妆品"));
    productTypeMgr.add(new ProductType("洗护用品"));
    productTypeMgr.add(new ProductType("酒水"));
    productTypeMgr.add(new ProductType("木具"));
    productTypeMgr.add(new ProductType("家电"));
    productTypeMgr.add(new ProductType("服装"));

    loadProducts();
    loadMembers();
}

void Supermarket::saveMembers() {
    ofstream ofs("members.txt");
    for (auto m : memberMgr.getAll()) {
        ofs << m->getName() << "," << m->getPhone() << "," << m->getType()->getName() << "," << m->getTotalSpent() << endl;
    }
    ofs.close();
}

void Supermarket::loadMembers() {
    ifstream ifs("members.txt");
    if (!ifs) return;
    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        string name, phone, typeName, spentStr;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, typeName, ',');
        getline(ss, spentStr, ',');
        MemberType* type = memberTypeMgr.find(typeName);
        if (!type) {
            type = new MemberType(typeName, 1.0);
            memberTypeMgr.add(type);
        }
        Member* m = new Member(name, phone, type);
        m->setTotalSpent(atof(spentStr.c_str()));
        memberMgr.add(m);
    }
    ifs.close();
}

// 检查商品是否已存在，避免重复
void Supermarket::addProduct() {
    string name, typeName;
    double price;
    string priceUnit;
    int byWeightChoice;
    bool isByWeight = false;
    safeInputStr(name, "商品名: ");
    if (productMgr.find(name)) {
        cout << "该商品已存在，不能重复添加！" << endl;
        return;
    }
    safeInputStr(typeName, "商品类型: ");
    ProductType* type = productTypeMgr.find(typeName);
    if (!type) {
        cout << "错误：商品类型不存在，请先通过菜单3手动添加该商品类型！" << endl;
        return;
    }
    safeInput(byWeightChoice, "商品销售方式（1-称重 2-按件）: ");
    if (byWeightChoice == 1) {
        isByWeight = true;
        safeInput(price, "请输入售价（数字）: ");
        int unitChoice;
        safeInput(unitChoice, "请选择单位（1-元/斤 2-元/两 3-元/千克 4-自定义）: ");
        switch (unitChoice) {
        case 1: priceUnit = "元/斤"; break;
        case 2: priceUnit = "元/两"; break;
        case 3: priceUnit = "元/千克"; break;
        case 4: safeInputStr(priceUnit, "请输入自定义单位（如元/箱）: "); break;
        default: priceUnit = "元/斤"; break;
        }
    }
    else {
        isByWeight = false;
        safeInput(price, "请输入售价（数字）: ");
        priceUnit = "元/个";
    }
    productMgr.add(new Product(name, type, price, priceUnit, isByWeight));
    saveProducts();
    cout << "添加成功\n";
}

// 检查手机号是否已存在，避免重复
void Supermarket::addMember() {
    string name, phone;
    safeInputStr(name, "请输入会员姓名: ");
    safeInputStr(phone, "请输入会员手机号: ");
    if (findMemberByPhone(memberMgr, phone)) {
        cout << "该手机号已注册会员，不能重复添加！" << endl;
        return;
    }
    MemberType* type = silverType;
    memberMgr.add(new Member(name, phone, type));
    saveMembers();
    cout << "会员卡注册成功，初始等级：白银会员" << endl;
}

void Supermarket::addProductType() {
    string name;
    safeInputStr(name, "商品类型名: ");
    productTypeMgr.add(new ProductType(name));
    cout << "添加成功\n";
}

void Supermarket::addMemberType() {
    string name; double discount;
    safeInputStr(name, "会员卡类型名: ");
    safeInput(discount, "折扣(如0.95): ");
    memberTypeMgr.add(new MemberType(name, discount));
    cout << "添加成功\n";
}

void Supermarket::modifyProduct() {
    string name;
    safeInputStr(name, "商品名: ");
    Product* p = productMgr.find(name);
    if (!p) throw runtime_error("商品不存在");
    double price;
    safeInput(price, "新售价: ");
    p->setPrice(price);
    saveProducts();
    cout << "修改成功\n";
}

void Supermarket::updateProduct() {
    string name;
    safeInputStr(name, "请输入要更新的商品名: ");
    vector<Product*> found;
    for (auto p : productMgr.getAll()) {
        if (p->getName() == name) found.push_back(p);
    }
    if (found.empty()) {
        cout << "未找到该商品！" << endl;
        return;
    }
    cout << "找到以下商品，请选择要更新的编号：" << endl;
    for (size_t i = 0; i < found.size(); ++i) {
        cout << i + 1 << ". 售价: " << found[i]->getPrice() << found[i]->getPriceUnit()
            << " 库存: " << found[i]->getStock() << " 类型: " << (found[i]->getType() ? found[i]->getType()->getName() : "") << endl;
    }
    int idx;
    safeInput(idx, "请输入编号: ");
    if (idx < 1 || idx >(int)found.size()) {
        cout << "编号无效！" << endl;
        return;
    }
    Product* p = found[idx - 1];
    double price;
    safeInput(price, "新售价: ");
    string unit;
    safeInputStr(unit, "新单位（直接输入，如元/斤）: ");
    p->setPriceUnit(unit);
    int byWeight;
    safeInput(byWeight, "是否设置为称重销售？(1-是 0-否): ");
    p->setIsByWeight(byWeight == 1);
    p->setPrice(price);
    saveProducts();
    cout << "商品信息已更新！" << endl;
}

void Supermarket::modifyMember() {
    string phone;
    safeInputStr(phone, "会员手机号: ");
    Member* m = findMemberByPhone(memberMgr, phone);
    if (!m) throw runtime_error("会员不存在");
    cout << "请选择新会员卡类型（1-白银 2-黄金 3-钻石）: ";
    int typeChoice;
    safeInput(typeChoice);
    MemberType* type = silverType;
    if (typeChoice == 2) type = goldType;
    else if (typeChoice == 3) type = diamondType;
    m->setType(type);
    saveMembers();
    cout << "修改成功\n";
}

void Supermarket::deleteProduct() {
    string name;
    safeInputStr(name, "商品名: ");
    productMgr.remove(name);
    saveProducts();
    cout << "删除成功\n";
}

void Supermarket::deleteMember() {
    string phone;
    safeInputStr(phone, "会员手机号: ");
    Member* m = findMemberByPhone(memberMgr, phone);
    if (!m) {
        cout << "未找到该会员！" << endl;
        return;
    }
    memberMgr.remove(m->getName());
    saveMembers();
    cout << "会员卡已注销（删除）成功\n";
}

void Supermarket::setPromotion() {
    string name;
    safeInputStr(name, "商品名: ");
    Product* p = productMgr.find(name);
    if (!p) throw runtime_error("商品不存在");
    int promo;
    safeInput(promo, "是否促销(1是0否): ");
    if (promo == 1) {
        double discount;
        safeInput(discount, "请输入促销折扣(如0.8表示8折，1表示不打折): ");
        if (discount <= 0 || discount > 1) {
            cout << "折扣输入有误，已设为不打折。\n";
            discount = 1.0;
        }
        p->setPromotion(true, discount);
    }
    else {
        p->setPromotion(false, 1.0);
    }
    saveProducts();
    cout << "设置成功\n";
}

void Supermarket::stockProduct() {
    string name;
    safeInputStr(name, "商品名: ");
    Product* p = productMgr.find(name);
    if (!p) throw runtime_error("商品不存在");
    double inPrice; int qty;
    safeInput(inPrice, "进货价: ");
    safeInput(qty, "数量: ");
    string unit;
    if (p->getIsByWeight()) {
        int unitChoice;
        safeInput(unitChoice, "请选择进货单位（1-斤 2-两 3-千克 4-自定义）: ");
        switch (unitChoice) {
        case 1: unit = "斤"; break;
        case 2: unit = "两"; break;
        case 3: unit = "千克"; break;
        case 4: safeInputStr(unit, "请输入自定义单位: "); break;
        default: unit = "斤"; break;
        }
    }
    else {
        unit = "个";
    }
    time_t now = time(0);
    p->addStock(inPrice, qty, now, unit);
    saveProducts();
    cout << "进货成功\n";
}

void Supermarket::sellProduct() {
    string name;
    safeInputStr(name, "商品名: ");
    Product* p = productMgr.find(name);
    if (!p) throw runtime_error("商品不存在");
    int qty;
    string unit;
    if (p->getIsByWeight()) {
        int unitChoice;
        safeInput(unitChoice, "请选择售卖单位（1-斤 2-两 3-千克 4-自定义）: ");
        switch (unitChoice) {
        case 1: unit = "斤"; break;
        case 2: unit = "两"; break;
        case 3: unit = "千克"; break;
        case 4: safeInputStr(unit, "请输入自定义单位: "); break;
        default: unit = "斤"; break;
        }
    }
    else {
        unit = "个";
    }
    safeInput(qty, string("数量(") + unit + "): ");
    int hasMember;
    safeInput(hasMember, "顾客是否有会员卡？(1-有 0-无): ");
    double total = 0;
    time_t now = time(0);
    if (hasMember == 1) {
        string phone;
        safeInputStr(phone, "请输入会员手机号: ");
        Member* m = findMemberByPhone(memberMgr, phone);
        if (!m) {
            cout << "未找到会员，请先注册会员卡。\n";
            return;
        }
        if (p->getPromotion()) {
            total = p->getPrice() * qty * p->getPromotionDiscount();
            cout << "商品促销，会员不再享受会员折扣。\n";
        }
        else {
            total = p->getPrice() * qty * m->getType()->getDiscount();
        }
        try {
            p->sell(qty);
            p->addSaleRecord(qty, now);
            m->addSpent(total);
            if (m->getType() == silverType && m->getTotalSpent() >= 1000) {
                m->setType(goldType);
                cout << "恭喜，已升级为黄金会员！" << endl;
            }
            if (m->getType() == goldType && m->getTotalSpent() >= 2000) {
                m->setType(diamondType);
                cout << "恭喜，已升级为钻石会员！" << endl;
            }
            saveProducts();
            saveMembers();
            cout << "销售成功，应收: " << total << "，会员等级：" << m->getType()->getName()
                << "，累计消费：" << m->getTotalSpent() << endl;
        }
        catch (exception& e) {
            cout << "销售失败: " << e.what() << endl;
        }
    }
    else {
        if (p->getPromotion()) {
            total = p->getPrice() * qty * p->getPromotionDiscount();
        }
        else {
            total = p->getPrice() * qty;
        }
        try {
            p->sell(qty);
            p->addSaleRecord(qty, now);
            saveProducts();
            cout << "销售成功，应收: " << total << endl;
        }
        catch (exception& e) {
            cout << "销售失败: " << e.what() << endl;
        }
        int reg;
        safeInput(reg, "是否要注册会员卡？(1-是 0-否): ");
        if (reg == 1) addMember();
    }
}

// 退货操作，减少销售记录和库存
void Supermarket::returnProduct() {
    string name;
    safeInputStr(name, "退货商品名: ");
    Product* p = productMgr.find(name);
    if (!p) {
        cout << "未找到该商品！" << endl;
        return;
    }
    int qty;
    safeInput(qty, "退货数量: ");
    vector<SaleRecord>& sales = p->getSaleRecordsNonConst();
    int remain = qty;
    for (int i = (int)sales.size() - 1; i >= 0 && remain > 0; --i) {
        if (sales[i].quantity <= remain) {
            remain -= sales[i].quantity;
            sales.erase(sales.begin() + i);
        }
        else {
            sales[i].quantity -= remain;
            remain = 0;
        }
    }
    p->addStock(p->getPrice(), qty, time(0), p->getPriceUnit());
    p->decreaseTotalSold(qty);
    saveProducts();
    cout << "退货成功，库存已增加，销量已减少。\n";
}

void Supermarket::queryProduct() {
    cout << "1. 按名称查询 2. 按价格区间查询 3. 显示全部\n";
    int op;
    safeInput(op);
    if (op == 1) {
        string name; safeInputStr(name, "商品名: ");
        Product* p = productMgr.find(name);
        if (p) cout << *p << endl;
        else cout << "未找到\n";
    }
    else if (op == 2) {
        double minp, maxp;
        safeInput(minp, "最低价格: ");
        safeInput(maxp, "最高价格: ");
        for (size_t i = 0; i < productMgr.getAll().size(); ++i) {
            Product* p = productMgr.getAll()[i];
            if (p->getPrice() >= minp && p->getPrice() <= maxp)
                cout << *p << endl;
        }
    }
    else {
        for (size_t i = 0; i < productMgr.getAll().size(); ++i)
            cout << *(productMgr.getAll()[i]) << endl;
    }
}

void Supermarket::queryMember() {
    for (size_t i = 0; i < memberMgr.getAll().size(); ++i) {
        Member* m = memberMgr.getAll()[i];
        cout << "会员姓名: " << m->getName()
            << " 手机号: " << m->getPhone()
            << " 会员等级: " << m->getType()->getName()
            << " 累计消费: " << m->getTotalSpent() << endl;
    }
}

// 按商品类型统计销售额
void Supermarket::statistics() {
    cout << "统计区间起始时间(格式: YYYY-MM-DD HH:MM:SS): ";
    string startStr, endStr;
    getline(cin, startStr);
    cout << "结束时间(格式: YYYY-MM-DD HH:MM:SS): ";
    getline(cin, endStr);
    time_t start, end;
    try {
        start = parseDateTime(startStr);
        end = parseDateTime(endStr);
    }
    catch (exception& e) {
        cout << "输入错误: " << e.what() << endl;
        return;
    }
    map<string, double> typeSales;
    for (auto p : productMgr.getAll()) {
        double amount = 0;
        const vector<SaleRecord>& records = p->getSaleRecords();
        for (const auto& rec : records) {
            if (rec.time >= start && rec.time <= end)
                amount += rec.quantity * p->getPrice();
        }
        if (p->getType())
            typeSales[p->getType()->getName()] += amount;
    }
    if (typeSales.empty()) {
        cout << "无数据\n";
        return;
    }
    cout << "区间内各商品类型销售额统计：" << endl;
    for (const auto& kv : typeSales) {
        cout << kv.first << "：销售额 " << kv.second << " 元" << endl;
    }
    auto maxIt = max_element(typeSales.begin(), typeSales.end(),
        [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second < b.second;
        });
    cout << "销售额最高的商品类型：" << maxIt->first << "，销售额：" << maxIt->second << " 元" << endl;
}

void Supermarket::help() {
    cout << "本系统支持商品/会员卡/类型的增删改查，进货、销售、促销、统计等功能。\n";
    cout << "销售和进货均可选择单位，销售时可选择是否会员，会员享受会员卡折扣，商品促销时优先用促销折扣。\n";
    cout << "会员卡注册仅需姓名和手机号，初次注册只能为白银会员，消费累计满1000元升级黄金会员，满2000元升级钻石会员。\n";
    cout << "如需帮助请联系管理员。\n";
}

void Supermarket::saveProducts() {
    ofstream ofs("products.txt");
    for (size_t i = 0; i < productMgr.getAll().size(); ++i) {
        productMgr.getAll()[i]->save(ofs);
    }
    ofs.close();
}

void Supermarket::loadProducts() {
    ifstream ifs("products.txt");
    if (!ifs) return;
    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        string name, typeName, priceStr, unit, byWeightStr, promoStr, promoDiscStr, soldStr, stockStr, saleStr;
        getline(ss, name, ',');
        getline(ss, typeName, ',');
        getline(ss, priceStr, ',');
        getline(ss, unit, ',');
        getline(ss, byWeightStr, ',');
        getline(ss, promoStr, ',');
        getline(ss, promoDiscStr, ',');
        getline(ss, soldStr, ',');
        getline(ss, stockStr, ',');
        getline(ss, saleStr);

        double price = atof(priceStr.c_str());
        bool isByWeight = atoi(byWeightStr.c_str()) != 0;
        bool isPromotion = atoi(promoStr.c_str()) != 0;
        double promoDisc = atof(promoDiscStr.c_str());
        int sold = atoi(soldStr.c_str());

        Product* prod = new Product(name, typeName, price, unit, isByWeight, isPromotion, promoDisc, sold);
        ProductType* type = productTypeMgr.find(typeName);
        if (!type) {
            type = new ProductType(typeName);
            productTypeMgr.add(type);
        }
        prod->setType(type);
        prod->loadStock(stockStr);
        prod->loadSaleRecords(saleStr);
        productMgr.add(prod);
    }
    ifs.close();
}