// My Solution
class Solution {
public:
    void transferLR(TreeNode *&root) {
        if (root == NULL) return;
        if (root -> left || root -> right) {
            TreeNode * tmp = root -> left;
            root -> left = root -> right;
            root -> right = tmp;
        }
        transferLR(root -> left);
        transferLR(root -> right);
    }
    TreeNode* invertTree(TreeNode* root) {
        transferLR(root);
        return root;
    }
};


// A Better Solution
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        swap(root->left, root->right);  // 中
        invertTree(root->left);         // 左
        invertTree(root->right);        // 右
        return root;
    }
};