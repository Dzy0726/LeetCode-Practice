class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue <Node*> q;
        if (root != NULL) q.push(root);
        vector<vector<int>> result;
        while (!q.empty()) {
            int size = q.size();
            vector <int> tmp;
            for (int i = 0; i < size; i++) {
                Node * node = q.front();
                q.pop();
                tmp.push_back(node -> val);
                for (int j = 0; j < node -> children.size(); j++) {
                    q.push(node -> children[j]);
                }
            }
            result.push_back(tmp);
        }
        return result;
    }
};