/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-26 21:54:45
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-26 22:29:05
 * @FilePath: \LeetCode-Practice\Dual Pointer\643.子数组最大平均数 I\findMaxAverage.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double result = -214700000.0;
        double sum = 0.0;
        for (int right = 0, left = 0; right < nums.size(); ++ right) {
            sum += nums[right];
            while (right - left + 1 > k) {
                sum -= nums[left];
                left++;
            }
            if (right - left + 1 == k) {
                if (sum / k > result) {
                    result = sum / k;
                }
            } 
        }
        return result;
    }
};