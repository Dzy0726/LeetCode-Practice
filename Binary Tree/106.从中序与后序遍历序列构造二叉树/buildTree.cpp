// My Solution
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty()) {
            return NULL;
        }
        int root_val = postorder.back();
        postorder.pop_back();
        TreeNode* root = new TreeNode(root_val);
        auto itInorderRoot = find(inorder.begin(), inorder.end(), root_val);
        vector<int> inLeft(inorder.begin(), itInorderRoot);
        vector<int> inRight(itInorderRoot + 1, inorder.end());
        vector<int> postLeft(postorder.begin(), postorder.begin() + inLeft.size());
        vector<int> postRight(postorder.end() - inRight.size(), postorder.end());
        root -> left = buildTree(inLeft, postLeft);
        root -> right = buildTree(inRight, postRight);
        return root;
    }
};

// A Better Solution
class Solution {
    unordered_map<int, int> inorderIndexMap;
    TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, int postStart, int postEnd, int inStart, int inEnd) {
        if (postStart > postEnd) {
            return NULL;
        }
        int root_val = postorder[postEnd];
        TreeNode* root = new TreeNode(root_val);
        int inRootIndex = inorderIndexMap[root_val];
        root->left = buildTreeHelper(inorder, postorder, postStart, postStart + inRootIndex - inStart - 1, inStart, inRootIndex - 1);
        root->right = buildTreeHelper(inorder, postorder, postStart + inRootIndex - inStart, postEnd - 1, inRootIndex + 1, inEnd);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderIndexMap[inorder[i]] = i;
        }
        return buildTreeHelper(inorder, postorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
    }
};