class Solution {
public:
    unordered_map<int, int> index;
    TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd) return NULL;
        int rootValue = preorder[preStart];
        TreeNode * root = new TreeNode(rootValue);
        int rootIndex = index[rootValue];
        root -> left = buildTreeHelper(preorder, inorder, preStart + 1, preStart + rootIndex - inStart , inStart, rootIndex - 1);
        root -> right = buildTreeHelper(preorder, inorder, preStart + rootIndex - inStart + 1 , preEnd, rootIndex + 1, inEnd);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            index[inorder[i]] = i;
        }
        return buildTreeHelper(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};