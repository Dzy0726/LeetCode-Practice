/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-03 14:39:07
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-03 14:39:40
 * @FilePath: \LeetCode-Practice\String\151.反转字符串中的单词\reverseWords.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    string reverseWords(string s) {
        string result;
        int i = s.size() - 1;
        int j = i;
        bool stop = false;
        while (i >= 0) {
            if (s[i] == ' ' && stop == false) {
                i--;
                j--;
            } else if (s[i] == ' ' && stop == true) {
                
                result.append(s, i + 1, j - i);
                result.push_back(' ');
                stop = false;
                i--;
                j = i;
            } else {
                i--;
                stop = true;
            }
        }
        if (stop == 1) {
            result.append(s, i + 1, j - i);
        }
        if (result[result.size() - 1] == ' ') {
            result.resize(result.size() - 1);
        }
        return result;
    }
};

// Standard Solution
class Solution {
public:
    void removeSpace(string& s) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < s.size(); fastIndex++) {
            if (s[fastIndex] != ' ') {
                if (slowIndex != 0) {
                    s[slowIndex++] = ' ';
                }
                while (fastIndex < s.size() && s[fastIndex] != ' ') {
                    s[slowIndex++] = s[fastIndex++];
                }
            }
        }
        s.resize(slowIndex);
    }

    void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    string reverseWords(string s) {
        removeSpace(s);
        myReverse(0, s.size() - 1, s);
        int start = 0;
        for (int i = 0; i <= s.size(); i++) {
            if (s[i] == ' ' || i == s.size() ) {
                myReverse(start, i - 1, s);
                start = i + 1;
            }
        }
        return s;
    }
};
