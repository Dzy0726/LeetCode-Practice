class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT32_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i];
            if (count > result) {
                result = count;
            }
            if (count < 0) {
                count = 0;
            }
        }
        return result;
    }
};

// dp methods

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp = nums;
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i], dp[i - 1] + nums[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};