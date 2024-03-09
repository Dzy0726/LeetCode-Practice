/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> dp(2);
        dp = robTree(root);
        return max(dp[0], dp[1]);
    }
    vector<int> robTree(TreeNode* root) {
        if (root == NULL) return {0, 0};
        vector<int> left = robTree(root -> left);
        vector<int> right = robTree(root -> right);
        int result1 = root -> val + left[0] + right[0]; 
        int result2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {result2, result1};
    }
};