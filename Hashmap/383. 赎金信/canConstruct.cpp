class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> isExist(26, 0);
        for (auto i : magazine) {
            isExist[i - 'a']++;
        }
        for (auto i : ransomNote) {
            if (isExist[i - 'a'] == 0) {
                return false;
            } else {
                isExist[i - 'a']--;
            }
        }
        return true;
    }
};