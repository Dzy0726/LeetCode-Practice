/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-25 23:14:55
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-25 23:47:10
 * @FilePath: \LeetCode-Practice\Dual Pointer\1984.学生分数的最小差值\minimumDifference.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if (k == 1) return 0;
        sort(nums.begin(), nums.end());
        int minNum = INT_MAX;
        int maxNum = INT_MIN;
        int result = INT_MAX;
        for (int right = 0, left = 0; right < nums.size(); ++right) {
            maxNum = nums[right];
            minNum = nums[left];
            while (right - left + 1 > k) {
                left++;
                minNum = nums[left];
            }
            if (right - left + 1 == k) {
                result = min(maxNum - minNum, result);
            }
        }
        return result;
    }
};