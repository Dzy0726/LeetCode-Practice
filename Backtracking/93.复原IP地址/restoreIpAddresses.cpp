/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-23 21:30:35
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-23 21:30:44
 * @FilePath: \LeetCode-Practice\Backtracking\93.复原IP地址\restoreIpAddresses.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    vector<string> result;
    int count = 0;
    bool isValid(const string &s, int start, int end) {
        if (start > end) return false;
        if (s[start] == '0' && start != end) return false;
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') return false;
            num = num * 10 + (s[i] - '0');
            if (num > 255) return false;
        }
        return true;
    }

    void backtracking(string s, int startIndex) {
        if (count == 3) {
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
            }
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                count++;
                backtracking(s, i + 2);
                count--;
                s.erase(s.begin() + i + 1);
            } else {
                break;
            }
        }

    }
    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0);
        return result;
    }
};