# 代码随想录算法训练营第十五天| 二叉树 Part02

## 今日题目

102.[二叉树的层序遍历](https://leetcode.cn/problems/binary-tree-level-order-traversal/)

107.[二叉树的层序遍历 II](https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/)

199.[二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/)

637.[二叉树的层平均值](https://leetcode.cn/problems/average-of-levels-in-binary-tree/)

429.[N 叉树的层序遍历](https://leetcode.cn/problems/n-ary-tree-level-order-traversal/)

515.[在每个树行中找最大值](https://leetcode.cn/problems/find-largest-value-in-each-tree-row/)

116.[填充每个节点的下一个右侧节点指针](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/)

117.[填充每个节点的下一个右侧节点指针 II](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/)

104.[二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

111.[二叉树的最小深度](https://leetcode.cn/problems/minimum-depth-of-binary-tree/)

226.[翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/)

101.[对称二叉树](https://leetcode.cn/problems/symmetric-tree/)

## LeetCode 102.二叉树的层序遍历

### 题目

给你二叉树的根节点 `root` ，返回其节点值的 **层序遍历** 。 （即逐层地，从左到右访问所有节点）。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGU2NjI3ZmM1ZWRhNWIxMWQ5YTg0YWEyZjQzYTY4YTdfUjlNeDBWcm1UZUVERzVPQnc3N2pDRFBUekpTR01zZ01fVG9rZW46SzFIRmJkcTdlb3dmZHR4bmRZV2NEOU9ZbnpmXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：[[3],[9,20],[15,7]]

### 思路

想到了用队列实现，但是没有想到如何控制每层的边界。一开始试图像迭代中序遍历一样，再每层结束后加入一个null节点，遍历队列遇到null节点表示前面是同一层，但是在实际代码中没找到插入null的正确方式。

看了视频将讲解后写出了AC代码，用size来记录每层的个数，每次遍历节点时size如果大于0，就将其子节点加入队列，size--；当size为0，就将tmp中存放的值加入的result，清空tmp，重置size为当前队列长度，也就是下一层的节点个数。

### 代码

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector<int>> result;
        queue <TreeNode*> q;
        vector <int> tmp;
        q.push(root);
        int size = q.size();
        while (!q.empty() || tmp.size() > 0) {
            if (size > 0) {
                TreeNode * node = q.front();
                q.pop();
                if (node != nullptr) {
                    tmp.push_back(node -> val);
                    if (node -> left) q.push(node -> left);
                    if (node -> right) q.push(node -> right);
                }
                size--;
            } else {
                result.push_back(tmp);
                tmp.erase(tmp.begin(),tmp.end());
                size = q.size();
            }            
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：该算法遍历了树中的每个节点一次，每个节点都被加入队列和从队列中移除一次。对于每个节点，操作的时间复杂度为常数时间 O(1)。因此，总的时间复杂度是 O(n)，其中 n 是树中节点的总数。

空间复杂度：`result` 存储了树的层序遍历结果，其空间复杂度为 O(n)，因为它需要存储树中所有节点的值。队列 `q` 在最坏的情况下（即树是完全平衡的），会存储最多一层的所有节点，这也是 O(n)。临时向量 `tmp` 在最坏的情况下（即树是完全平衡的），空间复杂度也是 O(n)。

综上所述，算法的总空间复杂度是 O(n)。

### 学习与小结

代码还是有许多冗余的地方，不适合作为模板，要学习简洁的代码：

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }
};
```

1. 将树空条件前置，不用再循环内判断节点是否为空；
2. 在循环内创建临时变量vec(同tmp)，省去了erase操作；
3. 将判断size的if语句改为了循环，这样优化了while循环的终止条件，避免了有时将所有队列元素出队后不进入循环的情况；
4. 如果要清空一个vector，clear比erase更有效率，更简洁。

## LeetCode 107.二叉树的层序遍历Ⅱ

### 题目

给你二叉树的根节点 `root` ，返回其节点值 **自底向上的层序遍历** 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NWUxYTk5N2E5OTA0NTZlYjBjMDZmMzdjNmNhZGZlYWRfeFh5eVFnWWJEbk51RThFRXdtS21xQ05BSHAyQlhsdVZfVG9rZW46UFFVaWJRTWZHb3hKZ1l4VmNtcGNCUUR6bkxiXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：[[15,7],[9,20],[3]]

### 思路

和普通层序遍历相同，最后将result数组反转即可。

有另一个思路是：同样用size标记每层个数，size为0，加入一个标记，数据结构用栈，孩子节点入栈时先右后左，最后出栈时，碰到标记说明一层已经结束。但是显然更复杂，没有必要实现了。

### **代码**

```C++
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <vector<int>> result;
        while (!q.empty()) {
            int size = q.size();
            vector <int> tmp;
            while (size--) {
                TreeNode * node = q.front();
                q.pop();
                tmp.push_back(node -> val);
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(tmp);
        }
        reverse(result.begin(),result.end());
        return result;
    }
};
```

### 时空复杂度

时间复杂度：因为每个节点只会入队和出队一次，所以总的操作次数与节点总数 `n` 成正比。因此，这段代码的时间复杂度是 **O(n)**，其中 `n` 是树中节点的总数。

空间复杂度：取决于用于存储结果的 `result` 向量和用于层序遍历的队列 `que`。

1. `vector<vector<int>> result` 将存储每个节点的值，最终的大小也会是 `n`，因此这部分的空间复杂度是 **O(n)**。
2. `queue<TreeNode*> que` 在最坏的情况下（例如完全二叉树的最后一层），队列可能包含 `n/2` 个节点（最后一层的节点数）。因此，队列所需的空间复杂度最坏为 **O(n)**。

综合起来，这段代码的总空间复杂度也是 **O(n)**。

## LeetCode 199.二叉树的右视图

### 题目

给定一个二叉树的 **根节点** `root`，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDEzMDZmN2VhOTFjNjlhN2NjMTkyMzE3M2Y4ODgxMDlfV1d0UWo0b0Zrb25GdHpUZzd3aG5TNXVRNTJvb3JXRzZfVG9rZW46TGl3WmJhVXpib0p6OUh4RHk1ZmNhbWF6bmtmXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入: [1,2,3,null,5,null,4] 输出: [1,3,4]

### 思路

还是层序遍历的思路，但是要在size == 1时，把值加入，表示是该层最后一个元素，即最右边的元素，也就是题目中说的右视角。

### 代码

```C++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q;
        if (root != NULL)
            q.push(root);
        vector<int> result;
        while (!q.empty()) {
            int size = q.size();
            while (size != 0) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                if (size == 1) result.push_back(node -> val);
                size--;
            }
        }
        return result;
    }
};
```

## LeetCode 637.二叉树的层平均值

### 题目

给定一个非空二叉树的根节点 `root` , 以数组的形式返回每一层节点的平均值。与实际答案相差 `10(-5)` 以内的答案可以被接受。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NDlhZWU2M2Q2OGY5NGY3MWE0MDE3YjViZmFmNmEyMjJfMk05WDRkblBGNHI0Y1VYajQwcEV2Ukk5bnBuaXN5Nk5fVG9rZW46VFJ0emJYUTA1bzAzdVR4QVpHVmNVNzdkbnpmXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：[3.00000,14.50000,11.00000] 解释：第 0 层的平均值为 3,第 1 层的平均值为 14.5,第 2 层的平均值为 11 。 因此返回 [3, 14.5, 11] 。

### 思路

层序遍历，对于每层的操作是计算其平均值，所以需要用sum来计算该层所有元素之和，用count来保留当前层的元素个数，从而求出平均值。

### 代码

```C++
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
```

### 学习与小结

之前层序遍历代码中，对于size的while循环和for循环功能相同。但在此题，计算平均值需要size值不改变，如果用while循环，size的值会一直减小直至为0，还需要另一个值来保存size一开始的大小。而for循环不回改变size的大小，计算均值时可以直接使用。

```C++
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        vector<double> result;
        while (!que.empty()) {
            int size = que.size();
            double sum = 0; 
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                sum += node->val;
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(sum / size);
        }
        return result;
    }
};
```

## LeetCode 429.N叉树的层序遍历

### 题目

给定一个 N 叉树，返回其节点值的*层序遍历*。（即从左到右，逐层遍历）。

树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MjQzNWQwNjEzNDgzYjAzNDRhOWUzOThlYTU0ZjllYjlfWkpNQUMxWmprb29uMGhUMkRXV1dDM3ptak9FTjhyTzVfVG9rZW46RmhyWWJSVGxab2t1aDB4bDhoQ2NGRnl3bjZnXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [1,null,3,2,4,null,5,6] 输出：[[1],[3,2,4],[5,6]]
>
> 示例 2：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmE2Y2NkMDFkNmI5NTlhODZlNWVmOTk3MzMwMDYxODVfZlB6UXV0WmVkQmdXWFhhamlVbjFLeGJEbHlkRDNHR1FfVG9rZW46TFdLOGJHUjVrb045SGN4MUYzR2NyeGRqblhnXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14] 输出：[[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

### 思路

将二叉树变为了N叉树，只需要将层序遍历插入左右孩子节点改为插入全部孩子节点即可。依旧属于是模板题。

### 代码

```C++
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
```

## LeetCode 515.在每个树行中找最大值

### 题目

给定一棵二叉树的根节点 `root` ，请找出该二叉树中每一层的最大值。

> 示例1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MjNmMDUzNTA3ZjRhMzBkYTI0OTI5M2M1YjcwMmExMDZfZUV1QVFBTzR1a3FtSWFZd3NmcnkzTDVaWnpVdjg1eGNfVG9rZW46RGpKcGJHbHJsb0NmcGV4OEZPOGNiajdCblBiXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入: root = [1,3,2,5,3,null,9] 输出: [1,3,9]

### 思路

每次遍历节点时，比较当前值与最大值，如果当前值更大，替换即可。

### 代码

```C++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue <TreeNode *> q;
        if (root != NULL) q.push(root);
        vector <int> result;
        while (!q.empty()) {
            int size = q.size();
            int max = INT32_MIN;
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                max = node -> val > max ? node -> val : max;
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
            result.push_back(max);
        }
        return result;
    }  
};
```

## LeetCode 116.填充每个节点的下一个右侧节点指针

### 题目

给定一个 **完美二叉树** ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

> struct Node {
>
>   int val;
>
>   Node *left;
>
>   Node *right;
>
>   Node *next;
>
> }

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 `NULL`。

初始状态下，所有 next 指针都被设置为 `NULL`。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzcwM2I2NGIxYzdmZDIxMTY2YmE4YjhlZjk3ZmFhODJfb0J5MVdDTzhXRTNGMEVacUgxSUZncWJPcXVFZjB6UDVfVG9rZW46RjRSQmJhbkdOb2NGWkp4NlAwdWNkb29KbmlmXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [1,2,3,4,5,6,7] 输出：[1,#,2,3,#,4,5,6,7,#] 解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化的输出按层序遍历排列，同一层节点由 next 指针连接，'#' 标志着每一层的结束。

### 思路

层序遍历时，如果遍历到了该层的末尾（i == size - 1），就让node的next指向NULL；如果不是末尾，就让node的next指向q.front()，因为在取到node后就将其出队，所以当前的队首就是它的邻居节点。

### 代码

```C++
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
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node ->right);
                if (i == size - 1) {
                    node -> next = NULL;
                } else {
                    node -> next = q.front();
                }
            }
        }
        return root;
    }
};
```

## LeetCode 117.填充每个节点的下一个右侧节点指针II

### 题目

给定一个二叉树：

> struct Node {
>
>   int val;
>
>   Node *left;
>
>   Node *right;
>
>   Node *next;
>
> }

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 `NULL` 。

初始状态下，所有 next 指针都被设置为 `NULL` 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTI3ZTg0YTY2ZGU0Yjc5YjgxZWQxYThlODYxZGQwMTlfRHVpUDNGclFXUE1oM1JoTlU3dDZwd29ialNhcGRFSVdfVG9rZW46VmxiZGJPYTZUb2RldUl4Q01kMGNmeFhEbnJmXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [1,2,3,4,5,null,7] 输出：[1,#,2,3,#,4,5,7,#] 解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化输出按层序遍历顺序（由 next 指针连接），'#' 表示每层的末尾。

### 思路

和上题思路相同，因为所有的next指针均被初始化为NULL，所以可以省去到达该层末尾的赋值操作。

### 代码

```C++
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
```

## LeetCode 104.二叉树的最大深度

### 题目

给定一个二叉树 `root` ，返回其最大深度。

二叉树的 **最大深度** 是指从根节点到最远叶子节点的最长路径上的节点数。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NzBhNjcyMWZhZjc4M2Y3MGJmMjI2ZDgwNjY4ZDFkM2VfSGx0Q0RXZjhtQ2NMRkd3NXdaZEVnUDVGYnNEa1pKUGpfVG9rZW46U0FvUWJKa2tPb3QwZ3B4NUJtOWNrVmV1blhnXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：3

### 思路

层序遍历找深度，每层遍历完深度加一即可。

### 代码

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
                if (node -> right) q.push(node -> right);
            }
            depth++;
        }
        return depth;
    }
};
```

## LeetCode 111.二叉树的最小深度

### 题目

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

**说明：**叶子节点是指没有子节点的节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2UwYjcwZjM2NmEyMzY2ZGU2NDI2ZDY4YjAxNTMyZjdfSzRUSlNLSFI1Q1pqYTU1V3ZDQ3BnY3dJcDVNUFlnTk9fVG9rZW46V2RhVGJRc0tmb05kVnh4a0hTV2NVY3FWbkZiXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [3,9,20,null,null,15,7] 输出：2

### 思路

按层序遍历，如果遍历到某个节点没有左右孩子，说明到达了最底层，返回层数即可。

### 代码

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        queue <TreeNode *> q;
        if (root == NULL) {
            return 0;
        }
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left == NULL && node -> right == NULL) {
                    return ++depth;
                } else {
                    if (node -> left) q.push(node -> left);
                    if (node -> right) q.push(node -> right);
                }
            }
            depth++;
        }
        return depth;
    }
};
```

## LeetCode 226.翻转二叉树

### 题目

给你一棵二叉树的根节点 `root` ，翻转这棵二叉树，并返回其根节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MTgxNjAwOGIzNjAyNDEzZTAwODg0NjY3Y2Q1MDc0YjVfUnhvaTRSUVNrc1Y5OXEwdmRwc0VtWU54YXlHbEU5WWlfVG9rZW46UTNyeGJWSzFIb1VZN0h4MFFYNWNlWmQybkRnXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [4,2,7,1,3,6,9] 输出：[4,7,2,9,6,3,1]

### 思路

观察示例发现就是交换左右孩子节点，所以写了递归函数：

1. 参数和返回值：参数就直接操作传入的这棵树，没有返回值；
2. 终止条件：树为空就不再有左右孩子，所以树空终止；
3. 每次递归的处理逻辑：每次将传入的节点视作根节点，交换其左右孩子；再递归调用函数，传入左右孩子作为参数，即下次处理的根节点。

### 代码

```C++
class Solution {
public:
    void transferLR(TreeNode *&root) {
        if (root == NULL) return;
        if (root -> left || root -> right) {
            TreeNode * tmp = root -> left;
            root -> left = root -> right;
            root -> right = tmp;
        }
        transferLR(root -> left);
        transferLR(root -> right);
    }
    TreeNode* invertTree(TreeNode* root) {
        transferLR(root);
        return root;
    }
};
```

### 时空复杂度

时间复杂度：递归调用 `transferLR(root -> left)` 和 `transferLR(root -> right)` 意味着算法将访问树中的每个节点一次。因为树中的每个节点都会被访问一次，并且每个节点的操作是常数时间的，所以 `transferLR` 的总体时间复杂度是 **O(n)**，其中 `n` 是树中节点的数量。

空间复杂度：

- 递归栈的最大深度等于树的高度。在最坏的情况下，即树完全不平衡，树的高度可以是 `n`（每个节点都只有一个子节点）。因此，在最坏的情况下，空间复杂度为 **O(n)**。
- 在最好的情况下，即树是完全平衡的，树的高度是 `log(n)`。因此，最好情况下的空间复杂度为 **O(log(n))**。
- 算法除了递归栈之外没有使用额外的空间（交换子节点不需要额外空间，因为它是在原地进行的）。

综上所述，`transferLR` 和 `invertTree` 方法的空间复杂度在最好的情况下是 **O(****log****(n))**，在最坏的情况下是 **O(n)**，其中 `n` 是树中节点的数量。

### 学习与小结

这道题其实我使用的是前序遍历的思想，但是自己在写的时候没有意识到。

针对二叉树的问题，解题之前一定要想清楚究竟是前中后序遍历，还是层序遍历。

二叉树解题的大忌就是自己稀里糊涂的过了（因为这道题相对简单），但是也不知道自己是怎么遍历的。

这也是造成了二叉树的题目“一看就会，一写就废”的原因。

但是递归不够优化，完全可以用一个函数来做：

```C++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        swap(root->left, root->right);  // 中
        invertTree(root->left);         // 左
        invertTree(root->right);        // 右
        return root;
    }
};
```

## LeetCode 101. 对称二叉树

### 题目

给你一个二叉树的根节点 `root` ， 检查它是否轴对称。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NGQ4YjE0OTY2NzZkMTczNjg1ZWRkM2I4NWQ1ZmM3NjNfUnhWbzZNMkllTG9XUmtRamNOejhnSzZNWmdtbnRpMmRfVG9rZW46TzlzSGJYTE1Sb2x1STV4TFdDaGNWRDhKblVnXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)
>
> 输入：root = [1,2,2,3,4,4,3] 输出：true

### 思路

刚做过上一题翻转二叉树，看到这道题我的第一想法是直接将树的左子树翻转，然后去和右子树比较不就可以了吗？结果显示是不行，因为不能仅仅使用 `newLeft == right` 来直接比较翻转后的左子树 `newLeft` 和原始的右子树 `right`。在 C++ 中，这样的比较只会**比较两个指针的地址**，而不会比较指针指向的树的结构和节点的值。

为了正确地比较两棵树，需要递归地比较两棵树的每个节点。你需要确保以下条件都满足：

- 当前两个节点的值相等。
- 一棵树的左子节点和另一棵树的右子节点相等（镜像对称位置的节点）。
- 一棵树的右子节点和另一棵树的左子节点相等。

#### 递归解法

1. 参数和返回值：参数就是左右两棵子树，返回值返回是否对称，为bool变量；
2. 终止条件：如果左右两棵树同时为空，返回true；只有一棵为空，返回false；都不为空但节点值不相同，返回false；
3. 递归逻辑：首先比较节点的值，这一点在终止条件3有体现；outside是比较了左子树的左子树与右子树的右子树是否相同，即树的外侧；inside是树的内侧，最后返回结果。这里实际上是后序遍历的体现，对于左子树来说，先看**左**，再看**右**，结果是左右的结合，相当于看**中（尽管不是严格的后序遍历）。**

#### 迭代解法

如何使用迭代法呢？迭代法主要是要将对称位置的两个节点成对取出来做前面提到的比较（是否都空，值是否相同等），那么我们可以用队列或者栈来存放对应的节点。

### 代码

递归代码：

```C++
class Solution {
public:
    bool isMirror(TreeNode * left, TreeNode * right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        if (left -> val != right -> val) return false;
        bool outside = isMirror(left -> left, right -> right);
        bool inside = isMirror(left -> right, right -> left);
        return outside && inside;
    }
    bool isSymmetric(TreeNode* root) {
        return isMirror(root -> left, root -> right);
    }
};
```

迭代代码：

迭代要注意如果两个都为空不能直接返回true，只能说明此时此刻是对称的，不能直接说明整体是对称的，因为队列中可能还有没处理的元素：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTk3ZTYwOGU3MTRhYWYwMDgzM2ZhNTQ3MTZhOTkyM2Zfem5FWXRFckVZNG95N1A3ZzlvN0ZVZGdVSGpmaVRMR2JfVG9rZW46TEpYTGJHOWxnb3dmZ054NnRsbmNFTUthbmFjXzE3MDQ4ODQxODY6MTcwNDg4Nzc4Nl9WNA)

像这棵树，当访问到左边-42的左节点和右边-42的右节点，两个都为空，只能说明遍历到此时此刻树是对称的，显然后面有不对称的部分。

```C++
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        queue <TreeNode *> q;
        q.push(root -> left);
        q.push(root -> right);
        while (!q.empty()) {
            TreeNode * left = q.front();
            q.pop();
            TreeNode * right = q.front();
            q.pop();
            if (left == NULL && right == NULL) continue;
            if (left == NULL || right == NULL) return false;
            if (left -> val != right -> val) return false;
            q.push(left -> left);
            q.push(right -> right);
            q.push(left -> right);
            q.push(right -> left);
        }
        return true;
    }
};
```

### 时空复杂度

时间复杂度：O(n)，其中 n 是树中节点的数量。这是因为我们需要访问树中的每个节点一次，来比较它们是否对称。`isMirror` 函数会对每个节点调用一次，而每个节点只会被访问一次。

空间复杂度：最坏的情况是 O(n)，这是在树完全不平衡时发生的，例如所有的节点都在一边的情况。这种情况下，递归调用会在调用栈上累积，直到它到达叶子节点。在最好的情况下，如果树是完全平衡的，空间复杂度是 O(log n)，其中 n 是树中节点的数量。这是因为递归树的高度将是 log n，每层递归调用都需要一些空间。

### 学习与小结

这道题首先要明确比较的本质，不能想当然的用指针来比较，指针存放的是内存中的地址。

其次就是要对称着比较，左的左和右的右，左的右和右的左。