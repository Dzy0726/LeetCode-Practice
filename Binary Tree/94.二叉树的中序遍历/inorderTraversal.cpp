// 递归实现
class Solution {
public:
    void inOrder(TreeNode * root, vector<int> & result) {
        if (root == nullptr) {
            return;
        }
        inOrder(root -> left, result);
        result.push_back(root -> val);
        inOrder(root -> right, result);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector <int> result;
        inOrder(root, result);
        return result;
    }
};


// 迭代实现
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector <int> result;
        stack <TreeNode*> st;
        TreeNode * cur = root;
        while (!st.empty() || cur != nullptr) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur -> left;
            } else {
                cur = st.top();
                st.pop();
                result.push_back(cur -> val);
                cur = cur -> right;
            }
        }
        return result;
    }
};


// 统一迭代
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
                if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

                st.push(node);                          // 添加中节点
                st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记。

                if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
            } else { // 只有遇到空节点的时候，才将下一个节点放进结果集
                st.pop();           // 将空节点弹出
                node = st.top();    // 重新取出栈中元素
                st.pop();
                result.push_back(node->val); // 加入到结果集
            }
        }
        return result;
    }
};