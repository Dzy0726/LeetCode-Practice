// My First Solution
class Solution {
public:
    bool findPath(TreeNode * root, vector<int> &sum, int targetSum) {
        if (root -> left == NULL && root -> right == NULL) {
            int s = 0;
            for (int i = 0; i < sum.size(); i++) {
                s += sum[i];
            }
            s += root -> val;
            if (s == targetSum) return true;
        }
        if (root -> left) {
            sum.push_back(root -> val);
            if (findPath(root -> left, sum, targetSum) == false) {
                sum.pop_back();
            } else {
                return true;
            }
            
        }
        if (root -> right) {
            sum.push_back(root -> val);
            if (findPath(root -> right, sum, targetSum) == false) {
                sum.pop_back();
            } else {
                return  true;
            }
        }
        return false;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        vector <int> sum;
        if (root == NULL) return false;
        return findPath(root, sum, targetSum);
    }
};

// A Better Solution
class Solution {
public:
    bool findPath(TreeNode* root, int targetSum) {
        if (targetSum == 0 && root -> left == NULL && root -> right == NULL) {
            return true;
        }
        if (root -> left == NULL && root -> right == NULL) {
            return false;
        }
        if (root -> left) {
            targetSum -= root -> left -> val;
            if (findPath(root -> left, targetSum) == true) {
                return true;
            }
            targetSum += root -> left -> val;
        }
        if (root -> right) {
            targetSum -= root -> right -> val;
            if (findPath(root -> right, targetSum) == true) {
                return true;
            }
            targetSum += root -> right -> val;
        }
        return false;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return false;
        return findPath(root, targetSum - root -> val);
    }
};

// A Cleaner Solution
class Solution {
public:
    bool findPath(TreeNode* root, int currentSum, int targetSum) {
        if (root == NULL) return false; 
        currentSum += root->val;
        if (root->left == NULL && root->right == NULL) {
            return currentSum == targetSum;
        }
        return findPath(root->left, currentSum, targetSum) || 
               findPath(root->right, currentSum, targetSum);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return findPath(root, 0, targetSum);
    }
};