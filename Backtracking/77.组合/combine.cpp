class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backTracking(int n, int k, int start) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = start; i <= n; i++) {
            path.push_back(i);
            backTracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backTracking(n, k, 1);
        return result;
    }
};


// 剪枝
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) { // 优化的地方
            path.push_back(i); // 处理节点
            backtracking(n, k, i + 1);
            path.pop_back(); // 回溯，撤销处理的节点
        }
    }
public:

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};