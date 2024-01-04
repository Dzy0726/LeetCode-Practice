/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-04 12:13:42
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-04 12:14:16
 * @FilePath: \LeetCode-Practice\String\459.重复的子字符串\repeatedSubstringPattern.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// KMP Solution
class Solution {
public:
    void getNext(int *next, string s) {
        int j = 0, i = 1;
        next[0] = 0;
        for (;i < s.size(); i++) {
            while (j > 0 && s[j] != s[i] ) {
                j = next[j - 1];
            }
            if (s[j] == s[i]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s) {
        int next[s.size()];
        getNext(next, s);
        if ((next[s.size() - 1] > 0) && (s.size() % (s.size() - next[s.size() - 1]) == 0)){
            return true;
        } else {
            return false;
        }
    }
};

// Magic Solution
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string t = s + s;
        t.erase(t.begin());
        t.erase(t.end() - 1);
        if (t.find(s) != std::string::npos)  {
            return true; 
        }
        return false;
    }
};