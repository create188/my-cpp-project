#define _CRT_SECURE_NO_WARNINGS
#include "Supermarket.h"
#include "Utils.h"
#include <iostream>
using namespace std;

int main() {
    Supermarket sm;
    while (true) {
        cout << "\n==== 超市管理系统 ====\n";
        cout << "1. 添加商品\n2. 注册会员卡\n3. 添加商品类型\n4. 添加会员卡类型\n";
        cout << "5. 修改商品\n6. 修改会员卡\n7. 删除商品\n8. 删除会员卡\n";
        cout << "9. 设置商品促销\n10. 商品进货\n11. 商品销售\n";
        cout << "12. 查询商品\n13. 查询会员卡\n14. 统计分析\n15. 帮助\n";
        cout << "16. 更新商品信息\n17. 商品退货\n0. 退出\n";
        cout << "请选择: ";
        int op;
        safeInput(op);
        try {
            switch (op) {
            case 1: sm.addProduct(); break;
            case 2: sm.addMember(); break;
            case 3: sm.addProductType(); break;
            case 4: sm.addMemberType(); break;
            case 5: sm.modifyProduct(); break;
            case 6: sm.modifyMember(); break;
            case 7: sm.deleteProduct(); break;
            case 8: sm.deleteMember(); break;
            case 9: sm.setPromotion(); break;
            case 10: sm.stockProduct(); break;
            case 11: sm.sellProduct(); break;
            case 12: sm.queryProduct(); break;
            case 13: sm.queryMember(); break;
            case 14: sm.statistics(); break;
            case 15: sm.help(); break;
            case 16: sm.updateProduct(); break;
            case 17: sm.returnProduct(); break;
            case 0: sm.saveProducts(); sm.saveMembers(); return 0;
            default: cout << "无效选择\n";
            }
        }
        catch (exception& e) {
            cout << "错误: " << e.what() << endl;
        }
    }
    return 0;
}