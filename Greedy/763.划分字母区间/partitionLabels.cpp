class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> end;
        for (int i = 0; i < s.size(); i++) {
            end[s[i]] = i;
        }
        vector<int> result;
        int oldOne = 0;
        int partition = 0;
        for (int i = 0; i < s.size(); i++) {
            partition = max(partition, end[s[i]]);
            if (i == partition && end[s[i]] >= partition) {
                result.push_back(partition - oldOne + 1);
                oldOne = partition + 1;
            }
        }
        return result;
    }
};