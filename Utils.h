#pragma once
#include <string>
#include <iostream>
#include <limits>
#include <ctime>
#include "Member.h"
#include "Manager.h"
using namespace std;

// 日期字符串转time_t
time_t parseDateTime(const string& dateStr);

// 输入数字安全读取
template<typename T>
void safeInput(T& var, const string& prompt = "") {
    while (true) {
        if (!prompt.empty()) cout << prompt;
        cin >> var;
        if (cin.fail()) {
            cout << "输入有误，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

// 输入字符串安全读取
void safeInputStr(string& var, const string& prompt = "");

// 通过手机号查找会员
Member* findMemberByPhone(Manager<Member>& memberMgr, const string& phone);