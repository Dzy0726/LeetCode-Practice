class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q;
        if (root != NULL)
            q.push(root);
        vector<int> result;
        while (!q.empty()) {
            int size = q.size();
            while (size != 0) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                if (size == 1) result.push_back(node -> val);
                size--;
            }
        }
        return result;
    }
};