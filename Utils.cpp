#include "Utils.h"
#include <stdexcept>
using namespace std;

// 日期字符串转time_t
time_t parseDateTime(const string& dateStr) {
    tm t = {};
#ifdef _MSC_VER
    // 使用Visual Studio编译器时使用sscanf_s
    if (sscanf_s(dateStr.c_str(), "%d-%d-%d %d:%d:%d",
        &t.tm_year, &t.tm_mon, &t.tm_mday,
        &t.tm_hour, &t.tm_min, &t.tm_sec) == 6) {
        t.tm_year -= 1900;
        t.tm_mon -= 1;
        t.tm_isdst = -1;
        return mktime(&t);
    }
#else
    // 其他编译器使用标准sscanf
    if (sscanf(dateStr.c_str(), "%d-%d-%d %d:%d:%d",
        &t.tm_year, &t.tm_mon, &t.tm_mday,
        &t.tm_hour, &t.tm_min, &t.tm_sec) == 6) 
    {
        t.tm_year -= 1900;
        t.tm_mon -= 1;
        t.tm_isdst = -1;
        return mktime(&t);
    }
#endif
    throw runtime_error("日期格式错误，应为YYYY-MM-DD HH:MM:SS");
}

// 输入字符串安全读取
void safeInputStr(string& var, const string& prompt) {
    if (!prompt.empty()) cout << prompt;
    getline(cin, var);
    while (var.empty()) {
        cout << "输入不能为空，请重新输入！" << endl;
        getline(cin, var);
    }
}

// 通过手机号查找会员
Member* findMemberByPhone(Manager<Member>& memberMgr, const string& phone) {
    for (auto m : memberMgr.getAll()) {
        if (m->getPhone() == phone) return m;
    }
    return nullptr;
}