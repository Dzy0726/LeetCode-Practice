class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        int count = 0;
        for (int i = 1; i < prices.size(); i++) {
            count = prices[i] - prices[i - 1];
            if (count > 0) {
                result += count;
            }
        }
        return result;
    }
};