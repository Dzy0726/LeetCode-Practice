// My Solution
class Solution {
public:
    static bool compare(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
    void inorder(TreeNode* root, unordered_map<int, int> &map) {
        if (root == NULL) return;
        inorder(root -> left, map);
        map[root -> val]++;
        inorder(root -> right, map);
    }
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map;
        vector<int> result;
        inorder(root, map);
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), compare);
        result.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i].second == vec[0].second) {
                result.push_back(vec[i].first);
            }
        }
        return result;
    }
};

// A Better Solution
class Solution {
public:
    vector<int> result;
    TreeNode* pre = NULL;
    int maxcount = 0;
    int count = 0;
    void inorder(TreeNode* cur) {
        if (cur == NULL) return;
        inorder(cur -> left);
        if (pre == NULL) { // 第一个节点count = 1
            count = 1;
        } else if (pre -> val == cur -> val) {
            count++;
        } else { // 前后不相等 count重置为1
            count = 1;
        }
        pre = cur;
        if (count == maxcount) {
            result.push_back(cur -> val);
        }
        if (count > maxcount) {
            maxcount = count;
            result.clear();
            result.push_back(cur -> val);
        }
        inorder(cur -> right);
    }
    vector<int> findMode(TreeNode* root) {
        count = 0;
        maxcount = 0;
        pre = NULL;
        result.clear();
        inorder(root);
        return result;
    }
};