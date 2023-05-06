class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    res.push_back(i);
                    res.push_back(j);
                }
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (map.find(target - nums[i]) == map.end()) {
                map.insert(pair<int, int>(nums[i], i));
            } else {
                res.push_back(i);
                res.push_back(map.find(target - nums[i])->second);
                break;
            } 
        }
        return res;
    }
};