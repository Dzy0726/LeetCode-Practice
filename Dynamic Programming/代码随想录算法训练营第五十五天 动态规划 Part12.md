# 代码随想录算法训练营第五十五天| 动态规划 Part12

## 今日题目

309.[买卖股票的最佳时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

714.[买卖股票的最佳时机含手续费](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

## LeetCode 309.最佳买卖股票时机含冷冻期

### 题目

给定一个整数数组`prices`，其中第  `prices[i]` 表示第 *`i`* 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

- 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

**注意：**你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

> 示例 1:
>
> 输入: prices = [1,2,3,0,2] 输出: 3  解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
>
> 示例 2:
>
> 输入: prices = [1] 输出: 0

### 思路

动态规划的核心就是找到状态和转移。

如何找到这个冷冻状态呢？没有想出来

用0-3表示4个状态：

0：持有股票

1：不持有股票，不是今天卖出（超过两天不持有股票）

2：不持有股票，是今天卖出

3：冷冻期（前天不持有股票，昨天卖出）

倒过来想一想怎么形成的四个状态，最开始的股票问题是两个状态，持有和不持有股票，加上冷冻期后，起码应该是三个状态，但是冷冻期的转移只能是前一天卖出股票，今天才会转移到冷冻状态，由此，对不持有股票做出细分，分为是不是今天卖的，从而方便到冷冻期的转移。

那么每个状态具体该如何转移？

0：持有股票，可能是今天买入的，也可能是之前买入的；今天买入的分为昨天是1状态还是3状态。所以dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i], dp[i-1][3] - prices[i])

1：超过两天不持有股票，不是今天卖出，那只能是之前就不持有股票。之前不持有股票又能分为，超过两天不持有股票和曾经持有但是昨天卖出进入冷冻期：dp[i][1] = max(dp[i-1][1], dp[i-1][3]

2：不持有股票今天卖出，那么昨天一定持有股票，不可能是状态1和3，所以dp[i][2] = dp[i-1][0] + prices[i] 3：冷冻期，能进入冷冻期只有一种方法：前天有股票，昨天卖了股票，今天冷冻，所以dp[i][3] = dp[i-1][2]

如何初始化？

这里主要讨论一下第0天如何初始化。

如果是持有股票状态（状态一）那么：dp[0][0] = -prices[0]，一定是当天买入股票。

保持卖出股票状态（状态二），这里其实从 「状态二」的定义来说 ，很难明确应该初始多少，这种情况我们就看递推公式需要我们给他初始成什么数值。

如果i为1，第1天买入股票，那么递归公式中需要计算 dp[i - 1][1] - prices[i] ，即 dp[0][1] - prices[1]，那么大家感受一下 dp[0][1] （即第0天的状态二）应该初始成多少，只能初始为0。想一想如果初始为其他数值，是我们第1天买入股票后 手里还剩的现金数量是不是就不对了。

今天卖出了股票（状态三），同上分析，dp[0][2]初始化为0，dp[0][3]也初始为0。

### 代码

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(4));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = 0;
        dp[0][3] = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1] - prices[i], dp[i - 1][3] - prices[i]));
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][0] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }
        return max(dp[prices.size() - 1][1], max(dp[prices.size() - 1][2], dp[prices.size() - 1][3]));
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(4n).

### 学习与小结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTJlYTE3NTZhMzkyODg2NWQzODdiOTFiYWI2MDVmYzlfOFNzeWh6TE1kNEI5UW5qNnZhNFU0c2NoMFdTQmkwRXpfVG9rZW46QUU2ZGJ6dEFQb0dSSTN4WVkwY2Nlc3NNbmllXzE3MTAzMzExNjU6MTcxMDMzNDc2NV9WNA)

状态不可能一下子完全找对，可以试着慢慢找，从多到少尽量合并，形成自己的思路和解法。

## LeetCode 714.买卖股票的最佳时机含手续费

### 题目

给定一个整数数组 `prices`，其中 `prices[i]`表示第 `i` 天的股票价格 ；整数 `fee` 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

**注意：**这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

> 示例 1：
>
> 输入：prices = [1, 3, 2, 8, 4, 9], fee = 2 输出：8 解释：能够达到的最大利润:   在此处买入 prices[0] = 1 在此处卖出 prices[3] = 8 在此处买入 prices[4] = 4 在此处卖出 prices[5] = 9 总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
>
> 示例 2：
>
> 输入：prices = [1,3,7,5,10,3], fee = 3 输出：6

### 思路

和买卖股票的最佳时机2思路相同，在处理卖出股票是要扣去手续费。

### 代码

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(prices.size(), vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }
        return dp[prices.size() - 1][1];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(2n).

### 学习与小结

买卖股票告一段落了，又一次强化了状态与转移的重要性。先搞清楚有哪几个状态，状态之间如何转移，状态能不能合并。