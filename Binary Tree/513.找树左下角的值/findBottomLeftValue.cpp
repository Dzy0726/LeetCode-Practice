// My Solution 迭代
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue <TreeNode *> q;
        int result = 0;
        if (root != NULL) q.push(root);
        while (!q.empty()) {
            result = q.front() -> val;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
        }
        return result;
    }
};


// 递归
class Solution {
public:
    int maxDepth = INT_MIN;
    int result;
    void traversal(TreeNode* root, int depth) {
        if (root->left == NULL && root->right == NULL) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }
        if (root->left) {
            depth++;
            traversal(root->left, depth);
            depth--; // 回溯
        }
        if (root->right) {
            depth++;
            traversal(root->right, depth);
            depth--; // 回溯
        }
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return result;
    }
};