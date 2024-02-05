/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-05 18:37:21
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-05 18:56:52
 * @FilePath: \LeetCode-Practice\Dynamic Programming\343.整数拆分\integerBreak.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(59);
        dp[0] = 0, dp[1] = 0, dp[2] = 1, dp[3] = 2, dp[4] = 4, dp[5] = 6, dp[6] = 9;
        for (int i = 7; i <= n; i++) {
            dp[i] = 3 * dp[i - 3];
        }
        return dp[n];
    }
};

// Correct Solution
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            int curMax = 0;
            for (int j = 1; j < i - 1; j++) {
                curMax = max(j * (i - j), j * dp[i - j]);
                dp[i] = max(dp[i], curMax);
            }
        }
        return dp[n];
    }
};