/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-03 14:40:33
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-03 14:40:40
 * @FilePath: \LeetCode-Practice\String\卡码网55.右旋字符串\rightReverse.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
#include <iostream>

using namespace std;

void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
int main(){
    int k;
    string s;
    cin >> k;
    cin >> s;
    myReverse(0, s.size() - 1 - k, s);
    myReverse(s.size() - k, s.size() - 1, s);
    myReverse(0, s.size() - 1, s);
    cout << s << endl;
}