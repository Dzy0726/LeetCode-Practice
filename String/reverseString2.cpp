/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-03 14:33:40
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-03 14:34:07
 * @FilePath: \LeetCode-Practice\String\reverseString2.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution

class Solution {
public:
    void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseStr(string s, int k) {
        int length = s.size();
        int count = length / (2 * k);
        int comp = length % (2 * k);
        int i = 0;
        while (i < length && count > 0) {
            myReverse(i, i + k - 1, s);
            count--;
            i += 2 * k;
        }
        if (comp >= k && comp < 2 * k) {
            myReverse(i, i + k - 1, s);
            i += k;
        } else {
            myReverse(i, length - 1, s);
        }
        return s;
    }
};

// Standard Solution

class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            // 1. 每隔 2k 个字符的前 k 个字符进行反转
            // 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
            if (i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k );
            } else {
                // 3. 剩余字符少于 k 个，则将剩余字符全部反转。
                reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
};