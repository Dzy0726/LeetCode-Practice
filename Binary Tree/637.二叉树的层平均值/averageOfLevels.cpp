class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <double> result;
        while (!q.empty()) {
            int size = q.size();
            int count = 0;
            double sum = 0;
            while (size--) {
                TreeNode * node = q.front();
                q.pop();
                sum += node -> val;
                count++;
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(sum / count);
        }
        return result;
    }
};