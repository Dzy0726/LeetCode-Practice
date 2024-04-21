/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-21 23:43:39
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-21 23:52:33
 * @FilePath: \LeetCode-Practice\Dual Pointer\1456.定长子串中元音的最大数目\maxVowels.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    bool isVowel(char c) {
        string vowels = "aeiou";
        return vowels.find(c) != string::npos;
    }
    int maxVowels(string s, int k) {
        int maxV = INT_MIN;
        int left = 0;
        int curWindowCount = 0;
        for (int right = 0; right < s.size(); ++right) {
            if (isVowel(s[right])) {
                curWindowCount++;
            }
            while (right - left + 1 > k) {
                if (isVowel(s[left])) {
                    curWindowCount--;
                }
                left++;
            }
            if (right - left + 1 == k) {
                maxV = max(maxV, curWindowCount);
            }
        }
        return maxV;
    }
};