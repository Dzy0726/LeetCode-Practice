// My Solution
class Solution {
public:
    bool findAncestor(TreeNode* root, TreeNode *p, deque<TreeNode*> &pAncestor) {
        if (root == NULL) return false;
        pAncestor.push_back(root);
        if (root == p) return true;
        if (findAncestor(root -> left, p, pAncestor) || findAncestor(root -> right, p, pAncestor)) {
            return true;
        }
        pAncestor.pop_back();
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        deque<TreeNode*> pAncestor;
        deque<TreeNode*> qAncestor;
        findAncestor(root, p, pAncestor);
        findAncestor(root, q, qAncestor);
        TreeNode * result;
        while (!pAncestor.empty() && !qAncestor.empty() && pAncestor.front() == qAncestor.front()) {
            result = pAncestor.front();
            pAncestor.pop_front();
            qAncestor.pop_front();
        }
        return result;
    }
};

// A Better Solution
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q ) return root;
        TreeNode * left = lowestCommonAncestor(root -> left, p, q);
        TreeNode * right = lowestCommonAncestor(root -> right, p ,q);
        if (left != NULL && right != NULL) return root;
        if (left == NULL && right != NULL) return right;
        else if (left != NULL && right == NULL) return left;
        else return NULL;
    }
};