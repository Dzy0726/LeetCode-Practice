/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-22 00:57:13
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-22 01:00:24
 * @FilePath: \LeetCode-Practice\Dual Pointer\2134.最少交换次数来组合所有的 1 II\minSwaps.cpp
 * @Description: 要学会转化问题
 *              1.环形的处理：把数组复制一遍，就相当于处理环的首尾相邻了
 *              2.如何把问题抽象成定长滑动窗口的问题？=》数组中 1 的数量是固定的，只要窗口长度为1，就可以计算把这个窗口全部填充为1需要的次数，算是暴力枚举
 *              3.因为可以直接交换任意位置的两个数，所以窗口内0的数量就是要交换的次数
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int countOne = 0;
        int n = nums.size();
        for (int num : nums) {
            if (num == 1) countOne++;
        }
        for (int i = 0; i < n; i++) {
            nums.push_back(nums[i]);
        }
        int left = 0;
        int countZero = 0;
        int result = INT_MAX;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) countZero++;
            while (right - left + 1 > countOne) {
                if (nums[left] == 0) countZero--;
                left++;
            }
            if (right - left + 1 == countOne) {
                result = min(result, countZero);
            }
        }
        return result;
    }
};