class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); 
        for (int k = 0; k < strs.size(); k++) {
            int lastZero = 0, lastOne = 0;
            for (int a = 0; a < strs[k].size(); a++) {
                if (strs[k][a] == '0') lastZero++;
                else lastOne++;
            }
            for (int i = m; i >= lastZero; i--) {
                for (int j = n; j >= lastOne; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - lastZero][j - lastOne] + 1);
                }
            }
        }
        return dp[m][n];
    }
};