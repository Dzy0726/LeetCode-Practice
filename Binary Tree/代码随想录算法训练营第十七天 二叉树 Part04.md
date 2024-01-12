# 代码随想录算法训练营第十七天| 二叉树 Part04

## 今日题目

110.[平衡二叉树](https://leetcode.cn/problems/balanced-binary-tree/)

257.[二叉树的所有路径](https://leetcode.cn/problems/binary-tree-paths/)

404.[左叶子之和](https://leetcode.cn/problems/sum-of-left-leaves/)

## LeetCode 110.平衡二叉树

### 题目

给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

> 一个二叉树*每个节点* 的左右两个子树的高度差的绝对值不超过 1 

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MTMxNmYyYjllYWQ2ZDdiZWFmODdkNGE1ZWJlOTFjOWZfd09JcU95Sm1OYkNQTUczbXV1RUh2ellaWXZ1OHozSTNfVG9rZW46VUR4dWJYYlFqb3EyZER4dkRyZmNBbUlzbmxzXzE3MDUwNDU2NTk6MTcwNTA0OTI1OV9WNA)
>
> 输入：root = [3,9,20,null,null,15,7]
>
> 输出：true

### 思路

一开始想着比较左子树和右子树的高度差，如果大于一就说明不是平衡二叉树；但是遇到了这样的情况：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NDBlNmRmY2Q4NTk1YmQxMTU4ZmJkN2ZiODk2MTIxYzFfTHpXd3BmZlMyTXZsNTBlbGVqNmlBMFhvVU52MjE2ZjhfVG9rZW46UUJSc2JkdUhlb3Y4OUh4bXZLSGN0TjZ2blpkXzE3MDUwNDU2NTk6MTcwNTA0OTI1OV9WNA)

显然，单纯的左右子树高度相同不足以判定一棵树是否是平衡二叉树。

所以用层序遍历，每次出队一个节点就比较一下左右子树的高度差，不符合平衡二叉树条件就返回false，否则就将左右节点加入队列继续比较。

### 代码

层序遍历：

```C++
class Solution {
public:
    int getHeight(TreeNode* root) {
        if (root == NULL)
            return 0;
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        return 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
        if (root == NULL) return true;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            int left = getHeight(node->left);
            int right = getHeight(node->right);
            if (right > left) swap(left, right);
            if (left - right > 1) return false;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return true;
    }
};
```

### 学习与小结

这道题用递归的后序遍历也可以解，递归三要素：

1. 参数及返回值

参数传入当前节点，返回以当前传入节点为根节点的树的高度。那么如何标记左右子树是否差值大于1呢？如果当前传入节点为根节点的二叉树**已经不是二叉****平衡树****了**，还返回高度的话就没有意义了。所以如果已经不是二叉平衡树了，可以返回-1来标记已经不符合平衡树的规则了。

1. 终止条件

递归的过程中依然是遇到空节点了为终止，返回0，表示当前节点为根节点的树高度为0。

1. 递归逻辑
   1.  分别求出其左右子树的高度，然后如果差值小于等于1，则返回当前二叉树的高度，否则返回-1，表示已经不是二叉平衡树了。

```C++
class Solution {
public:
    int getHeight(TreeNode* root) {
        if (root == NULL) return 0;
        int left = getHeight(root->left);
        int right = getHeighat(root->right);
        if (left == -1 || right == -1) return -1;
        if (right > left) swap(left, right);
        if (left - right > 1)  return -1;
        return 1 + max(left, right);
    }

    bool isBalanced(TreeNode* root) {
        if (getHeight(root) == -1) return false;
        return true;
    }
};
```

## LeetCode 257. 二叉树的所有路径

### 题目

给你一个二叉树的根节点 `root` ，按 **任意顺序** ，返回所有从根节点到叶子节点的路径。

**叶子节点** 是指没有子节点的节点。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODNiZmYwZGVlMGNkNzNkNzU2MWVkOTI2MDUzZDQ4MWJfUXIwd0dxcHJBTm0zZk1YaTBrQXAwWmQwdHZCQVdGRHNfVG9rZW46TWkwc2JCa0RLb0xjYmd4VzJ1NmNFYVZCbnRmXzE3MDUwNDU2NTk6MTcwNTA0OTI1OV9WNA)

输入：root = [1,2,3,null,5] 输出：["1->2->5","1->3"]

### 思路

用队列或者栈总是多一个节点或者少一个节点，无法写出正确的回溯代码。不过也是很长时间后再次接触回溯法，也在情理之中。

看过讲解茅塞顿开，原来是自己回溯的位置找的不对，修改了两行后，没能通过的代码直接AC。

我的思路是定义双端队列来记录从根节点找到叶子节点的过程。当传入节点左右孩子均为空，说明他是叶子节点，此时需要记录一条路径，就从我们的队列q中取出路径，写一条结果加入到result中。如果不为叶子节点，则左孩子不为空，继续递归遍历左孩子这棵树；右孩子不为空，递归遍历右孩子这棵树。

之所以会出现有时候多一个节点，有时候少一个节点，是因为pop的位置没有选对。一开始我在每加入一条结果就pop，导致结果会多出一个节点。真正pop是应该在某个节点左孩子这边完成了一次dfs，可以理解成左孩子这边输出了一条结果，再把这次dfs中加入的左孩子pop；右孩子这边输出了一条结果，再把右孩子pop；这样才能真正的做到回溯，不会多删也不会少删。

### 代码

乱七八糟代码：

```C++
class Solution {
public:
    void dfs(TreeNode * root, deque<TreeNode *> & q, vector<string>&result) {
        if (root == NULL && q.empty()) {
            return;
        }
        q.push_back(root);
        if (root -> left == NULL && root -> right == NULL) {
            string s;
            deque <TreeNode*> tmp = q;
            while (!tmp.empty()) {
                TreeNode * node = tmp.front();
                tmp.pop_front();
                s += to_string(node -> val);
                if (!tmp.empty()) s+= "->"; 
            }
            result.push_back(s);
        } 
        if (root -> left) {
            dfs(root -> left, q, result);
            q.pop_back();
        }
        if (root -> right) {
            dfs(root -> right, q, result);
            q.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector <string> result;
        deque <TreeNode*> q;
        dfs(root, q, result);
        return result;
    }
};
```

### 学习与小结

再来一次，理清逻辑。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzU5MmY1YmU5ODA4ZTRiN2RkNWY0ZDYwYTg3MTdkYzlfanFaeW1lTk5WSHVXQk94ZnBOVDJtbmdId3kwZE9pVjVfVG9rZW46RnZ0cmJhWVpEb3k1Y0t4VDRxV2NraDY5bjFiXzE3MDUwNDU2NTk6MTcwNTA0OTI1OV9WNA)

比如在进行第二步，遍历到了一个叶子节点，按照我的代码，将此节点加入队列，发现其左右均为空，输出一条结果1->2；此时队列是1，2，什么时候把这个2删掉呢？就是1的左子树dfs完，就删掉一个队列末尾的节点，表明这棵树及其子树已经遍历完成。

这道题我们用递归前序遍历来看：

1. 参数及返回值：要传入根节点，记录每一条路径的path，和存放结果集的result，这里递归不需要返回值；
2. 终止条件：不需要用root为空终止，可以用root左右均为空，完成一条记录作为终止条件；
3. 递归逻辑：前序遍历，先处理中间节点，加入到path，在看左右，递归遍历左右。

回溯和递归是一一对应的，有一个递归，就要有一个回溯！

回溯要和递归永远在一起，世界上最遥远的距离是你在花括号里，而我在花括号外！

```C++
class Solution {
public:
    void dfs(TreeNode * root, vector <int> &path, vector<string>&result) {
        path.push_back(root -> val);
        if (root -> left == NULL && root -> right == NULL) {
            string s;
            for (int i = 0; i < path.size(); i++) {
                s += to_string(path[i]);
                if (i != path.size() - 1) s += "->";
            }
            result.push_back(s);
        }
        if (root -> left) {
            dfs(root -> left, path, result);
            path.pop_back();
        }
        if (root -> right) {
            dfs(root -> right, path, result);
            path.pop_back();
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector <string> result;
        vector <int> path;
        dfs(root, path, result);
        return result;
    }
};
```

## LeetCode  **404.左叶子之和** 

### 题目

给定二叉树的根节点 `root` ，返回所有左叶子之和。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OWQxYzY1YTdiYWI1ZWRhOGI4YTM3ZmMxZDBjODYxZGZfamxMb2RUYU15MVBMbExDaWJua3hoS3c2TnQ3czczV1VfVG9rZW46R1FCNmJCMFdYb1BobTh4RGhGaGNPbXR6bmpnXzE3MDUwNDU2NTk6MTcwNTA0OTI1OV9WNA)
>
> **输入:** root = [3,9,20,null,null,15,7]  **输出:** 24  **解释:** 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

### 思路

我的思路是先用层序遍历找到所有的“左孩子”，并不一定都是“左叶子”。然后再遍历全部的左孩子，如果节点左右孩子均为空，说明他是左叶子，将其值加到sum中。

### 代码

```C++
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        queue <TreeNode *> q;
        queue <TreeNode *> left;
        int sum = 0;
        if (root != NULL) q.push(root);
        while (!q.empty()) {
            TreeNode * node = q.front();
            q.pop();
            if (node -> left) {
                q.push(node -> left);
                left.push(node -> left);
            }
            if (node -> right) q.push(node -> right);
        }
        while (!left.empty()) {
            TreeNode * node = left.front();
            left.pop();
            if (node -> left == NULL && node -> right == NULL) {
                sum += node -> val;
            }
        }
        return sum;
    }
};
```

### 时空复杂度

时间复杂度：

1. 方法首先通过广度优先搜索（BFS）遍历整棵树，将所有节点加入队列 `q`，并且将所有左子节点加入队列 `left`。每个节点都会被访问一次，因此这部分的时间复杂度是 `O(N)`，其中 `N` 是树中节点的数量。
2. 方法接着遍历队列 `left` 中的所有节点，检查它们是否是叶子节点，并计算它们的值的总和。由于每个左子节点也只被访问一次，这部分的时间复杂度也是 `O(N)`。

因此，总的时间复杂度是 `O(N)`。

空间复杂度：

1. `q` 队列在 BFS 过程中最多可能包含树的一层中的所有节点。在最坏的情况下，这将是树的最底层，其节点数最多为 `N/2`（在完全二叉树的情况下）。因此，这部分的空间复杂度是 `O(N)`。
2. `left` 队列存储的是每个节点的左子节点。在最坏的情况下，这也可能接近 `N/2`。因此，这部分的空间复杂度也是 `O(N)`。

因此，总的空间复杂度是 `O(N)`。

### 学习与小结

上面的代码也可以优化为不需要left存放左叶子，直接在层序遍历中判断其是否为叶子节点即可。

```C++
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
```