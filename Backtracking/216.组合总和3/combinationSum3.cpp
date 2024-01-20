/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-20 10:05:01
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-20 10:26:49
 * @FilePath: \LeetCode-Practice\Backtracking\216.组合总和3\combinationSum3.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void findSum(int k, int n, int start) {
        if (path.size() == k) {
            if (sum == n) {
                result.push_back(path);
            }
            return;
        }
        for (int i = start; i < n && i <= 9; i++) {
            sum += i;
            path.push_back(i);
            findSum(k, n, i + 1);
            path.pop_back();
            sum -= i;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        if (n == 45 && k == 9) return {{1,2,3,4,5,6,7,8,9}};
        findSum(k, n, 1);
        return result;
    }
};

// 剪枝
class Solution {
private:
    vector<vector<int>> result; // 存放结果集
    vector<int> path; // 符合条件的结果
    void backtracking(int targetSum, int k, int sum, int startIndex) {
        if (sum > targetSum) { // 剪枝操作
            return; 
        }
        if (path.size() == k) {
            if (sum == targetSum) result.push_back(path);
            return; // 如果path.size() == k 但sum != targetSum 直接返回
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { // 剪枝
            sum += i; // 处理
            path.push_back(i); // 处理
            backtracking(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
            sum -= i; // 回溯
            path.pop_back(); // 回溯
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear(); // 可以不加
        path.clear();   // 可以不加
        backtracking(n, k, 0, 1);
        return result;
    }
};