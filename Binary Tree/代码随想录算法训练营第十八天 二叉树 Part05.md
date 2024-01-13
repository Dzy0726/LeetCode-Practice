# 代码随想录算法训练营第十八天| 二叉树 Part05

## 今日题目

513.[找树左下角的值](https://leetcode.cn/problems/find-bottom-left-tree-value/)

112.[路径总和](https://leetcode.cn/problems/path-sum/)

113.[路径总和 II](https://leetcode.cn/problems/path-sum-ii/)

106.[从中序与后序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)

105.[从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

## LeetCode 513.找树左下角的值

### 题目

给定一个二叉树的 **根节点** `root`，请找出该二叉树的 **最底层 最左边** 节点的值。

假设二叉树中至少有一个节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NDAyMTNmZGE2NDQxMWIxNDIwNTg4MzRkNDdjNTM3YWVfQ3ppQnVCeFNSc3g5SlVOTkQyVTQ0T1cwZWRWT1haQ2NfVG9rZW46TkpCV2JpMndOb1ROZUF4N0JQMGNBM0dKblBmXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入: root = [2,1,3] 输出: 1
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDI1MzhkMzJlZTA0ZTI1NzdiNjRiYmNlNzhjMzVjYjNfdmQ1MWhBTzVENGc0MjdFaGpaMFk4eE9PZlRNRGxxbUVfVG9rZW46VTlMUWJHNzZrb095dEt4TWRBamN5ZXRLbk1oXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入: [1,2,3,4,null,5,6,null,null,7] 输出: 7

### 思路

要找到树左下角的值，先要找到最底层，然后是最底层的最左边的值。于是想到了层序遍历，层序遍历很方便找到最底层，而最左边的值也就是在层序遍历过程中，队列的第一个值。

所以只需要在层序遍历模板基础上，每层保存一下该层最左边的值，最后遍历完这棵树留下的就是最底层最左边的值。

### 代码

```C++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue <TreeNode *> q;
        int result = 0;
        if (root != NULL) q.push(root);
        while (!q.empty()) {
            result = q.front() -> val;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode * node = q.front();
                q.pop();
                if (node -> left) q.push(node -> left);
                if (node -> right) q.push(node -> right);
            }
        }
        return result;
    }
};
```

### 学习与小结

这道题用递归法会比迭代法复杂一点，不能简单的向左递归到头就是要求的节点，因为此时不一定到达最底层。所以还需要用一个参数来记录此时的深度，是否到达了最底层，只有深度最大才是最底层。

1. 参数和返回值：传入当前处理的节点和当前的深度，不需要返回值。（用全局变量记录结果和最大深度）
2. 终止条件：节点为叶子节点（左右孩子均为空），更新最大深度和结果。
3. 单层递归逻辑：在找最大深度的时候，递归的过程中依然要使用回溯

```C++
class Solution {
public:
    int maxDepth = INT_MIN;
    int result;
    void traversal(TreeNode* root, int depth) {
        if (root->left == NULL && root->right == NULL) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }
        if (root->left) {
            depth++;
            traversal(root->left, depth);
            depth--; // 回溯
        }
        if (root->right) {
            depth++;
            traversal(root->right, depth);
            depth--; // 回溯
        }
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return result;
    }
};
```

## LeetCode 112.路径总和

### 题目

给你二叉树的根节点 `root` 和一个表示目标和的整数 `targetSum` 。判断该树中是否存在 **根节点到****叶子节点** 的路径，这条路径上所有节点值相加等于目标和 `targetSum` 。如果存在，返回 `true` ；否则，返回 `false` 。

**叶子节点** 是指没有子节点的节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MGFmMWI0M2I0YzQ2OWRhMTBhODU3YmExMDg2ZGY4NjJfbzE2VkIwa1lneG9ybUNZd2gza2Mybmc3OFVUVHR6ZmtfVG9rZW46UjREeGJDZTg0b0ZSand4OXE5aWM2eW9lbkZjXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22 输出：true 解释：等于目标和的根节点到叶节点路径如上图所示。

### 思路

思路有点像257. 二叉树的所有路径，257所有路径要求输出录制，本题要求路径之和，将路径上的值保存下来，然后每次遇到叶子节点就求和看是否为目标值，如果是，返回true；若不是则回溯上一层继续递归。每次向vector加入值后，递归完要及时删除。回溯和递归一一对应！

### 代码

```C++
class Solution {
public:
    bool findPath(TreeNode * root, vector<int> &sum, int targetSum) {
        if (root -> left == NULL && root -> right == NULL) {
            int s = 0;
            for (int i = 0; i < sum.size(); i++) {
                s += sum[i];
            }
            s += root -> val;
            if (s == targetSum) return true;
        }
        if (root -> left) {
            sum.push_back(root -> val);
            if (findPath(root -> left, sum, targetSum) == false) {
                sum.pop_back();
            } else {
                return true;
            }
            
        }
        if (root -> right) {
            sum.push_back(root -> val);
            if (findPath(root -> right, sum, targetSum) == false) {
                sum.pop_back();
            } else {
                return  true;
            }
        }
        return false;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        vector <int> sum;
        if (root == NULL) return false;
        return findPath(root, sum, targetSum);
    }
};
```

### 学习与小结

代码逻辑还可以更加清晰简洁，首先是对上述代码进行优化 ：

1. **避免重复计算路径和**：在目前的实现中，每到达一个叶子节点时，都会重新计算一次路径和。可以通过将当前路径和作为参数传递给递归函数来避免这种重复计算。
2. **在找到符合条件的路径时立即返回**：一旦找到符合条件的路径，应该立即停止递归并返回结果，而不是继续执行其他不必要的递归调用。
3. **减少不必要的检查**：在递归调用 `findPath` 函数之后，无需再次检查返回值是否为 `false`，因为无论如何都要将当前值从 `sum` 向量中移除。

根据上述三点，可以优化代码为：

```C++
class Solution {
public:
    bool findPath(TreeNode* root, int currentSum, int targetSum) {
        if (root == NULL) return false; 
        currentSum += root->val;
        if (root->left == NULL && root->right == NULL) {
            return currentSum == targetSum;
        }
        return findPath(root->left, currentSum, targetSum) || 
               findPath(root->right, currentSum, targetSum);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return findPath(root, 0, targetSum);
    }
};
```

对于递归三部曲：

1. 参数及返回值：

参数：需要二叉树的根节点，还需要一个计数器，这个计数器用来计算二叉树的一条边之和是否正好是目标和，计数器为int型。

再来看返回值，递归函数什么时候需要返回值？什么时候不需要返回值？这里总结如下三点：

- 如果需要搜索整棵二叉树且不用处理递归返回值，递归函数就不要返回值。
- 如果需要搜索整棵二叉树且需要处理递归返回值，递归函数就需要返回值。 
- 如果要搜索其中一条符合条件的路径，那么递归一定需要返回值，因为遇到符合条件的路径了就要及时返回。

而本题我们要找一条符合条件的路径，所以递归函数需要返回值，及时返回。

1. 终止条件

把每个节点值存在vector显然非常麻烦，用currentSum累加会优化很多。还有一种思路是用targetSum做减法操作，每次递归减去当前节点的值。如果最后targetSum == 0，同时到了叶子节点的话，说明找到了目标和。如果遍历到了叶子节点，targetSum不为0，就是没找到。

1. 单层递归逻辑

左右孩子如果不为空，就递归左右子树，找到就及时返回true；最终没找到返回false。要注意回溯。

```C++
class Solution {
public:
    bool findPath(TreeNode* root, int targetSum) {
        if (targetSum == 0 && root -> left == NULL && root -> right == NULL) {
            return true;
        }
        if (root -> left == NULL && root -> right == NULL) {
            return false;
        }
        if (root -> left) {
            targetSum -= root -> left -> val;
            if (findPath(root -> left, targetSum) == true) {
                return true;
            }
            targetSum += root -> left -> val;
        }
        if (root -> right) {
            targetSum -= root -> right -> val;
            if (findPath(root -> right, targetSum) == true) {
                return true;
            }
            targetSum += root -> right -> val;
        }
        return false;
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return false;
        return findPath(root, targetSum - root -> val);
    }
};
```

## LeetCode 113.路径之和Ⅱ

### 题目

给你二叉树的根节点 `root` 和一个整数目标和 `targetSum` ，找出所有 **从根节点到****叶子节点** 路径总和等于给定目标和的路径。

**叶子节点** 是指没有子节点的节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NGZhNTExM2RiMTdmMDNiMWViMjQzZmI4YzVmNzlmNThfUW0xcWlBanhyanhIV0tGZWhKelRCYmpuQU1udEhKSm5fVG9rZW46VUV0dWJvNWVGb2hRUlN4RXh1ZWNvTHp2bmFiXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22 输出：[[5,4,11,2],[5,8,4,5]]

### 思路

这道题与上题比起来就不能简单地用curSum或者count来看是否存在路径，需要将路径上的值都保存下来。

递归三部曲：

1. 参数和返回值

因为需要遍历整个二叉树，所以返回值为空；参数需要传入当前处理的节点，当前的“路径”，目标值，结果集。后两者也可设为全局变量，对其进行引用操作。

1. 终止条件
   1.  如果当前路径和等于目标值，且已经是叶子节点，就把路径添加，然后返回；
2. 单层递归逻辑

先要求当前路径总和，如果左右子树存在，递归遍历左右子树，注意回溯与递归一一对应，将元素加入“路径”，递归完后还要将其删除。

### 代码

```C++
class Solution {
public:
    void findPath(TreeNode* root, vector<int> current, int targetSum, vector<vector<int>> &result) {
        int curSum = 0;
        for (int i = 0; i < current.size(); i++) {
            curSum += current[i];
        }
        if (root -> left == NULL && root -> right == NULL && curSum == targetSum) {
            result.push_back(current);
        }
        if (root -> left) {
            current.push_back(root -> left -> val);
            findPath(root -> left, current, targetSum, result);
            current.pop_back();
        }
        if (root -> right) {
            current.push_back(root -> right -> val);
            findPath(root -> right, current, targetSum, result);
            current.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> current;
        if (root == NULL) return result;
        current.push_back(root -> val);
        findPath(root, current, targetSum, result);
        return result;
    }
};
```

### 时空复杂度

时间复杂度：最坏的情况下我们仍然需要访问树中的每个节点一次，这使得时间复杂度保持为 `O(N)`，其中 `N` 是树中节点的数量.

空间复杂度：

- 最坏情况下的递归深度等于树的高度 `H`，因此递归调用栈占用的空间为 `O(H)`；
- `current` 向量在递归过程中最大的长度也是 `H`，因此需要 `O(H)` 的空间；
- 如果我们考虑输出结果 `result` 向量占用的空间，则在最坏的情况下（每条从根到叶子的路径都等于目标和），空间复杂度为 `O(N * H)`，因为每个节点都可能在结果中出现。

综合考虑，算法的总空间复杂度是 `O(N * H)`，其中 `N` 是树中节点的数量，`H` 是树的高度。如果树是一个平衡二叉树，`H`是对数级的，即 `O(log N)`；如果树是一个退化成链表的二叉树，`H` 是线性的，即 `O(N)`。

### 学习与小结

上述代码可以优化的地方有：

1. **传递引用以避免不必要的复制**：在 `findPath` 函数中，传递了 `current` 向量的副本给递归调用，这在每次递归时会造成不必要的复制。通过传递引用，我们可以避免这种复制。
2. **累积和的优化**：在每次递归调用 `findPath` 时都重新计算了当前路径的和，这是不必要的。我们可以通过累加当前节点的值来维护一个运行时的路径和，而不是重新计算。
3. **提前终止**：如果当前路径和已经超过了目标和，我们可以提前终止，因为所有后续路径的和只会更大。

```C++
class Solution {
public:
    void findPath(TreeNode* root, vector<int> &current, int curSum, int targetSum, vector<vector<int>> &result) {
        if (!root) return; // 如果节点为空，直接返回。
        curSum += root->val; // 更新当前路径和。
        current.push_back(root->val); // 将当前节点值加入到路径中。
        // 如果是叶子节点，并且当前路径和等于目标和，将其添加到结果中。
        if (root->left == NULL && root->right == NULL && curSum == targetSum) {
            result.push_back(current);
        } else {
            // 递归搜索左右子树。
            findPath(root->left, current, curSum, targetSum, result);
            findPath(root->right, current, curSum, targetSum, result);
        }
        // 回溯：在返回父节点之前从当前路径中移除当前节点。
        current.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> current;
        if (root == NULL) return result;
        findPath(root, current, 0, targetSum, result);
        return result;
    }
};
```

## LeetCode 106.从中序与后序遍历序列构造二叉树

### 题目

给定两个整数数组 `inorder` 和 `postorder` ，其中 `inorder` 是二叉树的中序遍历， `postorder` 是同一棵树的后序遍历，请你构造并返回这颗 *二叉树* 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDcyMWU0MDAxYWJmNWZkY2NlNDQwZDgxOGFlYTVmNzNfNk8wRUV4VE5oVjhQZ2JMUWtTMjFDNjVzYWpyc3I5UWlfVG9rZW46SG12bWJ6SkRrb2hXMnh4dERpcWNBVnJXbkNoXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3] 输出：[3,9,20,null,null,15,7]

### 思路

由中后序遍历构成二叉树思路非常简单，从后序数组中找出二叉树的根，再根据这个根分割中序数组为左右两棵子树，再在后序数组中找左右子树的根节点，如此反复。这思路里蕴藏了浓浓的递归思想。

- 第一步：如果数组大小为零的话，说明是空节点了。
- 第二步：如果不为空，那么取后序数组最后一个元素作为节点元素。
- 第三步：找到后序数组最后一个元素在中序数组的位置，作为切割点
- 第四步：切割中序数组，切成中序左数组和中序右数组 
- 第五步：切割后序数组，切成后序左数组和后序右数组
- 第六步：递归处理左区间和右区间

### 代码

根据上述步骤，找好切割点和区间，写出如下代码：

```C++
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty()) {
            return NULL;
        }
        int root_val = postorder.back();
        postorder.pop_back();
        TreeNode* root = new TreeNode(root_val);
        auto itInorderRoot = find(inorder.begin(), inorder.end(), root_val);
        vector<int> inLeft(inorder.begin(), itInorderRoot);
        vector<int> inRight(itInorderRoot + 1, inorder.end());
        vector<int> postLeft(postorder.begin(), postorder.begin() + inLeft.size());
        vector<int> postRight(postorder.end() - inRight.size(), postorder.end());
        root -> left = buildTree(inLeft, postLeft);
        root -> right = buildTree(inRight, postRight);
        return root;
    }
};
```

### 学习与小结

上述代码不高效，因为频繁地使用 `insert` 和 `find` 操作，并且在每个递归调用中创建了新的向量。更高效的实现通常是通过使用迭代器来直接操作原始的 `inorder` 和 `postorder` 向量的子区间，这样可以避免额外的空间开销和不必要的元素复制。

1. 向量的拷贝：代码中有四次向量拷贝的操作，这是非常耗时的，特别是对于大数据集来说。你可以通过传递索引来避免这些拷贝。
2. 线性查找：通过 `std::find` 在中序遍历中查找根节点的索引是一个 O(N) 的操作，这在每次递归中都会重复执行，增加了整体的时间复杂度。
3. 空向量的检查：代码使用 `postorder.empty()` 来判断何时停止递归。这是一个有效的终止条件，但由于每次递归都会创建新的向量，这个检查可以避免。

改进后的代码：

```C++
class Solution {
    unordered_map<int, int> inorderIndexMap;
    TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, int postStart, int postEnd, int inStart, int inEnd) {
        if (postStart > postEnd) {
            return NULL;
        }
        int root_val = postorder[postEnd];
        TreeNode* root = new TreeNode(root_val);
        int inRootIndex = inorderIndexMap[root_val];
        root->left = buildTreeHelper(inorder, postorder, postStart, postStart + inRootIndex - inStart - 1, inStart, inRootIndex - 1);
        root->right = buildTreeHelper(inorder, postorder, postStart + inRootIndex - inStart, postEnd - 1, inRootIndex + 1, inEnd);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderIndexMap[inorder[i]] = i;
        }
        return buildTreeHelper(inorder, postorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
    }
};
```

中序左右子数组的边界很好确定，通过map找到根节点在中序数组中的索引（下标），那么中序左数组就是0~该下标-1，右数组是下标+1~中序数组末尾。二者都是左闭右闭；

中序左数组从 `inStart` 到 `inRootIndex - 1` 的范围表示左子树。左子树的节点数量是 `inRootIndex - inStart`。在后序遍历中，左子树的节点从 `postStart` 开始，连续排列，数量相同。因此，后序遍历中左子树的结束索引是起始索引 `postStart` 加上左子树的节点数量减去 1。

## LeetCode 105.从前序与中序遍历序列构造二叉树

### 题目

给定两个整数数组 `preorder` 和 `inorder` ，其中 `preorder` 是二叉树的**先序遍历**， `inorder` 是同一棵树的**中序遍历**，请构造二叉树并返回其根节点。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZWZlMzBmMmJiYmVhYmYxMGRmYWUxMTNiNmE5MTRmYWVfNmR5NzI2RVd4WEVFOGlPOGZTdXd4aXVRM2M4UU1XaktfVG9rZW46QnVSamIzY05Rb1QxTFZ4eGZuYmN2cTdZbmVyXzE3MDUxMzAxOTM6MTcwNTEzMzc5M19WNA)
>
> 输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7] 输出: [3,9,20,null,null,15,7]

### 思路

和上题一样，只要确定好前序左右数组的边界即可。

### 代码

```C++
class Solution {
public:
    unordered_map<int, int> index;
    TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd) return NULL;
        int rootValue = preorder[preStart];
        TreeNode * root = new TreeNode(rootValue);
        int rootIndex = index[rootValue];
        root -> left = buildTreeHelper(preorder, inorder, preStart + 1, preStart + rootIndex - inStart , inStart, rootIndex - 1);
        root -> right = buildTreeHelper(preorder, inorder, preStart + rootIndex - inStart + 1 , preEnd, rootIndex + 1, inEnd);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            index[inorder[i]] = i;
        }
        return buildTreeHelper(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};
```