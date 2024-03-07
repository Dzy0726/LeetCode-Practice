/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-05 16:21:32
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-05 16:21:39
 * @FilePath: \LeetCode-Practice\Dynamic Programming\70.爬楼梯\climbStairs.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int climbStairs(int n) {
        if (n < 3) return n;
        vector<int> dp(n + 1);
        dp[1] = 1, dp[2] = 2;
        for (int i = 3; i < n + 1; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

// 变成背包问题呢？每次可以爬1-m个楼梯？
class Solution {
public:
    int climbStairs(int n) {
        vector<int> nums = {1, 2};
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int j = 1; j < n + 1; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j >= nums[i]) dp[j] += dp[j - nums[i]];
            }
        }
        return dp[n];
    }
};