# 代码随想录算法训练营第十四天| 二叉树 Part01

## 今日题目

144.[二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)

145.[二叉树的后序遍历](https://leetcode.cn/problems/binary-tree-postorder-traversal/)

94.[二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)

## 基础知识

### 二叉树的种类

1. 满二叉树
   1.  二叉树只有度为0和度为2的节点，并且度为0的节点在同一层上：
   2. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YzFmNjRkZDg5NjRiZmY2N2ZkMWI2ZjU4YWM2YzAyM2JfS1hpUzNkTjhPRWdMbzJOSUVXZGUwS1VpbkR0bmMxZHJfVG9rZW46UmxzUmI3SnFxbzcwU3J4b25ZeWNqa1Bobk5nXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
   3.  深度为k，二叉树有$$2^{k-1}$$个节点。
2. 完全二叉树
   1.  除了最底层的节点没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第h层（h从1开始），则该层包含$$1-2^{h-1}$$个节点。
   2. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzNmODlkODhhN2ZhNmE5OWU0MzBlMzEwMTZhYWY2ZTJfZERlQTRWbFZMTnBQeFFKazlOT0lYT0xEMGdQWTBlUjNfVG9rZW46SUppSGJaeTVkb002MWd4MW5BYWNOYmNtbkhlXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
3. 二叉搜索树/二叉排序树
   1.  二叉搜索树是有数值的，是一个有序树。
   2. 若它的左子树不空，则左子树上所有节点的值均小于它的根节点的值；
   3. 若它的右子树不空，则右子树上所有节点的值均大于它的根节点的值；
   4. 它的左、右子树也分别为二叉排序树
   5. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NjQzMmM3OWIzYTExMmE0YTg2MGJmNDJiMWIyMWVlNzNfcGN2dEV4Z0R0bXNCVFBEalhVSFJzdmRwSG1peVEyc3FfVG9rZW46Rm1mRmJDSU5nb29wekF4eXUxR2NLRjhEbmhoXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
4. 平衡二叉搜索树
   1.  AVL：Adelson-Velsky and Landis，它是一棵空树或它的**左右两个子树的高度差的绝对值不超过1**，并且左右两个子树都是一棵平衡二叉树。
   2. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MWEzMmEyNmVlZGQ4ZTc0MGM2NGNkZjkyNTNhZmQ2OThfQm9QQ3psOEkycW5odlpreWE5bERZMlFzZ0d0ZEVOTTBfVG9rZW46UFNPYmJQRjhpb1hMQ3J4dWJqMmNkUnhFbkplXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
   3.  C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树，所以map、set的增删操作时间时间复杂度是logn，unordered_map、unordered_set底层实现是哈希表。

### 二叉树的存储方式

1. 链式存储

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGNlMzZjMmQ1OTllZTViMDA2OTYxMTAwMGU2MWI4OTJfNjU1cHdxWGozTDBqQzVNNGp2N3JGUFNIQWN0MU5HUFhfVG9rZW46UzVkdWJmZ0sxbzM2RVV4aWcxS2NPZDNkbkRsXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)

1. 顺序存储
   1. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTk2YzQ0ZDVmMDZjODhhNWVkZTRmZWIzNTM3Mjc1ZjJfSVNWZ1YyMjY2YlNuaTNiWHEyVHgzb0lpdTh0WVdqZDZfVG9rZW46Tjh2a2J4NHdrb28xY094TklRbmMwYmpubnpmXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)

### 二叉树的遍历方式

1. 深度优先遍历
   1. 前序遍历（递归法，迭代法）
   2. 中序遍历（递归法，迭代法）
   3. 后序遍历（递归法，迭代法）
2. 广度优先遍历
   1. 层次遍历（迭代法）

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2Q1ODhhYzk5NzI0NWVhYTJkZDA4ZGI4NjNhZTI0MTBfVHI4N3FWc3U0N0xpbldzeFlhOXF6dmJCZXpnbWk0MkNfVG9rZW46UWhVU2JMcDNQb0RTVFd4dmFRUGN4OFdFbldkXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)

1. 前中后序遍历的逻辑其实都是可以借助**栈**使用**递归**的方式来实现的。而广度优先遍历的实现一般使用**队列**来实现，这也是队列先进先出的特点所决定的，因为需要先进先出的结构，才能一层一层的来遍历二叉树。

### 二叉树的定义

```C++
struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

递归三要素

1. 确定递归函数的参数和返回值： 确定哪些参数是递归的过程中需要处理的，那么就在递归函数里加上这个参数，并且还要明确每次递归的返回值是什么进而确定递归函数的返回类型。
2. 确定终止条件：写完了递归算法, 运行的时候，经常会遇到栈溢出的错误，就是没写终止条件或者终止条件写的不对，操作系统也是用一个栈的结构来保存每一层递归的信息，如果递归没有终止，操作系统的内存栈必然就会溢出。
3. 确定单层递归的逻辑： 确定每一层递归需要处理的信息。在这里也就会重复调用自己来实现递归的过程。

## LeetCode 144.二叉树的前序遍历 

### 题目

给你二叉树的根节点 `root` ，返回它节点值的 **前序** 遍历。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MjNkOTBhMDQ1NTAwYzg4Y2MxMjFjZDgzZTQ1YTViYjhfYjBPM1VKU1QyYk4yRDNnR3N2TE1rbkdSZnh4MVJadFJfVG9rZW46U1pkMWJkb3NVb0ZnbTd4cExxVGNkVlJQbkNZXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
>
> 输入：root = [1,null,2,3] 输出：[1,2,3]

### 递归思路

1. 参数和返回值：参数为节点指针和结果数组，函数类型void，不设返回值；
2. 终止条件：当前节点为空；
3. 单层递归逻辑：如果当前节点不为空，访问当前节点的值；若为空，则返回；如果左右孩子不为空，依次递归遍历左右孩子。

### 递归代码

```C++
class Solution {
public:
    void preOrder(TreeNode * root, vector<int>& result) {
        if (root) {
            result.push_back(root->val);
        } else {
            return;
        }
        if (root -> left) preOrder(root -> left, result);
        if (root -> right) preOrder(root -> right, result);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector <int> result;
        preOrder(root, result);
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

1. **递归函数** **`preOrder`**: 这个函数会对每个节点递归调用自己两次（一次对左子树，一次对右子树），但实际上每个节点只被访问一次。因此，对于包含 `n` 个节点的树，`preOrder` 函数的时间复杂度是 `O(n)`，其中 `n` 是树中节点的数量。
2. **整体** **`preorderTraversal`** **函数**: 这个函数只是调用了 `preOrder` 函数一次，并在最后返回结果。所以，它的时间复杂度也是 `O(n)`。

空间复杂度：

1. **递归栈空间**: 在最坏的情况下（树完全不平衡，每个节点都只有左子节点或只有右子节点），递归的深度会达到 `n`，因此递归栈的空间复杂度是 `O(n)`。在最好的情况下（树完全平衡），递归的深度是 `O(log n)`。
2. **结果数组**: 存储结果的数组 `result` 需要 `O(n)` 的空间，因为它包含了树中每个节点的值。
3. **总空间复杂度**: 因此，整体空间复杂度是 `O(n)`，其中最主要的空间开销来自于结果数组和递归栈。

### 学习与小结

写递归函数应该按照三个条件的顺序来写，在我自己写的代码中就有冗余和逻辑不清的地方，比如没有先写终止条件，应该在节点为空时终止，写在最前面，这样就不需要判断左右孩子是否存在，直接递归左右孩子即可。

### 迭代思路

前序遍历是中左右，每次先处理的是中间节点，那么先将根节点放入栈中，然后将右孩子加入栈，再加入左孩子。

为什么要先加入 右孩子，再加入左孩子呢？ 因为这样出栈的时候才是中左右的顺序。

### 迭代代码

```C++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector <int> result;
        if (root == nullptr) {
            return result;
        }
        stack <TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode *tmp = st.top();
            st.pop();
            result.push_back(tmp -> val);
            if (tmp -> right) st.push(tmp -> right);
            if (tmp -> left) st.push(tmp -> left);
        }
        return result;
    }
};
```

## LeetCode 145.二叉树的后序遍历

### 题目

给你一棵二叉树的根节点 `root` ，返回其节点值的 **后序遍历** 。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NjkzOWFlMzlmNDg0ZDFiOGE3MzQzMTYxZGQyN2U5ZDBfZG94dEJ3OFREazVOQ0N0bEpWanlrcXZmbTVzTFpheFRfVG9rZW46UEdtOGI0aEthb1g3SUF4bE0xN2NUWlVlblhnXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
>
> 输入：root = [1,null,2,3] 输出：[3,2,1]

### 递归思路

1. 参数和返回值：参数为根节点root，result数组存放结果；
2. 终止条件：若当前节点为空，则终止；
3. 单层递归逻辑：深度优先遍历左右子树，最后记录中间节点的值。

### 递归代码

```C++
class Solution {
public:
    void postOrder(TreeNode * root, vector<int> & result) {
        if (root == nullptr) {
            return;
        }
        postOrder(root -> left, result);
        postOrder(root -> right, result);
        result.push_back(root -> val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector <int> result;
        postOrder(root, result);
        return result;
    }
};
```

### 迭代思路

后序遍历是**左右中**，前序遍历是**中左右**，那么在前序遍历的基础上，先将**中左右**变为**中右左**，再将整体逆置，不就变成**左右中**了吗？

所以在前序遍历迭代的基础上，改变左右子树的入栈顺序，先变成中右左，最后再将保存结果的数组整体逆置，就得到了需要的结果。

### 迭代代码

```C++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector <int> result;
        if (root == nullptr) {
            return result;
        }
        stack <TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode * tmp = st.top();
            st.pop();
            result.push_back(tmp -> val);
            if (tmp -> left) {
                st.push(tmp -> left);
            }
            if (tmp -> right) {
                st.push(tmp -> right);
            }
        }
        reverse(result.begin(),result.end());
        return result;
    }
};
```

## LeetCode 94.二叉树的中序遍历

### 题目

给定一个二叉树的根节点 `root` ，返回 *它的* ***中序*** *遍历* 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NjI3Nzc3YWFiYTA0MmQzOGIyNzBkZWMxNDg5NTgwN2ZfV2lqVThOMGlHM3JaNlprMmZxZlBKelVTQlRyNGNUZXhfVG9rZW46SE9pSmJrcDFqb1RRbG54SEZvM2NGd2phbmJiXzE3MDQ4MDUxOTU6MTcwNDgwODc5NV9WNA)
>
> 输入：root = [1,null,2,3] 输出：[1,3,2]

### 递归思路

1. 参数和返回值：参数为根节点root，result数组存放结果；
2. 终止条件：若当前节点为空，则终止；
3. 单层递归逻辑：深度优先遍历左子树，然后记录中间节点的值，最后深度优先遍历右子树。

### 递归代码

```C++
class Solution {
public:
    void inOrder(TreeNode * root, vector<int> & result) {
        if (root == nullptr) {
            return;
        }
        inOrder(root -> left, result);
        result.push_back(root -> val);
        inOrder(root -> right, result);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector <int> result;
        inOrder(root, result);
        return result;
    }
};
```

### 迭代思路

中序遍历和前序遍历的迭代思路不同，前序遍历时，访问到该节点顺势就对该节点进行了操作（将节点值加入到结果数组中），而中序遍历是左中右的顺序，访问到中间节点还需要看其是否有左孩子。所以要一直向左下走，直至左下为空，那么在最后一个左下节点之前，所有走过的节点都是将来要访问的节点，所以存在栈中。

访问到最后一个左节点后，对当前节点进行操作，加入结果数组，再开始迭代访问右节点。

### 迭代代码

```C++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector <int> result;
        stack <TreeNode*> st;
        TreeNode * cur = root;
        while (!st.empty() || cur != nullptr) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur -> left;
            } else {
                cur = st.top();
                st.pop();
                result.push_back(cur -> val);
                cur = cur -> right;
            }
        }
        return result;
    }
};
```

## 统一迭代

无法同时解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况。那我们就将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记。

如何标记呢，就是要处理的节点放入栈之后，紧接着放入一个**空指针**作为标记。 这种方法也可以叫做标记法。

### 中序遍历

```C++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
                if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

                st.push(node);                          // 添加中节点
                st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记。

                if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
            } else { // 只有遇到空节点的时候，才将下一个节点放进结果集
                st.pop();           // 将空节点弹出
                node = st.top();    // 重新取出栈中元素
                st.pop();
                result.push_back(node->val); // 加入到结果集
            }
        }
        return result;
    }
};
```

### 前序遍历

```C++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左
                st.push(node);                          // 中
                st.push(NULL);
            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};
```

### 后序遍历

```C++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != NULL) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                st.push(node);                          // 中
                st.push(NULL);
                if (node->right) st.push(node->right);  // 右
                if (node->left) st.push(node->left);    // 左

            } else {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};
```