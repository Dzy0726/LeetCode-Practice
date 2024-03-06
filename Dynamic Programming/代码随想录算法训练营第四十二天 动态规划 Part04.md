# 代码随想录算法训练营第四十二天| 动态规划 Part04

## 今日题目

416.[分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)

## LeetCode 416.分割等和子集

### 题目

给你一个 **只包含正整数** 的 **非空** 数组 `nums` 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

> 示例 1：
>
> 输入：nums = [1,5,11,5] 输出：true 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
>
> 示例 2：
>
> 输入：nums = [1,2,3,5] 输出：false 解释：数组不能分割成两个元素和相等的子集。

### 思路

一开始想到了求和看是否是偶数，如果不是偶数就不能分割，但是后面对于如何把这道题和背包问题结合起来无从下手，所以没有做出来。

要找是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。那么只要找到集合里能够出现 sum / 2 的子集总和，就算是可以分割成两个相同元素和子集了。所以只需要考虑一个子集就行。

那么怎么考虑这个子集呢？

每个元素只能使用一次，所以应该是01背包问题：

- 背包的体积为sum / 2
- 背包要放入的商品（集合里的元素）重量为元素的数值，价值也为元素的数值
- 背包如果正好装满，说明找到了总和为 sum / 2 的子集。
- 背包中每一个元素是不可重复放入。

动归五部曲：

1. 确定dp数组以及下标的含义

01背包中，dp[j] 表示：容量为j的背包，所背的物品价值最大可以为dp[j]。

本题中每一个元素的数值既是重量，也是价值。套到本题，dp[j]表示 背包总容量（所能装的总重量）是j，放进物品后，背的最大重量为dp[j]。

那么如果背包容量为target， dp[target]就是装满 背包之后的重量，所以当 dp[target] == target 的时候，背包就装满了。

装不满的情况：数组 [1, 5, 11, 5]，dp[7] 只能等于 6，因为只能放进 1 和 5。

而dp[6]就可以等于6了，放进1和5，那么dp[6] == 6，说明背包装满了。

1. 确定递推公式

01背包的递推公式为：dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);

本题，相当于背包里放入数值，那么物品i的重量是nums[i]，其价值也是nums[i]。

所以递推公式：dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);

1. dp数组如何初始化

从dp[j]的定义来看，首先dp[0]一定是0。如果题目给的价值都是正整数那么非0下标都初始化为0就可以了，如果题目给的价值有负数，那么非0下标就要初始化为负无穷，这样才能让dp数组在递推的过程中取得最大的价值，而不是被初始值覆盖了。

本题题目中只包含正整数的非空数组，所以非0下标的元素初始化为0就可以了。

1. 确定遍历顺序

如果使用一维dp数组，物品遍历的for循环放在外层，遍历背包的for循环放在内层，且内层for循环倒序遍历。

1. 举例推导dp数组

dp[j]的数值一定是小于等于j的，如果dp[j] == j 说明，**集合中的子集总和正好可以凑成总和j**。

用例1，输入[1,5,11,5] 为例，如图：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjVlYzRiOTQ5OWEwOGEzMjdkZDI0YjZhYTk4ZjhlMGZfOXFRNlpXTmo1NFZGR2Nzblp0emhacnU1YmMycDZXbjhfVG9rZW46SjM2emJDdHZZb09Gc1N4amRtVWNMcXNBbkllXzE3MDk3MDcxODE6MTcwOTcxMDc4MV9WNA)

最后dp[11] == 11，说明可以将这个数组分割成两个子集，使得两个子集的元素和相等。

### 代码

```C++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 2 == 1) return false;
        // max sum == 20000, max sum/2 = 10000
        // init dp to 0
        vector<int> dp(10001, 0);
        int target = sum / 2;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        if (dp[target] == target) {
            return true;
        } else {
            return false;
        }
    }
};
```

### 时空复杂度

时间复杂度：

1. 第一个for循环遍历`nums`数组，时间复杂度为O(n)，其中n是`nums`数组的长度。
2. 第二个for循环是一个嵌套循环，外循环同样遍历`nums`数组，时间复杂度为O(n)。
3. 内循环从`target`递减到`nums[i]`，最坏的情况下（`nums[i]`最小为1），时间复杂度为O(target)。
4. 因此，嵌套循环的总时间复杂度为O(n*target)。

空间复杂度：额外创建了一个大小为`target + 1`的`dp`数组用于存储中间结果，因此空间复杂度为O(target)。

### 学习与小结

如何将实际应用套入到已有模型（比如01背包问题）很重要。