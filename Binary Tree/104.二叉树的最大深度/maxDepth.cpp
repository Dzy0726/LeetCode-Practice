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