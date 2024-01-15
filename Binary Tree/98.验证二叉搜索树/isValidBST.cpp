// 迭代代码：
class Solution {
public:
    void inorder(TreeNode * root, vector<int> & vec) {
        if (root -> left) inorder(root -> left, vec);
        vec.push_back(root -> val);
        if (root -> right) inorder(root -> right, vec);
    }
    bool isValidBST(TreeNode* root) {
        vector<int> vec;
        inorder(root, vec);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }
};

// 递归：
class Solution {
public:
    long long maxVal = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        bool left = isValidBST(root -> left);
        if (root -> val <= maxVal) {
            return false;
        } else {
            maxVal = root -> val;
        }
        bool right = isValidBST(root -> right);
        return left && right;
    }
};