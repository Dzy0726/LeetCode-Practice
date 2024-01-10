class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <int> result;
        while (!q.empty()) {
            int size = q.size();
            int max = INT32_MIN;
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                max = node -> val > max ? node -> val : max;
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(max);
        }
        return result;
    }  
};