// My Solution
class Solution {
public:
    void findPath(TreeNode* root, vector<int> current, int targetSum, vector<vector<int>> &result) {
        int curSum = 0;
        for (int i = 0; i < current.size(); i++) {
            curSum += current[i];
        }
        if (root -> left == NULL && root -> right == NULL && curSum == targetSum) {
            result.push_back(current);
        }
        if (root -> left) {
            current.push_back(root -> left -> val);
            findPath(root -> left, current, targetSum, result);
            current.pop_back();
        }
        if (root -> right) {
            current.push_back(root -> right -> val);
            findPath(root -> right, current, targetSum, result);
            current.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> current;
        if (root == NULL) return result;
        current.push_back(root -> val);
        findPath(root, current, targetSum, result);
        return result;
    }
};

// Optimal Solution
class Solution {
public:
    void findPath(TreeNode* root, vector<int> &current, int curSum, int targetSum, vector<vector<int>> &result) {
        if (!root) return; // 如果节点为空，直接返回。
        curSum += root->val; // 更新当前路径和。
        current.push_back(root->val); // 将当前节点值加入到路径中。
        // 如果是叶子节点，并且当前路径和等于目标和，将其添加到结果中。
        if (root->left == NULL && root->right == NULL && curSum == targetSum) {
            result.push_back(current);
        } else {
            // 递归搜索左右子树。
            findPath(root->left, current, curSum, targetSum, result);
            findPath(root->right, current, curSum, targetSum, result);
        }
        // 回溯：在返回父节点之前从当前路径中移除当前节点。
        current.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> current;
        if (root == NULL) return result;
        findPath(root, current, 0, targetSum, result);
        return result;
    }
};