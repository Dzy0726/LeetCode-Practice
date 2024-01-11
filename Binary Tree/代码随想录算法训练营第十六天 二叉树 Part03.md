# 代码随想录算法训练营第十六天| 二叉树 Part03

## 今日题目

104.[二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

559.[N 叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-n-ary-tree/)

111.[二叉树的最小深度](https://leetcode.cn/problems/minimum-depth-of-binary-tree/)

222.[完全二叉树的节点个数](https://leetcode.cn/problems/count-complete-tree-nodes/)

## LeetCode  **104.二叉树的最大深度**

### 题目

给定一个二叉树 `root` ，返回其最大深度。

二叉树的 **最大深度** 是指从根节点到最远叶子节点的最长路径上的节点数。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTRkZDRiODVkNTM3MDFhMmEwYTk2MWI0ZTJiZTUwZTRfRmdJWHdOWUd4VjBRcWdtYW1jN0VhTjROaVBybDk4cTFfVG9rZW46Q043QmJFZTlFbzhGdG54Mk9ka2NCSmg1bmllXzE3MDQ5NzQ5MTg6MTcwNDk3ODUxOF9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：3

### 思路

昨天做过一次，直接用层序遍历，每层结束深度加一。

### 代码

层序遍历：

```C++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node ->right);
            }
            depth++;
        }
        return depth; 
    }
};
```

### 学习与小结

- 二叉树节点的深度：指从根节点到该节点的最长简单路径边的条数或者节点数（取决于深度从0开始还是从1开始）
- 二叉树节点的高度：指从该节点到叶子节点的最长简单路径边的条数或者节点数（取决于高度从0开始还是从1开始）

根节点的高度就是这棵二叉树的深度

层序遍历是迭代的方法来求高度，那么如何使用递归求高度呢？

递归三部曲：

1. 参数及返回值：参数就是根节点，返回值是当前节点的高度；
2. 终止条件：如果当前节点为空，说明其高度为0，返回0；
3. 递归逻辑：采用后序遍历，左右中的顺序遍历整个树。

递归代码如下：

```C++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftHeight = maxDepth(root -> left);
        int rightHeight = maxDepth(root -> right);
        int height = 1 + max(leftHeight, rightHeight);
        return height;
    }
};
```

## LeetCode 559.n叉树的最大深度

### 题目

给定一个 N 叉树，找到其最大深度。

最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。

N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MmYxZDc2MWQ0MDAxOWE0MmVlNDg4ODRmMDMxZjNmZDJfRW1zSnUyQzY0WDZZVHRQVVpLVUdKRk9zeEFnQnRmcVFfVG9rZW46TmJmN2JVamlwb1c5Q254UGk5ZGMwWUM1bnFlXzE3MDQ5NzQ5MTg6MTcwNDk3ODUxOF9WNA)
>
> 输入：root = [1,null,3,2,4,null,5,6] 输出：3
>
> 示例 2：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTE4MDkyYjlhYjJjNWIxMWM0YjVjNTM5NGM4NDg3NWZfNkJya3FNYTdZUk9wdndYbTVZblZrU0FNZ01tNmNvdG5fVG9rZW46VVl3NGJ6QzQzb1JEb0J4eXgzUWNqWUhYbldkXzE3MDQ5NzQ5MTg6MTcwNDk3ODUxOF9WNA)
>
> 输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14] 输出：5

### 思路

迭代法：思路同上一题，层序遍历在每层之后让深度加一。

递归法：

参数及返回值：参数传入当前节点，返回值返回当前树的深度；

终止条件：当前节点为空，返回高度为0；

递归逻辑：每层递归遍历所有孩子，取出深度最大的一个加一，作为本层深度。

### 代码

层序遍历（迭代法）：

```C++
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
```

递归代码：

- Vector的增加如果没指定vector大小，用pushback防止越界；
- maxelement返回vector中最大值的**迭代器**，用*来取值；

```C++
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
```

### 学习与小结

有更简洁的递归写法：

```C++
class solution {
public:
    int maxDepth(Node* root) {
        if (root == 0) return 0;
        int depth = 0;
        for (int i = 0; i < root->children.size(); i++) {
            depth = max (depth, maxDepth(root->children[i]));
        }
        return depth + 1;
    }
};
```

## LeetCode 111.二叉树的最小深度

### 题目

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

**说明：**叶子节点是指没有子节点的节点。

> def

### 思路

昨天用层序遍历（迭代法）实现，今天用递归来实现：

参数及返回值：参数传入当前根节点，返回当前树的最小深度；

终止条件：如果树为空，则终止，返回最小深度0；

递归逻辑：依旧是后序遍历，左右中，选出最小值；要注意**最小深度是从根节点到最近****叶子节点****的最短路径上的节点数量**。叶子节点是左右孩子均为空的节点！所有如果一个节点单是左孩子或者右孩子为空，不能算是叶子节点，要将其高度加一返回。

### 代码

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftDepth = minDepth(root -> left);
        int rightDepth = minDepth(root -> right);
        if (root -> left == NULL && root -> right != NULL) {
            return 1 + rightDepth;
        } 
        if (root -> left != NULL && root -> right == NULL) {
            return 1 + leftDepth;
        } 
        int min_depth = 1 + min(leftDepth, rightDepth);
        return min_depth;
    }
};
```

### 学习与小结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NmU0YjU1YzE0YWY0YzZmNmY4MzVmMGE1NmUzNzA4ODFfYWNxeFB4WVJ5NGtYcTk0UW5CQlpjc2RMSGd2VWVWMDdfVG9rZW46R2dsTWJSTEFLb05FWGx4bmFaV2N3c0t6bkxoXzE3MDQ5NzQ5MTg6MTcwNDk3ODUxOF9WNA)

如果直接返回左右二者的最小值的话，没有左孩子的分支会算为最短深度。

所以，如果左子树为空，右子树不为空，说明最小深度是 1 + 右子树的深度。

反之，右子树为空，左子树不为空，最小深度是 1 + 左子树的深度。 最后如果左右子树都不为空，返回左右子树深度最小值 + 1 。

## LeetCode **222.****完全二叉树****的节点个数**

### 题目

给你一棵 **完全二叉树** 的根节点 `root` ，求出该树的节点个数。

[完全二叉树](https://baike.baidu.com/item/完全二叉树/7773232?fr=aladdin) 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 `h` 层，则该层包含 `1~ 2(h)` 个节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YzZjODk4NzJhZmE5ZWU4ZTFmNTg2MmVlMmJiYTU2ZDlfWlJTVGpvcXlickNXbGkwWlZtMUVmY3NhNEpqaUZ1cnFfVG9rZW46SkdKR2J6S2c1b1o1VGJ4aldmZ2NvREY0blhiXzE3MDQ5NzQ5MTg6MTcwNDk3ODUxOF9WNA)
>
> 输入：root = [1,2,3,4,5,6] 输出：6

### 思路

迭代法，按照层序遍历，层序遍历中的size统计了每层的元素个数，将这些相加就是元素总数。

递归法，可以后序遍历这棵树，只要当前节点不为空，count就加一；

参数和返回值：参数是当前树节点，返回算上当前节点的总数；

终止条件：当前节点为空，返回0；

递归逻辑：后序遍历左右中，将左子树和右子树的个数加起来加上当前节点的个数就是总数。

### 代码

迭代代码：

```C++
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
```

递归代码：

```C++
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int leftNum = countNodes(root -> left);
        int rightNum = countNodes(root -> right);
        int sum = leftNum + rightNum + 1;
        return sum;
    }
};
```

### 时空复杂度

迭代法：

时间复杂度：如果树中有 `N` 个节点，每个节点都将被访问一次，因此总的时间复杂度是 **O(N)**

空间复杂度：

- 在最坏的情况下，即树完全不平衡，像一条链一样，队列中最多同时只有一个节点，空间复杂度是 **O(1)**。
- 在最好的情况下，即树完全平衡，最后一层的节点数最多，且大约等于总节点数的一半，此时队列中最多有 `N/2` 个节点（`N` 是总节点数），因此空间复杂度是 **O(N)**。

递归法：

时间复杂度：如果树有 `N` 个节点，每个节点都会被处理一次。

- 每个节点的处理时间是常数时间复杂度 `O(1)`（不包括递归调用的时间）。
- 因此，总的时间复杂度是 `N` 乘以 `O(1)`，即 **O(N)**。

空间复杂度：

- 在最坏的情况下（树完全不平衡，每个节点只有一个子节点），递归栈的深度会与节点数 `N` 相同，此时空间复杂度为 **O(N)**。
- 在最好的情况下（树完全平衡），树的高度是 `log(N)`，此时递归栈的最大深度也是 `log(N)`，所以空间复杂度为 **O(log(N))**。

### 学习与小结

以上两种做法无需考虑树是完全二叉树还是非完全二叉树，只要是二叉树就可以求出其节点总数。

而这道题特别提到求完全二叉树的节点总数，那么还可以用完全二叉树的性质来求。

完全二叉树也分为最后一层是满还是非满，如果完全二叉树的最底层是满的，那么他同时是一棵满二叉树，求节点个数：$$2^n -1$$，n为树的高度；如果是非满的，就用左子树加右子树+1来求。代码如下：

```C++
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        int leftDepth = 0, rightDepth = 0; // 这里初始为0是有目的的，为了下面求指数方便
        while (left) {  // 求左子树深度
            left = left->left;
            leftDepth++;
        }
        while (right) { // 求右子树深度
            right = right->right;
            rightDepth++;
        }
        if (leftDepth == rightDepth) {
            return (2 << leftDepth) - 1; // 注意(2<<1) 相当于2^2，所以leftDepth初始为0
        }
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
```