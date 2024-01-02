/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-02 18:00:33
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-02 18:00:48
 * @FilePath: \LeetCode-Practice\Hashmap\18.四数之和\fourSum.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (target >= 0 && nums[i] > target) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            long long target_ll = static_cast<long long>(target);
            for (int j = i + 1; j < nums.size(); j++) {
                if (target >= 0 && nums[i] + nums[j] > target) {
                    break;
                }
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    long long sum = static_cast<long long>(nums[i]) + nums[j] +
                                    nums[left] + nums[right];
                    if (sum > target_ll) {
                        right--;
                    } else if (sum < target_ll) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[i], nums[j],
                                                     nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        left++;
                        right--;
                    }
                }
            }
        }
        return result;
    }
};
