# 代码随想录算法训练营第五十天| 动态规划 Part07

## 今日题目

70.[爬楼梯](https://leetcode.cn/problems/climbing-stairs/)

322.[零钱兑换](https://leetcode.cn/problems/coin-change/)

279.[完全平方数](https://leetcode.cn/problems/perfect-squares/)

## LeetCode 70.爬楼梯（进阶）

### 题目

假设你正在爬楼梯。需要 `n` 阶你才能到达楼顶。

每次你可以爬 `1` 或 `2` 个台阶。你有多少种不同的方法可以爬到楼顶呢？

> 示例 1：
>
> 1. 输入：n = 2 输出：2 解释：有两种方法可以爬到楼顶。 1 阶 + 1 阶 2 阶
>
> 示例 2：
>
> 1. 输入：n = 3 输出：3 解释：有三种方法可以爬到楼顶。 1 阶 + 1 阶 + 1 阶 1 阶 + 2 阶 2 阶 + 1 阶

### 思路

进阶版是要把问题看做是一个完全背包问题来解决，可以无限取背包内的1和2，使其总和为n，求排列数k。

dp[j] += dp[j - nums[i]]

### 代码

```C++
class Solution {
public:
    int climbStairs(int n) {
        vector<int> nums = {1, 2};
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int j = 1; j < n + 1; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j >= nums[i]) dp[j] += dp[j - nums[i]];
            }
        }
        return dp[n];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

这道题可以从简单的斐波那契数列扩展到每次可以爬1-m个楼梯，就变成了完全背包问题。要求有几种爬法，就是求排列数。背包容量是外层循环，背包内的物品是内层循环，在本题中容量就是要爬的楼梯总数n，背包内的物品就是每次可以爬的楼梯数1-m。

## LeetCode 322.零钱兑换

### 题目

给你一个整数数组 `coins` ，表示不同面额的硬币；以及一个整数 `amount` ，表示总金额。

计算并返回可以凑成总金额所需的 **最少的****硬币****个数** 。如果没有任何一种硬币组合能组成总金额，返回 `-1` 。

你可以认为每种硬币的数量是无限的。

> 示例 1：
>
> 输入：coins = [1, 2, 5], amount = 11
>
> 输出：3  解释：11 = 5 + 5 + 1
>
> 示例 2：
>
> 输入：coins = [2], amount = 3
>
> 输出：-1
>
> 示例 3：
>
> 输入：coins = [1], amount = 0 输出：0

### 思路

这道题做的还是比较快的，因为每种硬币的数量是无限的，所以可以考虑是完全背包问题。

i，dp[j] = k的含义是使用0-i这几种硬币构成金额j最少要k个硬币。

因为要求最少的硬币，是求最少的组合，那么钱币有顺序和没有顺序都可以，都不影响钱币的最小个数。所以本题并不强调集合是组合还是排列。

递推公式为：dp[j]= min(dp[j], dp[j- coins[i]] + 1)，前者表示不用当前i这个硬币最少是几种，后者表示使用i这个硬币最少是几种，取二者最小值；

所以初始化需要将整个数组初始化为INT32_MAX，并且将dp[0]初始化为0.

### 代码

```C++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<unsigned int> dp(amount + 1, INT32_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return dp[amount] == INT32_MAX ? -1 : dp[amount];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n*amount).

空间复杂度：空间复杂度为O(amount).

### 学习与小结

**本题是要求最少****硬币****数量，硬币是组合数还是排列数都无所谓！所以两个****for循环****先后顺序怎样都可以！**

## LeetCode 322.完全平方数

### 题目

给你一个整数 `n` ，返回 *和为* *`n`* *的完全平方数的最少数量* 。

**完全平方数** 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，`1`、`4`、`9` 和 `16` 都是完全平方数，而 `3` 和 `11` 不是。

> 示例 1：
>
> 输入：n = 12
>
> 输出：3
>
> 解释：12 = 4 + 4 + 4
>
> 示例 2：
>
> 输入：n = 13
>
> 输出：2
>
> 解释：13 = 4 + 9

### 思路

思路和上题相同，这里的nums数组是由完全平方数组成的。

完全平方数就是物品（可以无限件使用），凑个正整数n就是背包，问凑满这个背包最少有多少物品？

### 代码

```C++
class Solution {
public:
    int numSquares(int n) {
        vector<int> nums(sqrt(n));
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = (i + 1) * (i + 1);
        }
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = nums[i]; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - nums[i]] + 1);
            }
        }
        return dp[n];
    }
};
```

### 时空复杂度

时间复杂度：O(n * √n)

空间复杂度: O(n)