class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == NULL) return root;
        if (root -> val < low) {
            TreeNode* right = trimBST(root -> right, low, high);
            return right;
        } else if (root -> val > high) {
            TreeNode* left = trimBST(root -> left, low, high);
            return left;
        } else {
            root -> left = trimBST(root -> left, low, high);
            root -> right = trimBST(root -> right, low, high);
        }
        return root;
    }
};