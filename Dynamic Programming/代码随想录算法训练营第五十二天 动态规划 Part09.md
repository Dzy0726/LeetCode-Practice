# 代码随想录算法训练营第五十二天| 动态规划 Part09

## 今日题目

198.[打家劫舍](https://leetcode.cn/problems/house-robber/)

213.[打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)

337.[打家劫舍 III](https://leetcode.cn/problems/house-robber-iii/)

## LeetCode 198.打家劫舍

### 题目

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **不触动警报装置的情况下** ，一夜之内能够偷窃到的最高金额。

> 示例 1：
>
> 输入：[1,2,3,1] 输出：4 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。     偷窃到的最高金额 = 1 + 3 = 4 。
>
> 示例 2：
>
> 输入：[2,7,9,3,1] 输出：12 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。     偷窃到的最高金额 = 2 + 9 + 1 = 12 

### 思路

1. 确定dp数组（dp table）以及下标的含义

dp[i]：考虑下标i（包括i）以内的房屋，最多可以偷窃的金额为dp[i]。

1. 确定递推公式

决定dp[i]的因素就是第i房间偷还是不偷。

如果偷第i房间，那么dp[i] = dp[i - 2] + nums[i] ，即：第i-1房一定是不考虑的，找出 下标i-2（包括i-2）以内的房屋，最多可以偷窃的金额为dp[i-2] 加上第i房间偷到的钱。

如果不偷第i房间，那么dp[i] = dp[i - 1]，即考虑i-1房（注意这里是考虑，并不是一定要偷i-1房，这是很多同学容易混淆的点）

然后dp[i]取最大值，即dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);

1. dp数组如何初始化

从递推公式dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);可以看出，递推公式的基础就是dp[0] 和 dp[1]

从dp[i]的定义上来讲，dp[0] 一定是 nums[0]，dp[1]就是nums[0]和nums[1]的最大值即：dp[1] = max(nums[0], nums[1]);

1. 确定遍历顺序

dp[i] 是根据dp[i - 2] 和 dp[i - 1] 推导出来的，那么一定是从前到后遍历！

1. 举例推导dp数组

以示例二，输入[2,7,9,3,1]为例。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NWIyYjA0MzI5ZTU0ZjJmZGM2MTg1MTE3YzNkYTU3NDZfWkc4dzhvQjdwcjRpemszdHA5aWJnVEdMRGIxSEthWk9fVG9rZW46UVA1RWJWM1Zxb0NzZVV4RlptSGM3ZjdpbmRiXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)

### 代码

```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums[0];
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[nums.size() - 1];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

EZPZ~

## LeetCode 213.打家劫舍II

### 题目

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警** 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **在不触动警报装置的情况下** ，今晚能够偷窃到的最高金额。

> 示例 1：
>
> 输入：nums = [2,3,2] 输出：3 解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
>
> 示例 2：
>
> 输入：nums = [1,2,3,1] 输出：4 解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。     偷窃到的最高金额 = 1 + 3 = 4 。

### 思路

与上题相比多了一个限制条件，那就是不能同时取nums数组的第一个和最后一个。

考虑到“之前的状态”，我一直在想怎么处理最后一个dp的最大值，于是根据未通过的测试用例，陷入到了奇偶的泥潭……大的思考方向出错了……

对于一个数组，成环的话主要有如下三种情况：

- 情况一：考虑不包含首尾元素

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=M2RkOWM3Y2FhM2ZmMTU0YmVmZjFmZDFkNDZiMWFmMjRfUGgxcTJtS0VzeDU5V1ZZVjFKQkt6NkkzaWhHTkhQRVBfVG9rZW46S1FXbmJrOEZOb0tHQWF4WlpmM2NrTEJmbmxXXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)

- 情况二：考虑包含首元素，不包含尾元素

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTFmZjJkZjFhZmYzMjA3ODRiZjUwMzAzMTY2MTNlMTRfR01NRkhiWU4yTWNVZU52ak05aFAwM2ZrWWt6ajJyYUxfVG9rZW46Wmx3MGJzazRyb3EyQzN4WmMwbWNSYlAybnVkXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)

- 情况三：考虑包含尾元素，不包含首元素

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZWIzZjExNTFhNDA0MjQ5YmU3NGE4MGM4NjNmNjcyMTBfY0tXbWVnUGRUTmdpTEpNRXlIVGJ4eEt1WVU1UVdtRnVfVG9rZW46QnFGN2IzRlU4b3R1YmR4UldFa2M1VTRVbjRMXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)

注意是"考虑"，例如情况三，虽然是考虑包含尾元素，但不一定要选尾部元素！ 对于情况三，取nums[1] 和 nums[3]就是最大的。

而情况二和情况三都包含了情况一了，所以只考虑情况二和情况三就可以了。

### 代码

```C++
class Solution {
public:
    int robRange(vector<int>& nums, int start, int end) {
        if (end == start) return nums[start];
        vector<int> dp(nums.size());
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int res1 = robRange(nums, 0, nums.size() - 2);
        int res2 = robRange(nums, 1, nums.size() - 1);
        return max(res1, res2);
    }

};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

纠结于最后一个dp值怎么处理，没有想到分成两段打家劫舍1，然后取最大值，这个思路也得记一下。

## LeetCode 

### 题目

小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 `root` 。

除了 `root` 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 **两个直接相连的房子在同一天晚上被打劫** ，房屋将自动报警。

给定二叉树的 `root` 。返回 ***在不触动警报的情况下*** *，小偷能够盗取的最高金额* 。

> 示例 1:
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MThmNGVjZjkxNDVlZDczODY5ZmUxYTIzMzM5NmYwNTJfMmZBWVVzODJqQUtRTGJwMmhtMHN3MVRHOWZ0QUtXU0tfVG9rZW46SXFnMWJrTXlib0pSbFN4VEI0ZWNBSXFQbkZlXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)
>
> 输入: root = [3,2,3,null,3,null,1] 输出: 7  解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7
>
> 示例 2:
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NmQ4NGZhYzE0Y2MxMDJlNzAxNjVkYzA3MmMwYjY3MjlfSUIzVjFsS0Z5WmRtOGtGYnNZVTlGcURYZWRZUGh6Qk9fVG9rZW46TzJJRWJDTEdVb1lwNVh4TDVoMmN0RUU5bmJlXzE3MDk5Njc3NDQ6MTcwOTk3MTM0NF9WNA)
>
> 输入: root = [3,4,5,1,3,null,1] 输出: 9 解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9

### 思路

树形结构就得考虑遍历的顺序，是dfs的前中后序还是bfs层序遍历。

一开始想法是dp[i] = k表示偷到第i层最多可以偷k，然后转化成打家劫舍1的问题，间隔层数的偷，用层序遍历算每层的和，但是显然不正确，忽略了能同时偷同一层的左节点和下一层右边的两个节点的情况。

所以应该用dfs，但是用哪个顺序呢？

中序遍历首先被排除，前序遍历遍历到最底层有一堆节点，不好处理，看起来后序遍历从下往上最后返回到根节点是最好的解法。

使用后续遍历从下往上回溯，dp数组的含义是dp[0]表示不偷当前这个节点最多能偷多少，dp[1]表示偷这个节点最多返回多少，dp的大小就是2.

那这样的话状态转移公式就是 dp[1] = node -> val + 左孩子dp[0]+右孩子dp[0]，dp[0]表示不偷这个节点最多能偷多少

dp[0] = 左孩子max(dp[0],dp[1]) + 右孩子max(dp[0],dp[1])。这里一定要注意！不偷当前节点不等于说左右孩子必须偷，可以左右孩子都不偷，或者都偷，或者只偷左，或者只偷右！至于到底偷不偷一定是选一个最大的。

### 代码

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> dp(2);
        dp = robTree(root);
        return max(dp[0], dp[1]);
    }
    vector<int> robTree(TreeNode* root) {
        if (root == NULL) return {0, 0};
        vector<int> left = robTree(root -> left);
        vector<int> right = robTree(root -> right);
        int result1 = root -> val + left[0] + right[0]; 
        int result2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {result2, result1};
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).每个节点只遍历了一次

空间复杂度：O(log n)，算上递推系统栈的空间

### 学习与小结

这道题是树形DP的入门题目，所谓树形DP就是在树上进行递归公式的推导。

第一道常规dp题目；第二道要能想的清楚分成两部分0到n-1和1到n，这样能巧妙的避开0和n两个的相遇；第三道树形dp，先要想明白用哪个遍历是最省事的，然后要注意的就是不偷当前节点不意味着他的孩子必须偷，还是要选最大的情况！