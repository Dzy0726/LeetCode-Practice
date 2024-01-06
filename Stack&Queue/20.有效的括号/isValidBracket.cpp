/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-06 16:08:11
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-06 16:08:36
 * @FilePath: \LeetCode-Practice\Stack&Queue\20.有效的括号\isValidBracket.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    bool isValid(string s) {
        stack <char> bracket;
        unordered_map<char, char> map = {
        {'}', '{'},
        {']', '['},
        {')', '('}
    };
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                bracket.push(s[i]);
            } else {
                if (bracket.empty()) {
                    return false;
                }
                if (map[s[i]] != bracket.top()) {
                    return false;
                } else {
                    bracket.pop();
                }               
            }
        }
        if (!bracket.empty()) {
            return false;
        }
        return true;
    }
};

// A Better Solution
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false; // 如果s的长度为奇数，一定不符合要求
        stack<char> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') st.push(')');
            else if (s[i] == '{') st.push('}');
            else if (s[i] == '[') st.push(']');
            // 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
            // 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
            else if (st.empty() || st.top() != s[i]) return false;
            else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
        }
        // 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
        return st.empty();
    }
};