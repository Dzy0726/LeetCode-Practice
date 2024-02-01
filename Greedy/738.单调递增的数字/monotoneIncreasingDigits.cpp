/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-01 14:08:37
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-01 14:14:51
 * @FilePath: \LeetCode-Practice\Greedy\738.单调递增的数字\monotoneIncreasingDigits.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    bool isIncrease(string num) {
        for (int i = 0; i < num.size() - 1; i++) {
            if (num[i] > num[i + 1]) return false;
        }
        return true;
    }
    int monotoneIncreasingDigits(int n) {
        string num = to_string(n);
        if (isIncrease(num)) return n;
        int i = num.size() - 1;
        while (!isIncrease(num) && i > 0) {
            num[i] = '9';
            int pre = num[i - 1] - '0';
            pre -= 1;
            num[i - 1] = pre + '0';
            i--;
        }
        int result = stoi(num);
        return result;
    }
};

// A Better Solution