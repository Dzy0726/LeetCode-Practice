// My Solution
class Solution {
public:
    TreeNode* buildTree(vector<int>& nums, int begin, int end) {
        if (begin > end) return NULL;
        int mid = (begin + end) / 2; // int mid = begin + (end - begin) / 2;
        int midVal = nums[mid];
        TreeNode* root = new TreeNode(midVal);
        root -> left = buildTree(nums, begin, mid - 1);
        root -> right = buildTree(nums, mid + 1, end);
        return root;

    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildTree(nums, 0, nums.size() - 1);
    }
};