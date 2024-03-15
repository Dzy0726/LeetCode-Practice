/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-03-15 17:40:49
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-03-15 17:40:57
 * @FilePath: \LeetCode-Practice\Dynamic Programming\392.判断子序列\isSubsequence.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        if (i == s.size()) return true;
        else return false;
    }
};