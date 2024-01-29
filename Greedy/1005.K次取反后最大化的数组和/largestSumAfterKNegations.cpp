/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-29 18:14:45
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-29 18:14:52
 * @FilePath: \LeetCode-Practice\Greedy\1005.K次取反后最大化的数组和\largestSumAfterKNegations.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        while (k--) {
            sort(nums.begin(), nums.end());
            nums[0] = -nums[0];
        }
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;
    }
};