// My Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backTracking(vector<int>& candidates, int target) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        if (sum > target) return;
        for (int i = 0; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backTracking(candidates, target);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backTracking(candidates, target);
        for (auto& path : result) {
            sort(path.begin(), path.end());
        }
        sort(result.begin(), result.end());
        auto last = unique(result.begin(), result.end());
        result.erase(last, result.end());        
        return result;
    }
};

// A Better Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backTracking(vector<int>& candidates, int target, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        if (sum > target) return;
        for (int i = startIndex; i < candidates.size() && sum+candidates[i] <= target; i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backTracking(candidates, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backTracking(candidates, target, 0);     
        return result;
    }
};