/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-24 23:42:57
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-24 23:57:49
 * @FilePath: \LeetCode-Practice\Dual Pointer\2269.找到一个数字的 K 美丽值\divisorSubstrings.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    bool canDevided(int a, int b) {
        if (b == 0) {
            return false;
        }
        return (a % b == 0);
    }
    int divisorSubstrings(int num, int k) {
        string number = to_string(num);
        int result = 0;
        string current;
        for (int right = 0, left = 0; right < number.size(); ++right) {
            current += number[right];
            while (current.size() > k) {
                current.erase(current.begin(), current.begin() + 1);
                left++;
            }
            if (current.size() == k) {
                int curNum = stoi(current);
                if (canDevided(num, curNum)) {
                    result++;
                }
            }
        }
        return result;
    }
};