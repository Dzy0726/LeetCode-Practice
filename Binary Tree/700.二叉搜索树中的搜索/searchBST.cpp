// 递归
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL) return NULL;
        TreeNode * result = NULL;
        if (root -> val == val) return root;
        else if (root -> val > val) result = searchBST(root -> left, val);
        else result = searchBST(root -> right, val);

        return result;
    }
};

// 迭代
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != NULL) {
            if (root->val > val) root = root->left;
            else if (root->val < val) root = root->right;
            else return root;
        }
        return NULL;
    }
};
