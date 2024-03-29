class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(k * 2 + 1));
        for (int i = 0; i < k * 2 + 1; i++) {
            if (i % 2 == 0) dp[0][i] = 0;
            if (i % 2 == 1) dp[0][i] = -prices[0];
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 1; j < k * 2 + 1; j++) {
                if (j % 2 == 0) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + prices[i]);
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
                }
            }
        }
        return dp[prices.size() - 1][2*k];
    }
};