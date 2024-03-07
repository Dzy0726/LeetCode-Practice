class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> word(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i < s.length() + 1; i++) {
            for (int j = 0; j < i; j++) {
                string sub = s.substr(j, i - j);
                if (word.find(sub) != word.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.length()];
    }
};