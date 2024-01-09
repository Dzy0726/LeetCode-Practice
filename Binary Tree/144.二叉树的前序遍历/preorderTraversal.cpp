// 递归实现
class Solution {
public:
    void preOrder(TreeNode * root, vector<int>& result) {
        if (root) {
            result.push_back(root->val);
        } else {
            return;
        }
        if (root -> left) preOrder(root -> left, result);
        if (root -> right) preOrder(root -> right, result);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector <int> result;
        preOrder(root, result);
        return result;
    }
};


// 迭代实现
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector <int> result;
        if (root == nullptr) {
            return result;
        }
        stack <TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode *tmp = st.top();
            st.pop();
            result.push_back(tmp -> val);
            if (tmp -> right) st.push(tmp -> right);
            if (tmp -> left) st.push(tmp -> left);
        }
        return result;
    }
};


// 统一迭代
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左
                st.push(node);                          // 中
                st.push(NULL);
            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};