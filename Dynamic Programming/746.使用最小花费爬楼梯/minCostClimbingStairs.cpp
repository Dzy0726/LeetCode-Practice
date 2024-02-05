/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-05 16:58:10
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-05 16:58:15
 * @FilePath: \LeetCode-Practice\Dynamic Programming\746.使用最小花费爬楼梯\minCostClimbingStairs.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1);
        dp[0] = 0, dp[1] = 0;
        for (int i = 2; i <= n; i++) {
            dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);
        }
        return dp[n];
    }
};