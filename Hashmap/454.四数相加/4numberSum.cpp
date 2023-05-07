class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> map12;        
        unordered_map<int, int> map34;
        int n = nums1.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int sum12 = nums1[i] + nums2[j];
                int sum34 = nums3[i] + nums4[j];
                if (map12.find(sum12) == map12.end()) {
                    map12.insert(pair<int, int> (sum12, 1));
                } else {
                    auto it = map12.find(sum12);
                    it->second++;
                }
                if (map34.find(sum34) == map34.end()) {
                    map34.insert(pair<int, int> (sum34, 1));
                } else {
                    auto its = map34.find(sum34);
                    its->second++;
                }
            }
        }
        int count = 0;
        for (auto it = map12.begin(); it != map12.end(); it++) {
            auto it2 = map34.find(0 - it->first);
            if (it2 != map34.end()) {
                count = count + (it->second * it2->second);
            }
        }
        return count;
    }
};