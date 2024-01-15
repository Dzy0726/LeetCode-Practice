// My Solution
class Solution {
public:
    TreeNode* buildHelper(vector<int>& num, int start, int end) {
        if (start > end) return NULL;
        int maxNum = INT32_MIN;
        int count = 0;
        for (int i = start; i <= end; i++) {
            if (num[i] > maxNum) {
                maxNum = num[i];
                count = i;
            }
        }
        TreeNode * root = new TreeNode(maxNum);
        root -> left = buildHelper(num, start, count - 1);
        root -> right = buildHelper(num, count + 1, end);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) return NULL;
        return buildHelper(nums, 0, nums.size() - 1);
    }
};