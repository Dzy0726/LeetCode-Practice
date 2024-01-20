/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-20 10:57:51
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-20 10:58:12
 * @FilePath: \LeetCode-Practice\Backtracking\17.电话号码的字母组合\letterCombinations.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    vector<string> result;
    string path;
    int count = 0;
    unordered_map <string, vector<string>> myMap = {
        {"2", {"a", "b", "c"}},
        {"3", {"d", "e", "f"}},
        {"4", {"g", "h", "i"}},
        {"5", {"j", "k", "l"}},
        {"6", {"m", "n", "o"}},
        {"7", {"p", "q", "r", "s"}},
        {"8", {"t", "u", "v"}},
        {"9", {"w", "x", "y", "z"}},
    };
    void backTracking(string digits, int start) {
        if (count > digits.size()) return;
        if (path.size() == digits.size()) {
            result.push_back(path);
            return;
        }
        auto it = myMap.find(string(1,digits[start]));
        for (int i = 0; i < it ->second.size(); i++) {
            path.append(it -> second[i]);
            count++;
            backTracking(digits, start + 1);
            path.pop_back();
            count--;
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return result;
        backTracking(digits, 0);
        return result;
    }
};