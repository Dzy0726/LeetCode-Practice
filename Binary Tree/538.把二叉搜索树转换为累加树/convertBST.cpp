// My Solution
class Solution {
public:
    int sum = 0;
    void getSum(TreeNode*& root) {
        if (root -> right != NULL) {
            getSum(root -> right);
        }
        sum += root -> val;
        root -> val = sum;
        if (root -> left) {
            getSum(root -> left);
        }
    }
    TreeNode* convertBST(TreeNode* root) {
        if (root == NULL) return root;
        getSum(root);
        return root;
    }
};

// A Better Solution
class Solution {
public:
    int pre = 0;
    void reInorder(TreeNode* root) {
        if (root == NULL) return;
        reInorder(root -> right);
        root -> val += pre;
        pre = root -> val;
        reInorder(root -> left);
    }

    TreeNode* convertBST(TreeNode* root) {
        reInorder(root);
        return root;
    }
};