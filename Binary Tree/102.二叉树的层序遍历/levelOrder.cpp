// My Bad Solution (Just record, do not study this solution)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector<int>> result;
        queue <TreeNode*> q;
        vector <int> tmp;
        q.push(root);
        int size = q.size();
        while (!q.empty() || tmp.size() > 0) {
            if (size > 0) {
                TreeNode * node = q.front();
                q.pop();
                if (node != nullptr) {
                    tmp.push_back(node -> val);
                    if (node -> left) q.push(node -> left);
                    if (node -> right) q.push(node -> right);
                }
                size--;
            } else {
                result.push_back(tmp);
                tmp.erase(tmp.begin(),tmp.end());
                size = q.size();
            }            
        }
        return result;
    }
};

// A Better Solution
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <vector <int>> result;
        while (!q.empty()) {
            vector <int> tmp;
            int size = q.size();
            while (size--) {
                TreeNode * node = q.front();
                q.pop();
                tmp.push_back(node -> val);
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(tmp);
        }
        return result;
    }
};