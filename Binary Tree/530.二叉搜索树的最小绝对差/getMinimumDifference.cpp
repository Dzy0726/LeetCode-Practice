// My Solution
class Solution {
public:
    void inorder(TreeNode* root, vector<int> &vec) {
        if (root == NULL) return;
        inorder(root -> left, vec);
        vec.push_back(root -> val);
        inorder(root -> right, vec);    
    }
    int getMinimumDifference(TreeNode* root) {
        vector<int> vec;
        inorder(root, vec);
        int minVal = INT32_MAX;
        for (int i = 1;i < vec.size(); i++) {
            minVal = minVal < (vec[i] - vec[i - 1]) ? minVal : (vec[i] - vec[i - 1]);
        }
        return minVal;
    }
};

// A Better Solution
class Solution {
public:
    int result = INT32_MAX;
    TreeNode* pre = NULL;
    void inorder(TreeNode* cur) {
        if (cur == NULL) return;
        inorder(cur -> left);
        if (pre != NULL) {
            result = min(result, cur -> val - pre -> val);
        }
        pre = cur;
        inorder(cur -> right);
    }
    int getMinimumDifference(TreeNode* root) {
        inorder(root);
        return result;
    }
};