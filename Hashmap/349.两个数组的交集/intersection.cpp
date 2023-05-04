class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> my_map;        
        vector<int> res;
        for (int i = 0; i < nums1.size(); i++) {
            my_map[nums1[i]] = 1;
        }
        for (int i = 0; i < nums2.size(); i++) {
            if(my_map[nums2[i]] == 1) {
                my_map[nums2[i]] = 2;
            }
        }
        for (const auto &pair : my_map) {
            if(pair.second == 2) {
                res.push_back(pair.first);
            }
        }
        return res;
    }
};