class Solution {
public:
    int numSquares(int n) {
        vector<int> nums(sqrt(n));
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = (i + 1) * (i + 1);
        }
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = nums[i]; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - nums[i]] + 1);
            }
        }
        return dp[n];
    }
};