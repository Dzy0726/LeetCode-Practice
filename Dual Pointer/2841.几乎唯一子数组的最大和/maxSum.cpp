/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-21 23:58:57
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-22 00:19:28
 * @FilePath: \LeetCode-Practice\Dual Pointer\2841.几乎唯一子数组的最大和\maxSum.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        long long result = INT_MIN;
        unordered_map<int, int> map;
        int curDiff = 0;
        long long curSum = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (map[nums[right]] == 0) {
                curDiff++;
            }
            map[nums[right]]++;
            curSum += nums[right];
            while (right - left + 1 > k) {
                if (map[nums[left]] == 1) {
                    curDiff--;
                }
                map[nums[left]]--;
                curSum -= nums[left];
                left++;
            }
            if (right - left + 1 == k && curDiff >= m) {
                if (curSum > result) {
                    result = curSum;
                }
            } 
        }
        return result == INT_MIN ? 0 : result;
    }
};