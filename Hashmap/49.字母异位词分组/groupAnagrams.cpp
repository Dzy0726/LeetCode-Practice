/*
    First Solution: 111 / 126 个通过的测试用例 超时
    isAnagrams时间复杂度为O(n),总的复杂度大于O(n^2)
*/ 

class Solution {
public:
    bool isAnagrams(string str1, string str2) {
        if (str1.size() != str2.size())
            return false;
        unordered_map<char, int> map;
        for (int i = 0; i < str1.size(); i++) {
            map[str1[i]]++;
            map[str2[i]]--;
        }
        for (auto it : map) {
            if (it.second != 0)
                return false;
        }
        return true;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        vector<int> flag(strs.size(), 0);
        for (int i = 0; i < strs.size(); i++) {
            vector<string> group;
            if (flag[i] == 0) {
                group.push_back(strs[i]);
                flag[i] = 1;
            } else {
                continue;
            }
            for (int j = i + 1; j < strs.size(); j++) {
                if (flag[j] == 0 && isAnagrams(strs[i], strs[j])) {
                    group.push_back(strs[j]);
                    flag[j] = 1;
                }
            }
            result.push_back(group);
        }
        return result;
    }
};


/*
    时间复杂度为O(n * m log m)
    这里的 n 是字符串数组 strs 的长度，m 是字符串的平均长度。
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> map;
        for (string str : strs) {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            map[tmp].push_back(str);
        }
        for (auto it : map) {
            result.push_back(it.second);
        }
        return result;
    }
};