// 迭代
class Solution {
public:
    int minDepth(TreeNode* root) {
        queue <TreeNode *> q;
        if (root == NULL) {
            return 0;
        }
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left == NULL && node -> right == NULL) {
                    return ++depth;
                } else {
                    if (node -> left) q.push(node -> left);
                    if (node -> right) q.push(node -> right);
                }
            }
            depth++;
        }
        return depth;
    }
};


// 递归
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftDepth = minDepth(root -> left);
        int rightDepth = minDepth(root -> right);
        if (root -> left == NULL && root -> right != NULL) {
            return 1 + rightDepth;
        } 
        if (root -> left != NULL && root -> right == NULL) {
            return 1 + leftDepth;
        } 
        int min_depth = 1 + min(leftDepth, rightDepth);
        return min_depth;
    }
};