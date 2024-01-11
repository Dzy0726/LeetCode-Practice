// 迭代：
class Solution {
public:
    int maxDepth(Node* root) {
        queue <Node *> q;
        if (root != NULL) q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node * node = q.front();
                q.pop();
                for (int j = 0; j < node->children.size(); j++) {
                    q.push(node -> children[j]);
                }
            }
            depth++;
        }
        return depth;
    }
};

// 递归：
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == NULL) return 0;
        int depthNow = 1;
        vector <int> depth;
        for (int i = 0; i < root -> children.size(); i++) {
            depth.push_back(maxDepth(root -> children[i]));
        }
        auto it = max_element(depth.begin(), depth.end());
        if (it != depth.end()) {
            depthNow =  *it + 1;
        }
        return depthNow;
    }
};