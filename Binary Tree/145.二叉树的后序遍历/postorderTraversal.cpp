// 递归实现
class Solution {
public:
    void postOrder(TreeNode * root, vector<int> & result) {
        if (root == nullptr) {
            return;
        }
        postOrder(root -> left, result);
        postOrder(root -> right, result);
        result.push_back(root -> val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector <int> result;
        postOrder(root, result);
        return result;
    }
};


// 迭代实现
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector <int> result;
        if (root == nullptr) {
            return result;
        }
        stack <TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode * tmp = st.top();
            st.pop();
            result.push_back(tmp -> val);
            if (tmp -> left) {
                st.push(tmp -> left);
            }
            if (tmp -> right) {
                st.push(tmp -> right);
            }
        }
        reverse(result.begin(),result.end());
        return result;
    }
};


// 统一迭代
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                st.push(node);                          // 中
                st.push(NULL);
                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左

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