/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-21 23:39:57
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-21 23:41:12
 * @FilePath: \LeetCode-Practice\Dual Pointer\2023.03.19-MHY第二题-子序列\subSq.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
/**
 * 题目内容
 * 塔子哥是一名研究生，正在研究一种基于字符串操作的算法。他最近接到了一个字符串操作的任务，需要将给定的字符串 s 转化为目标字符串 t 。然而，他发现这个任务并不是一件简单的事情。因为他只能进行两种操作：删除 s 中的一个子序列 "mhy" ，或在 s 中添加一个子序列 "mhy" 。
 * 例如，给定 s 为 "mhbdy" ，塔子哥进行一次操作后可以使 s 变成 "bd" ，或者变成 "mhmbhdyy" 。
 * 塔子哥想知道，经过若干次操作后 s 是否可以变成 t ？
 * 注：子序列在原串中的顺序也是从左到右，但可以不连续。
 * 
 * 输入描述
 * 第一行输入一个正整数 q ，代表询问的次数。
 * 接下来每两行为一次询问：每行均为一个字符串，分别代表 s 和 t 。
 * 
 * 字符串的长度均不超过 10^3
 * 
 * 输出描述
 * 输出 q 行，每行输入一行答案。若可以使 s 变成 t ，则输出 "Yes" 。否则输出 "No" 。
*/
#include <csignal>
#include <iostream>
#include <string>

using namespace std;

bool canChangeTo(string s, string t) {
    if (s.size() == t.size()) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                return false;
            }
        }
        return true;
    } else if (s.size() < t.size()) {
        int index = 0;
        string mhy = "mhy";
        int i = 0, j = 0;
        while (i < s.size() && j < t.size() && index < mhy.size()) {
            if (s[i] != t[j]) {
                if (t[j] != mhy[index]) {
                    return false;
                } else {
                    index++;
                    j++;
                }
            } else {
                i++;
                j++;
            }
        }
        if (i == s.size() && j == t.size() && index == mhy.size()) {
            return true;
        } else {
            return false;
        }
    } else {
        int index = 0;
        string mhy = "mhy";
        int i = 0, j = 0;
        while (i < s.size() && j < t.size() && index < mhy.size()) {
            if (s[i] != t[j]) {
                if (s[i] != mhy[index]) {
                    return false;
                } else {
                    index++;
                    i++;
                }
            } else {
                i++;
                j++;
            }
        }
        if (i == s.size() && j == t.size() && index == mhy.size()) {
            return true;
        } else {
            return false;
        } 
    }
}

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q * 2; i+=2) {
        string s, t;
        cin >> s >> t;
        bool result = canChangeTo(s, t);
        if (result) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}