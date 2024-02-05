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