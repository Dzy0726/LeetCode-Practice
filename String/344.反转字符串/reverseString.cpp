/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-03 14:32:12
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-03 14:32:20
 * @FilePath: \LeetCode-Practice\String\reverseString.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0; i < s.size()/2; i++) {
            int j = s.size() - 1 - i;
            swap(s[i],s[j]);
        }
    }
};