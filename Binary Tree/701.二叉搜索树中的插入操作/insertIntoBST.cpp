// 迭代：My Solution
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        if (root == NULL) return newNode;
        TreeNode* cur = root;
        while (cur -> left || cur -> right) {
            if (val < cur -> val && cur -> left != NULL) {
                cur = cur -> left;
            } else if (val > cur -> val && cur ->right != NULL) {
                cur = cur -> right;
            } else {
                break;
            }
        }
        if (val < cur -> val) {
            cur -> left = newNode;
        } else {
            cur -> right = newNode;
        }
        return root;
    }
};

// 递归：
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode * node = new TreeNode(val);
            return node;
        }
        if (root -> val > val) {
            root -> left = insertIntoBST(root -> left, val);
        } else {
            root -> right = insertIntoBST(root -> right, val);
        }
        return root;
    }   
};