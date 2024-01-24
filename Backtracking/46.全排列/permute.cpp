class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int size = 0;
    void backtracking(vector<int>& nums) {
        if (path.size() == size) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            int tmp = nums[i];
            path.push_back(nums[i]);
            nums.erase(nums.begin() + i);
            backtracking(nums);
            nums.insert(nums.begin() + i, tmp);
            path.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        size = nums.size();
        backtracking(nums);
        return result;
    }
};

// Another Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};