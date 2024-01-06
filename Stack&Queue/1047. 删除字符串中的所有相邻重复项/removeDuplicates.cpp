/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-06 16:27:59
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-06 16:32:40
 * @FilePath: \LeetCode-Practice\Stack&Queue\1047. 删除字符串中的所有相邻重复项\removeDuplicates.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    string removeDuplicates(string s) {
        stack <char> st;
        for (int i = 0; i < s.size(); i++) {
            if (st.empty()) {
                st.push(s[i]);
            } else {
                if (s[i] == st.top()) {
                    st.pop();
                } else {
                    st.push(s[i]);
                }
            }
        }
        string res;
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

// A Better Solution
class Solution {
public:
    string removeDuplicates(string S) {
        string result;
        for(char s : S) {
            if(result.empty() || result.back() != s) {
                result.push_back(s);
            }
            else {
                result.pop_back();
            }
        }
        return result;
    }
};