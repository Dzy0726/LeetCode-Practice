# 代码随想录算法训练营第二十三天| 二叉树 Part09

## 今日题目

669.[修剪二叉搜索树](https://leetcode.cn/problems/trim-a-binary-search-tree/)

108.[将有序数组转换为二叉搜索树](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/)

538.[把二叉搜索树转换为累加树](https://leetcode.cn/problems/convert-bst-to-greater-tree/)

## LeetCode 669.修剪二叉搜索树 

### 题目

给你二叉搜索树的根节点 `root` ，同时给定最小边界`low` 和最大边界 `high`。通过修剪二叉搜索树，使得所有节点的值在`[low, high]`中。修剪树 **不应该** 改变保留在树中的元素的相对结构 (即，如果没有被移除，原有的父代子代关系都应当保留)。 可以证明，存在 **唯一的答案** 。

所以结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTVlMTUwZTM1ZDZiODc2OGRiYjdhY2JiYjY5ZTJkYmZfcDY4cHFwZVplUElhZzYxRmV3QlBKd201cjJ3alY1SGVfVG9rZW46SktSM2JPSFZpb2toVmt4YzV3SGNqdXJkbmlUXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)
>
> 输入：root = [1,0,2], low = 1, high = 2 输出：[1,null,2]
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NjBjNzUyMGFiYzZmYjBiZTQ0MjMwNTQ2MDcyMmQxOWJfUW15eVZ6UGJzZjh3MlBNWWpCcGNtUGZJSTJ2ekhDem5fVG9rZW46SmNQc2JIZU1Fb2VhYlR4ZWxwV2NXSFB6blhlXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)
>
> 输入：root = [3,0,4,null,2,null,null,1], low = 1, high = 3 输出：[3,2,null,1]

### 思路

最开始想着和昨天的删除二叉搜索树的节点一样，重构整个二叉搜索树，但是发现不断陷入内存访问错误。

其实这道题如果重构的话，就没有利用到二叉搜索树的性质。如果一个节点的值小于区间的最小值，那么就没有必要看它的左子树，因为他的左子树的全部值一定都小于区间最小值。同理，如果节点的值大于区间的最大值，也没有必要看该节点的右子树，右子树的全部节点必定都大于区间的最大值。所以我们只需要对不满足条件的节点的单个子树进行处理即可。

如何处理？递归三部曲：

1. 参数及返回类型：参数为传入当前节点，区间上下界；返回类型最后返回TreeNode，修剪完之后的树。
2. 终止条件：如果当前节点为空，返回NULL；
3. 单层递归逻辑：对于不满足条件的节点单个子树进行递归处理，看它的子树是否满足条件。

删除某个节点后，它的孩子是怎么处理的？

我们可以模拟示例二中删除0节点的过程：

1. root=3，符合区间条件，递归处理其左子树（root -> left = trimBST(root -> left, low, high)）:
   1. root=0，不符合区间条件，递归处理其右子树：
      1. root=2，符合区间条件，递归处理其左子树：
         1. root=1，符合区间条件，递归处理其左子树：左子树为空，返回NULL，即root=1 -> left = NULL；
         2. root=1，递归处理其右子树：右子树为空，返回NULL，即root=1 ->right = NULL；
      2. root=2左子树处理完成，即root=2 -> left = (1)；递归处理其右子树：右子树为空，返回NULL，即root=2 -> right = NULL；
   2. root=0的右子树处理完成，return right，即return (2)->((1),NULL)；
2. root=3的左子树处理完成，即root=3->left = (2)->((1),NULL)；
3. root=3，递归处理其右子树，发现符合条件，不再赘述。

通过上述过程，我们得知，0不符合条件，递归它的右子树，右子树符合条件，返回它的右子树，返回给了0上一层3的left，用3->left接住了0返回上来的0->right。

### 代码

```C++
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == NULL) return root;
        if (root -> val < low) {
            TreeNode* right = trimBST(root -> right, low, high);
            return right;
        } else if (root -> val > high) {
            TreeNode* left = trimBST(root -> left, low, high);
            return left;
        } else {
            root -> left = trimBST(root -> left, low, high);
            root -> right = trimBST(root -> right, low, high);
        }
        return root;
    }
};
```

### 学习与小结

我认为这道题自己没做出来的主要原因是没有想到如果节点值小于low，说明该节点的左侧就不用再处理，单独处理右侧就好；次要原因是对递归的理解也不够深入，没有想到单独处理右侧时用递归处理，而是直接返回了右侧节点。

## LeetCode 108.将有序数组转换为二叉搜索树 

### 题目

给你一个整数数组 `nums` ，其中元素已经按 **升序** 排列，请你将其转换为一棵 **高度平衡** 二叉搜索树。

**高度平衡** 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZWE4MTNhNDVkODkzNTEwNzVlZDM4NjkyNDk4ZjA3M2JfbVRXaGlpbmx6M0FoZTJvVEZnNjdROTBzYUpYQ3N0ZGpfVG9rZW46VWRDdmJQMXRVb3ZNWTJ4ZjVQaGNvU2hKbmFlXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)
>
> 输入：nums = [-10,-3,0,5,9] 输出：[0,-3,9,-10,null,5] 解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODNkYjJhNzI2MTdiNjJmNGZiYjgzYTgwMzZhZDQyZmVfSjlTQTdXY1FWQ0FSZDA3RUt3RGJjdnlXOE9ncVRUN3VfVG9rZW46T0xKOGJhNTQ1b1lPckF4dDF0RWN1NnREbllmXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)

### 思路

给定严格有序的数组，构造平衡的二叉搜索树，思路就和二分查找差不多。取中间值当做根节点，用根节点所在位置划分左右两个子树，递归构造即可。

递归三部曲：

1. 参数及返回类型：参数传入数组引用，数组起始和终止位置作为当前子树的范围；返回TreeNode*，即返回构造好的子树；
2. 终止条件：如果begin>end，说明数组用完了，子树为空，返回NULL；
3. 单层递归逻辑：子树不空，找到中间位置，找到中间值，构建子树根节点，利用中间位置划分左右子树的区间，递归构造其左右子树，最终返回root。

### 代码

```C++
class Solution {
public:
    TreeNode* buildTree(vector<int>& nums, int begin, int end) {
        if (begin > end) return NULL;
        int mid = (begin + end) / 2;
        int midVal = nums[mid];
        TreeNode* root = new TreeNode(midVal);
        root -> left = buildTree(nums, begin, mid - 1);
        root -> right = buildTree(nums, mid + 1, end);
        return root;

    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildTree(nums, 0, nums.size() - 1);
    }
};
```

### 学习与小结

1. 区间是**左闭右闭**；
2. 取数组中间位置直接用(begin + end) / 2不好，如果begin和end很大，和会超过int范围，写二分法必须有意识：

```C++
int mid = left + ((right - left) / 2);
```

## LeetCode 538.把二叉搜索树转换为累加树

### 题目

给出二叉 **搜索** 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 `node` 的新值等于原树中大于或等于 `node.val` 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

- 节点的左子树仅包含键 **小于** 节点键的节点。
- 节点的右子树仅包含键 **大于** 节点键的节点。
- 左右子树也必须是二叉搜索树。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjdiNzQwOTRkNDZkZTljYTQ3Y2EwYWE4ZDA0OGVkNmVfMGlSUE02VlRmRmswQTE2QkdwVUp0aUswTjFXNnBLbWFfVG9rZW46S3p0bmI5cHg2b0s0NmZ4cGJWcWN4R1NGbkNmXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)
>
> 输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8] 输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

### 思路

最开始想着中序遍历二叉搜索树，得到一个升序数组；然后倒着从末尾更改数组的值，再用新数组构成一个二叉搜索树。但是发现样式会发生变化，所以行不通。

后面就努力的想递归怎么做，我想的递归是：

1. 参数及返回值：参数就是传入当前节点的引用（因为要修改当前节点），考虑到整个树都要修改，所以返回值为空。
2. 终止条件：如果当前节点的右孩子为空，就修改当前节点的值为全局变量sum；
3. 单层递归逻辑：右孩子不为空，就一直向右下递归遍历；找到最右下的孩子后，开始修改，并加到sum中；如果节点有左孩子，再递归求左孩子的和。

说实话，思路不是特别清晰，基本是看着示例一点点改出来的，然后就AC了。所以还得学。

### 代码

```C++
class Solution {
public:
    int sum = 0;
    void getSum(TreeNode*& root) {
        if (root -> right) {
            getSum(root -> right);
        }
        sum += root -> val;
        root -> val = sum;
        if (root -> left) {
            getSum(root -> left);
        }
    }
    TreeNode* convertBST(TreeNode* root) {
        if (root == NULL) return root;
        getSum(root);
        return root;
    }
};
```

### 学习与小结

1. 好的一点是想到了“反中序遍历”，自己的遍历顺序也是右中左；想到了要遍历整棵树，所以返回类型为空。但没想到用双指针，pre指向前一个节点的值，于是处理中间节点就变为当前节点的值加上前一个节点的值，再将pre改成前一个节点的值。从代码看起来sum和pre的作用差不多，sum记录当前的总和，pre记录上一个节点的值，误打误撞好像写了一个很对的代码，但终止条件没有想清楚，如果当前节点为空，直接返回不做修改。这样的话就不用判断左右孩子是否存在，直接递归遍历即可。

   1. ```C++
      class Solution {
      public:
          int pre = 0;
          void reInorder(TreeNode* root) {
              if (root == NULL) return;
              reInorder(root -> right);
              root -> val += pre;
              pre = root -> val;
              reInorder(root -> left);
          }
      
          TreeNode* convertBST(TreeNode* root) {
              reInorder(root);
              return root;
          }
      };
      ```

从结果代码来看，好像就是做了一次简单的反中序遍历……但是其实想的过程有些复杂。

1. 迭代法之前用模版用的不亦乐乎，但是这道题也没想到迭代法的解法。统一迭代的方法再复习一次。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YjUwYzZkZjZhODcwM2Q3MDM0ODAwNzVkNmViZDBiYWJfekZtQ242RzRZYWxOalY0c0FSWDkwcnBWUlFZd2ZyTU1fVG9rZW46WnhBR2J5aWRab3dwdUl4UUE0MGNFTk9Qbm9lXzE3MDU1NDgwODk6MTcwNTU1MTY4OV9WNA)