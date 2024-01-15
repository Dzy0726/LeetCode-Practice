# 代码随想录算法训练营第二十天| 二叉树 Part06

## 今日题目

654.[最大二叉树](https://leetcode.cn/problems/maximum-binary-tree/)

617.[合并二叉树](https://leetcode.cn/problems/merge-two-binary-trees/)

700.[二叉搜索树中的搜索](https://leetcode.cn/problems/search-in-a-binary-search-tree/)

98.[验证二叉搜索树](https://leetcode.cn/problems/validate-binary-search-tree/)

## LeetCode **654.最大二叉树**

### 题目

给定一个不重复的整数数组 `nums` 。 **最大二叉树** 可以用下面的算法从 `nums` 递归地构建:

1. 创建一个根节点，其值为 `nums` 中的最大值。
2. 递归地在最大值 **左边** 的 **子数组前缀上** 构建左子树。
3. 递归地在最大值 **右边** 的 **子数组后缀上** 构建右子树。

返回 *`nums`* *构建的* ***最大二叉树*** 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzE5M2MzZTRiZDVkMDUzNDA3ODc4NmMzZTE0N2U4YWZfVEpFeFVneHRJVlRiVXlsb0FQcm9YSmRCaHhzeWRhbU9fVG9rZW46VVhXVmJhTjNEb05yZjB4MG9QeGNHeFd5blVoXzE3MDUzMDgyMjE6MTcwNTMxMTgyMV9WNA)
>
> 输入：nums = [3,2,1,6,0,5] 输出：[6,3,5,null,2,0,null,null,1]
>
> 解释：递归调用如下所示： - [3,2,1,6,0,5] 中的最大值是 6 ，左边部分是 [3,2,1] ，右边部分是 [0,5] 。    - [3,2,1] 中的最大值是 3 ，左边部分是 [] ，右边部分是 [2,1] 。        - 空数组，无子节点。        - [2,1] 中的最大值是 2 ，左边部分是 [] ，右边部分是 [1] 。            - 空数组，无子节点。            - 只有一个元素，所以子节点是一个值为 1 的节点。    - [0,5] 中的最大值是 5 ，左边部分是 [0] ，右边部分是 [] 。        - 只有一个元素，所以子节点是一个值为 0 的节点。        - 空数组，无子节点。

### 思路

经过由前序中序/中序后序构造二叉树两道题，这道题略显“稚嫩”。每次从划定范围内找出最大值作为根节点，并记录下根节点的位置以便于下次划分范围，然后递归构造左右子树。EZPZ~

### 代码

```C++
class Solution {
public:
    TreeNode* buildHelper(vector<int>& num, int start, int end) {
        if (start > end) return NULL;
        int maxNum = INT32_MIN;
        int count = 0;
        for (int i = start; i <= end; i++) {
            if (num[i] > maxNum) {
                maxNum = num[i];
                count = i;
            }
        }
        TreeNode * root = new TreeNode(maxNum);
        root -> left = buildHelper(num, start, count - 1);
        root -> right = buildHelper(num, count + 1, end);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) return NULL;
        return buildHelper(nums, 0, nums.size() - 1);
    }
};
```

### 时空复杂度

时间复杂度：

1. 对于每个节点，遍历了当前的子数组以找到最大值。在每次递归调用中，子数组的大小平均减半。
2. 在最坏的情况下，即输入数组是有序的，每次递归调用 `buildHelper` 都需要遍历整个子数组。这样，第一次调用需要时间 O(n)，第二次需要时间 O(n-1)，依此类推，直到 O(1)。因此，总的时间复杂度为 O(n^2/2)，简化为 O(n^2)。

在最好的情况下，如果每次找到的最大值都恰好把数组分成两半，那么时间复杂度会是 O(n log n)，因为这样的话，每层递归总共需要 O(n) 的时间，而递归的深度是 log n。

综上所述，时间复杂度在最坏情况下是 O(n^2)，最好情况下是 O(n log n)。

空间复杂度：

1. 由于递归的使用，空间复杂度主要取决于递归调用的最大深度，也就是树的高度。在最坏的情况下，树的高度可以是 n（输入数组有序时），因此空间复杂度为 O(n)。
2. 在最好的情况下，如果每次都能将数组分成两个大小相等的子数组，那么树的高度将是 log n，空间复杂度也是 O(log n)。
3. 同样，每个元素都需要创建一个新的 TreeNode，因此还需要 O(n) 的空间来存储树节点。

### 学习与小结

1. **性能**: 每次调用 `buildHelper` 函数时，都会遍历当前的子数组寻找最大值，这会导致算法的时间复杂度较高。在最坏的情况下，时间复杂度将是 O(n^2)，其中 n 是数组 `nums` 的长度。如果数组已经接近排序状态，每次递归调用都几乎遍历整个子数组。
2. **内存****管理**: 在C++中，使用 `new` 创建了一个新的 `TreeNode`。在实际应用中，还需要考虑内存的释放。虽然这个问题通常在面试或在线评测平台上不是问题，但在更大的系统中需要注意。

## LeetCode 617.合并二叉树

### 题目

给你两棵二叉树： `root1` 和 `root2` 。

想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，**不为** null 的节点将直接作为新二叉树的节点。

返回合并后的二叉树。

**注意:** 合并过程必须从两个树的根节点开始。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NzcwOWE3ZGFkNGM1NDU4YzQwMjQ1NjM0MDBjMDJiZGZfNUU3VzBzWExWbXdQWDJXNHpTUWhzWm5KRDFBcnByMTJfVG9rZW46QURGcWJ4c0pob0ZpUjJ4RW51S2NqRDZJbmRXXzE3MDUzMDgyMjE6MTcwNTMxMTgyMV9WNA)
>
> 输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7] 输出：[3,4,5,5,4,null,7]

### 思路

就是按照题目的要求进行合并，先对当前节点判断是否为空，再递归合并左右子树。还是比较简单的~

### 代码

```C++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL && root2 == NULL) return NULL;
        if (root1 == NULL) return root2;
        if (root2 == NULL) return root1;
        TreeNode * root = new TreeNode(root1 -> val + root2 -> val);
        root -> left = mergeTrees(root1 -> left, root2 -> left);
        root -> right = mergeTrees(root1 -> right, root2 -> right);
        return root;
    }
};
```

### 学习与小结

题目虽简单，但是用到递归还是要考虑递归三部曲：

1. 参数和返回值：要合并的两棵树的当前的节点，返回合并后的节点；
2. 终止条件：如果两个节点都为空，则返回空节点；有一个节点为空，返回另一个节点；
3. 单层递归逻辑：实际上我的代码是前序遍历的顺序，中左右，递归合并左右两子树。

## LeetCode 700.二叉搜索树中的搜索

### 题目

给定二叉搜索树（BST）的根节点 `root` 和一个整数值 `val`。

你需要在 BST 中找到节点值等于 `val` 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 `null` 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmNlZTg4OGRkZjQzOTg0Y2RhYjE2ODM5ZTJiNTg1ODFfZGNjOEJ0Y245SFdlOUtkOGpEbE85UkxkZkZIQWtLUGFfVG9rZW46S0ZCTmJZSjZsb1paN0N4Mm5uTWNLeno0bjBnXzE3MDUzMDgyMjE6MTcwNTMxMTgyMV9WNA)
>
> 输入：root = [4,2,7,1,3], val = 2 输出：[2,1,3]

### 思路

递归思路，前序遍历：

1. 参数及返回值：参数为当前遍历到的节点，返回值为节点类型；
2. 终止逻辑：如果当前节点为空，返回NULL；如果找到了val，返回当前节点；
3. 单层递归逻辑：只要节点不为空，比较它与val，如果相同则返回当前节点；如果val大于当前节点值，则递归遍历右子树；如果val小于当前节点值，则递归遍历左子树。

迭代思路，层序遍历：

当前值等于目标值，返回当前节点；当前值大于目标值，将左孩子加入队列；当前值小于目标值，将右孩子加入队列。队列不空就一直比较，队列为空说明没有找到，返回NULL。

### 代码

递归：

```C++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL) return NULL;
        TreeNode * result = NULL;
        if (root -> val == val) return root;
        else if (root -> val > val) result = searchBST(root -> left, val);
        else result = searchBST(root -> right, val);

        return result;
    }
};
```

迭代：

```C++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        queue <TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (node != NULL) {
                if (node -> val == val) return node;
                else if (node -> val > val) q.push(node -> left);
                else q.push(node -> right);
            }
        }
        return NULL;
    }
};
```

### 学习与小结

对于二叉搜索树可就不一样了，因为二叉搜索树的特殊性，也就是**节点的有序性**，可以不使用辅助栈或者队列就可以写出迭代法。

```C++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != NULL) {
            if (root->val > val) root = root->left;
            else if (root->val < val) root = root->right;
            else return root;
        }
        return NULL;
    }
};
```

## LeetCode 98.验证二叉搜索树

### 题目

给你一个二叉树的根节点 `root` ，判断其是否是一个有效的二叉搜索树。

**有效** 二叉搜索树定义如下：

- 节点的左子树只包含 **小于** 当前节点的数。
- 节点的右子树只包含 **大于** 当前节点的数。
- 所有左子树和右子树自身必须也是二叉搜索树。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTA3ZjkyY2YyYTcwNTVkMjZkMTg4YzE3ODRiMjIyYTFfN0JqekdQQVhZMTYxZE1MSnBQb3hqVGxtUEp2VE5YSDVfVG9rZW46Q1psUGJWRWZxb05WRnR4dlp2RWNVMG9RbkNnXzE3MDUzMDgyMjE6MTcwNTMxMTgyMV9WNA)
>
> 输入：root = [5,1,4,null,null,3,6] 输出：false 解释：根节点的值是 5 ，但是右子节点的值是 4 。

### 思路

只考虑了局部满足搜索二叉树性质，没有考虑全局的性质，导致只通过了76/84个测试用例。

如果遇到：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODNjZTQ3Y2UyMDBhZmRjNjU4NTZhZjhjZGNiYWYyNWVfRnd5V1pQdzVBNVhlYXNzd0UxcXFEV0w5RklWTzJUaENfVG9rZW46QlpKTGJ0T09jbzVNbnJ4RUhaa2NDdFBsbkdoXzE3MDUzMDgyMjE6MTcwNTMxMTgyMV9WNA)

只考虑局部的话，满足条件，但整体来看并不满足搜索二叉树的条件。

### 学习与小结

迭代法：在中序遍历下，符合要求的二叉搜索树是一个递增序列，所以根据这一特点，中序遍历这棵树，然后检查序列是否递增即可。

递归法：

1. 参数及返回值：参数就是传入当前节点，返回值是是否是合法的二叉搜索树；
2. 终止条件：如果树为空，返回true；
3. 单层递归逻辑：采用中序遍历，左中右，每次访问中间节点的操作是：当前值与maxval比较，如果当前值小于maxval，说明二叉搜索树左子树有值大于中间值，返回false；如果maxval较小，则更新maxcal为当前值。

### 代码

迭代代码：

```C++
class Solution {
public:
    void inorder(TreeNode * root, vector<int> & vec) {
        if (root -> left) inorder(root -> left, vec);
        vec.push_back(root -> val);
        if (root -> right) inorder(root -> right, vec);
    }
    bool isValidBST(TreeNode* root) {
        vector<int> vec;
        inorder(root, vec);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }
};
```

递归代码：

```C++
class Solution {
public:
    long long maxVal = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        bool left = isValidBST(root -> left);
        if (root -> val <= maxVal) {
            return false;
        } else {
            maxVal = root -> val;
        }
        bool right = isValidBST(root -> right);
        return left && right;
    }
};
```