/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-27 19:38:01
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-27 19:38:08
 * @FilePath: \LeetCode-Practice\Dual Pointer\1052.爱生气的书店老板\maxSatisfied.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int result = 0;
        for (int i = 0; i < customers.size(); ++i) {
            if (grumpy[i] == 0) {
                result += customers[i];
            }
        }
        int cur = result;
        for (int right = 0, left = 0; right < customers.size(); ++right) {
            if (grumpy[right] == 1) {
                cur += customers[right];
            }
            while (right - left + 1 > minutes) {
                if (grumpy[left] == 1) {
                    cur -= customers[left];
                }
                left++;
            }
            result = max(result, cur);
        }
        return result;
    }
};