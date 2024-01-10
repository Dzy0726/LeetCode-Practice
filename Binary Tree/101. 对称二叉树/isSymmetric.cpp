// 递归
class Solution {
public:
    bool isMirror(TreeNode * left, TreeNode * right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        if (left -> val != right -> val) return false;
        bool outside = isMirror(left -> left, right -> right);
        bool inside = isMirror(left -> right, right -> left);
        return outside && inside;
    }
    bool isSymmetric(TreeNode* root) {
        return isMirror(root -> left, root -> right);
    }
};

// 迭代
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        queue <TreeNode *> q;
        q.push(root -> left);
        q.push(root -> right);
        while (!q.empty()) {
            TreeNode * left = q.front();
            q.pop();
            TreeNode * right = q.front();
            q.pop();
            if (left == NULL && right == NULL) continue;
            if (left == NULL || right == NULL) return false;
            if (left -> val != right -> val) return false;
            q.push(left -> left);
            q.push(right -> right);
            q.push(left -> right);
            q.push(right -> left);
        }
        return true;
    }
};