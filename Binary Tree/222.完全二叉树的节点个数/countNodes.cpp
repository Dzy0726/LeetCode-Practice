// 迭代
class Solution {
public:
    int countNodes(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        int count = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            count += size;
        }
        return count;
    }
};

// 递归
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int leftNum = countNodes(root -> left);
        int rightNum = countNodes(root -> right);
        int sum = leftNum + rightNum + 1;
        return sum;
    }
};s