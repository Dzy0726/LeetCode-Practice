// My Solution
class Solution {
public:
    int getHeight(TreeNode* root) {
        if (root == NULL)
            return 0;
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        return 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
        if (root == NULL) return true;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            int left = getHeight(node->left);
            int right = getHeight(node->right);
            if (right > left) swap(left, right);
            if (left - right > 1) return false;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return true;
    }
};


// A Better Solution

class Solution {
public:
    int getHeight(TreeNode* root) {
        if (root == NULL) return 0;
        int left = getHeight(root->left);
        int right = getHeighat(root->right);
        if (left == -1 || right == -1) return -1;
        if (right > left) swap(left, right);
        if (left - right > 1)  return -1;
        return 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
        if (getHeight(root) == -1) return false;
        return true;
    }
};