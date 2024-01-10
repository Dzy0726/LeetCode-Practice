class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <vector<int>> result;
        while (!q.empty()) {
            int size = q.size();
            vector <int> tmp;
            while (size--) {
                TreeNode * node = q.front();
                q.pop();
                tmp.push_back(node -> val);
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(tmp);
        }
        reverse(result.begin(),result.end());
        return result;
    }
};