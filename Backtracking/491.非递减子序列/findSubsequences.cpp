// My Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        if (path.size() >= 2) {
            result.push_back(path);
        }
        if (startIndex >= nums.size()) {
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            if (path.size() == 0) {
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            } else {
                if (nums[i] >= path[path.size() - 1]) {
                    path.push_back(nums[i]);
                    backtracking(nums, i + 1);
                    path.pop_back();
                }
            }
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        sort(result.begin(), result.end());
        auto it = unique(result.begin(), result.end());
        result.erase(it, result.end());
        return result;
    }
};


// A Better Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        if (startIndex > nums.size()) return;
        if (path.size() >= 2) result.push_back(path);
        int used[201] = {0};
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) continue;
            path.push_back(nums[i]);
            used[nums[i] + 100] = 1;
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};