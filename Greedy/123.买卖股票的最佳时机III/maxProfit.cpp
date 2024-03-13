class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(5));
        dp[0][0] = 0; //第一天不操作
        dp[0][1] = -prices[0]; //第一天第一次次买入股票
        dp[0][2] = 0; // 第一天第一次卖出股票
        dp[0][3] = -prices[0]; // 第一天第二次买入股票
        dp[0][4] = 0; // 第一天第二次卖出股票
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = 0; // 截止到第i天不操作
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]); // 截止到第i天，有一次买入，且当前是持有股票状态;要么是之前(0到i-1)买入的，要么是今天买入的
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]); // 截止到第i天,有一次卖出,且当前不持股;要么是之前i-1天卖的,要么是今天卖的
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]); // 截止到第i天,有两次买入,要么是之前买的第二次,要么是今天买的第二次
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]); // 截止到第i天,有两次卖出,要么是之前就卖了两次,要么是今天卖第二次
        }
        return dp[prices.size() - 1][4];
    }
};