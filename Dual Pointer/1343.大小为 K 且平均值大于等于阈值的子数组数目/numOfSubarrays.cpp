/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-26 22:59:21
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-26 22:59:36
 * @FilePath: \LeetCode-Practice\Dual Pointer\1343.大小为 K 且平均值大于等于阈值的子数组数目\numOfSubarrays.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int sum = 0;
        int result = 0;
        for (int right = 0, left = 0; right < arr.size(); ++right) {
            sum += arr[right];
            while (right - left + 1 > k) {
                sum -= arr[left];
                left++;
            }
            if (right - left + 1 == k && sum >= threshold * k) {
                result++;
            } 
        }
        return result;
    }
};