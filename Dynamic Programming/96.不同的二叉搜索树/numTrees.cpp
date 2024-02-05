/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-05 18:59:33
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-05 20:28:50
 * @FilePath: \LeetCode-Practice\Dynamic Programming\96.不同的二叉搜索树\numTrees.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1, dp[1] = 1, dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j]; 
            }
        }
        return dp[n];
    }
};