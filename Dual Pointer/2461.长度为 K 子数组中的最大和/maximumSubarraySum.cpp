/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-27 20:23:51
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-27 20:27:36
 * @FilePath: \LeetCode-Practice\Dual Pointer\2461.长度为 K 子数组中的最大和\maximumSubarraySum.cpp
 * @Description: 哈希表可以用size来看现在存了几个元素，哈希表中key对应的value为0时，就erase掉这个key，以免影响大小
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long result = 0;
        long long sum = 0;
        unordered_map<int, int> map;
        for (int right = 0, left = 0; right < nums.size(); ++right) {
            sum += nums[right];
            map[nums[right]]++;

            while (right - left + 1 > k) {
                map[nums[left]]--;
                sum -= nums[left];
                if (map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            if (map.size() == k) {
                result = max(result, sum);
            }
        }
        return result;
    }
};