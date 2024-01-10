class Solution {
public:
    Node* connect(Node* root) {
        queue <Node *> q;
        if (root != NULL) q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node * node = q.front();
                q.pop();
                if (i != size - 1) node -> next = q.front();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
        }
        return root;
    }
};