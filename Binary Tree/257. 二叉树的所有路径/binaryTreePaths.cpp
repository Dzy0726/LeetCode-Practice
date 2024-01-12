// My Solution
class Solution {
public:
    void dfs(TreeNode * root, deque<TreeNode *> & q, vector<string>&result) {
        if (root == NULL && q.empty()) {
            return;
        }
        q.push_back(root);
        if (root -> left == NULL && root -> right == NULL) {
            string s;
            deque <TreeNode*> tmp = q;
            while (!tmp.empty()) {
                TreeNode * node = tmp.front();
                tmp.pop_front();
                s += to_string(node -> val);
                if (!tmp.empty()) s+= "->"; 
            }
            result.push_back(s);
        } 
        if (root -> left) {
            dfs(root -> left, q, result);
            q.pop_back();
        }
        if (root -> right) {
            dfs(root -> right, q, result);
            q.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector <string> result;
        deque <TreeNode*> q;
        dfs(root, q, result);
        return result;
    }
};

// A Better Solution
class Solution {
public:
    void dfs(TreeNode * root, vector <int> &path, vector<string>&result) {
        path.push_back(root -> val);
        if (root -> left == NULL && root -> right == NULL) {
            string s;
            for (int i = 0; i < path.size(); i++) {
                s += to_string(path[i]);
                if (i != path.size() - 1) s += "->";
            }
            result.push_back(s);
        }
        if (root -> left) {
            dfs(root -> left, path, result);
            path.pop_back();
        }
        if (root -> right) {
            dfs(root -> right, path, result);
            path.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector <string> result;
        vector <int> path;
        dfs(root, path, result);
        return result;
    }
};