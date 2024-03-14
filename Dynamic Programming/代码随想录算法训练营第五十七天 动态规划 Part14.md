# 代码随想录算法训练营第五十七天| 动态规划 Part14

## 今日题目

1143.[最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)

1035.[不相交的线](https://leetcode.cn/problems/uncrossed-lines/)

53.[最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

## LeetCode 1143.最长公共子序列

### 题目

给定两个字符串 `text1` 和 `text2`，返回这两个字符串的最长 **公共子序列** 的长度。如果不存在 **公共子序列** ，返回 `0` 。

一个字符串的 **子序列** 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

- 例如，`"ace"` 是 `"abcde"` 的子序列，但 `"aec"` 不是 `"abcde"` 的子序列。

两个字符串的 **公共子序列** 是这两个字符串所共同拥有的子序列。

> 示例 1：
>
> 输入：text1 = "abcde", text2 = "ace"  输出：3   解释：最长公共子序列是 "ace" ，它的长度为 3 。
>
> 示例 2：
>
> 输入：text1 = "abc", text2 = "abc" 输出：3 解释：最长公共子序列是 "abc" ，它的长度为 3 。
>
> 示例 3：
>
> 输入：text1 = "abc", text2 = "def" 输出：0 解释：两个字符串没有公共子序列，返回 0 。

### 思路

与最长重复子数组不同的点在于最长重复子数组必须是连续的，而这道题的最长公共子序列可以不连续，只要不改变顺序就可以。

所以可以按照前一题，dp[i][j] = k表示text1[0:i-1]和text2[0:j-1]最长公共子序列的长度是k，那么如何确定状态转移公式呢？

如果text[i-1]==text[j-1]，很好想明白，就是在dp[i-1][j-1]的基础上加1，那如果不相等呢？

在最长重复子数组中，因为要求连续，一旦出现不相等，说明无法连续，直接让dp为0；而在本题中不要求连续，所以即使不相等，也应该取目前的最大值。这个目前的最大值就是dp[i-1][j]和dp[i][j-1]的最大值。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODFiZGUwMDQ0Njc3Nzc5Mjk3MWU2YWE4ZjUxZDM0MTdfdGJ5dTJMMHFMODFBWEtKSlF1UXZvcjVteHBHRTFoM2RfVG9rZW46TnpWeWJPUUhrb0tNNWl4UmJ0RWNZamJVbnFlXzE3MTAzOTc0NjQ6MTcxMDQwMTA2NF9WNA)

从上图可以看出，如果末尾两个正好相等了，去掉他俩就是左上角这格，所以用dp[i-1][j-1]+1；如果不相等，那么要让公共子序列最长，就必须取上边和左边的最大值。比如ac和abcd遍历到末尾时，c和d不相等，那就要取{a,abcd}和{ac,abc}的最大值。

举例推导dp数组

以输入：text1 = "abcde", text2 = "ace" 为例，dp状态如图：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MGQxNTg5NTE1NTFjMzU4ZTE5NjEwYjIwNGMxMjU2ZTBfcENhZ3JQZFhyOWJlQnF3MkxiY2JzRlR4N2JXdW9SbkhfVG9rZW46QUJHRWJsQlc0b3l0NHB4U1JldmNFZlJsbktiXzE3MTAzOTc0NjQ6MTcxMDQwMTA2NF9WNA)

### 代码

```C++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        for (int i = 1; i < text1.size() + 1; i++) {
            for (int j = 1; j < text2.size() + 1; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n * m).

空间复杂度：空间复杂度为O(n * m).

### 学习与小结

如果末尾两个正好相等了，去掉他俩就是左上角这格，所以用dp[i-1][j-1]+1；如果不相等，那么要让公共子序列最长，就必须取上边和左边的最大值。比如ac和abcd遍历到末尾时，c和d不相等，那就要取{a,abcd}和{ac,abc}的最大值。

如果末尾不相等，说明末尾这两个元素同时存在与否不影响dp的值，所以要取他俩有一个不在时的最大值。

这里后续可以再理解一下。

## LeetCode 1035.不相交的线

### 题目

在两条独立的水平线上按给定的顺序写下 `nums1` 和 `nums2` 中的整数。

现在，可以绘制一些连接两个数字 `nums1[i]` 和 `nums2[j]` 的直线，这些直线需要同时满足满足：

-  `nums1[i] == nums2[j]`
- 且绘制的直线不与任何其他连线（非水平线）相交。

请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

以这种方法绘制线条，并返回可以绘制的最大连线数。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGQ1NjlmMzlkZTdmNjQyZWU4NTU2MGVlOGYyZmQ3MTBfMWhQQmUxTFJRNkY1UEVSSWYxNkZKVjR1TUlUZHlWQU1fVG9rZW46WW1JUmJpcks1b29SOVd4MHNNWWNhM2xBbkFJXzE3MTAzOTc0NjU6MTcxMDQwMTA2NV9WNA)
>
> 输入：nums1 = [1,4,2], nums2 = [1,2,4]
>
> 输出：2
>
> 解释：可以画出两条不交叉的线，如上图所示。  但无法画出第三条不相交的直线，因为从 nums1[1]=4 到 nums2[2]=4 的直线将与从 nums1[2]=2 到 nums2[1]=2 的直线相交。
>
> 示例 2：
>
> 输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
>
> 输出：3
>
> 示例 3：
>
> 输入：nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
>
> 输出：2

### 思路

这道题思路与上一题完全相同，甚至因为“连线”而更加直观。

本题说是求绘制的最大连线数，其实就是求两个字符串的最长公共子序列的长度。

尤其是在当前末尾两个值不相等时，不能连线。dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MjViMmFhMjM4NjhjYjgwOWIwMzQxMzUwMjM4ODFlMzhfOUNlNnFoUFM4OXRtM0VUU1hMS1p2YXZFeGlFTXNkU3dfVG9rZW46VG1tNWJHYlphbzVNSjN4UllqN2Nwczl4bk9oXzE3MTAzOTc0NjU6MTcxMDQwMTA2NV9WNA)

如上图，当末尾是2和3时，2和3不相等不能连线，所以看新来的2或3（对于第四张图来说，2和3都是新增的元素），看2或3能否和之前的末尾有连线，也就是上一个状态（上边和左边），取两者的最大值作为当前的dp值。

### 代码

```C++
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        for (int i = 1; i < nums1.size() + 1; i++) {
            for (int j = 1; j < nums2.size() + 1; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i -1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[nums1.size()][nums2.size()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n * m).

空间复杂度：空间复杂度为O(n * m).

## LeetCode 53.最大子数组和

### 题目

给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**子数组**是数组中的一个连续部分。

> 示例 1：
>
> 输入：nums = [-2,1,-3,4,-1,2,1,-5,4] 输出：6 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
>
> 示例 2：
>
> 输入：nums = [1] 输出：1
>
> 示例 3：
>
> 输入：nums = [5,4,-1,7,8] 输出：23

### 思路

动态规划的思路比较直观的想到，要连续所以只能比较从i开始连续还是接着之前的连续。

dp[i] = k表示到i时，最大连续子数组和为k，来源要么是接着之前连续的子数组继续连续，那么和为dp[i-1]+nums[i]；要么就是从自己这里新建连续，前面断开，dp[i]

所以dp[i] = max(dp[i], dp[i - 1] + nums[i]);

初始化就直接将nums赋值给dp，每个dp初始都可以看成只有自己是连续子数组。

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]，对应的dp状态如下： 

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=N2IwMDg2ZjhkN2ZhMzM0NmVmMDNiMmU5Yjg3NzZlOWZfYVJwVGIyRGhvVkhjMUNXVXFZWFlaVjMwandxaVhqVlZfVG9rZW46V0lJcGJPclA0b1hnZjZ4VFByeWNJWVVxbnRnXzE3MTAzOTc0NjU6MTcxMDQwMTA2NV9WNA)

### 代码

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp = nums;
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i], dp[i - 1] + nums[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).