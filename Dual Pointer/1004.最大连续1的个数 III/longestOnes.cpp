/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-22 23:36:55
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-22 23:37:18
 * @FilePath: \LeetCode-Practice\Dual Pointer\1004.最大连续1的个数 III\longestOnes.cpp
 * @Description: 与1493一样的做法
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int countZero = 0;
        int result = 0;
        for (int right = 0, left = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                countZero++;
            }
            while (countZero > k) {
                if (nums[left] == 0) {
                    countZero--;
                }
                left++;
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};