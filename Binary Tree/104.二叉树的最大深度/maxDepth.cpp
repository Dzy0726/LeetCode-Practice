// 层序遍历，迭代法
class Solution {
public:
    int maxDepth(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            depth++;
        }
        return depth;
    }
};

// 后序遍历，递归法
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftHeight = maxDepth(root -> left);
        int rightHeight = maxDepth(root -> right);
        int height = 1 + max(leftHeight, rightHeight);
        return height;
    }
};