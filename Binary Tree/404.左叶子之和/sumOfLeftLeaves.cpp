/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-12 15:47:10
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-12 15:47:16
 * @FilePath: \LeetCode-Practice\Binary Tree\404.左叶子之和\sumOfLeftLeaves.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        queue <TreeNode *> q;
        int sum = 0;
        if (root != NULL) q.push(root);
        while (!q.empty()) {
            TreeNode * node = q.front();
            q.pop();
            if (node -> left) {
                if (node -> left -> left == NULL && node -> left -> right == NULL) {
                    sum += node -> left -> val;
                } else {
                    q.push(node -> left);
                } 
            }
            if (node -> right) q.push(node -> right);
        }
        return sum;
    }
};