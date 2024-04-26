/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-26 23:29:12
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-26 23:29:18
 * @FilePath: \LeetCode-Practice\Dual Pointer\2090.半径为 k 的子数组平均值\getAverages.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> result(nums.size());
        long long  sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            result[i] = -1;
            if (i < 2 * k) {
                sum += nums[i];
            }
        }
        if (nums.size() < k) {
            return result;
        }

        for (int right = k, left = 0; right < nums.size() - k; ++right) {
            sum += nums[right + k];
            while (right - left > k) {
                sum -= nums[left];
                left++;
            }
            result[right] = sum / (2 * k + 1);
        }
        return result;
    }
};