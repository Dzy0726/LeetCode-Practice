# 代码随想录算法训练营第四十三天| 动态规划 Part05

## 今日题目

1049.[最后一块石头的重量 II](https://leetcode.cn/problems/last-stone-weight-ii/)

494.[目标和](https://leetcode.cn/problems/target-sum/)

474.[一和零](https://leetcode.cn/problems/ones-and-zeroes/)

## LeetCode 1049.最后一块石头的重量II

### 题目

有一堆石头，用整数数组 `stones` 表示。其中 `stones[i]` 表示第 `i` 块石头的重量。

每一回合，从中选出**任意两块石头**，然后将它们一起粉碎。假设石头的重量分别为 `x` 和 `y`，且 `x <= y`。那么粉碎的可能结果如下：

- 如果 `x == y`，那么两块石头都会被完全粉碎；
- 如果 `x != y`，那么重量为 `x` 的石头将会完全粉碎，而重量为 `y` 的石头新重量为 `y-x`。

最后，**最多只会剩下一块** 石头。返回此石头 **最小的可能重量** 。如果没有石头剩下，就返回 `0`。

> 示例 1：
>
> 输入：stones = [2,7,4,1,8,1] 输出：1 解释： 组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]， 组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]， 组合 2 和 1，得到 1，所以数组转化为 [1,1,1]， 组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
>
> 示例 2：
>
> 输入：stones = [31,26,33,21,40] 输出：5

### 思路

复健第一天，思路一点子没有，看了题解疑惑了好久为什么这是背包问题……

其实和昨天的题的做法是一样的，昨天的题目416.分割等和子集是要将一个数组分成两个和相同的数组，所以dp[j]表示背包总容量是j，放进物品i后，背的最大重量为dp[j]，如果dp[target]=target了，就说明可以分成两个和相同的数组（target = sum/2）。

上题其实是这道题的最优情况，分成了两个数组，两数组的和相同，那么碰石头最终结果是0，为最优情况。

所以以此可以想到依旧分成两个数组，让他们的差值最小（当然，最好就是0）。

按着这个思路，其他的想法就和之前那到题目一模一样了。

动归五部曲：

1. 确定dp数组以及下标的含义
   1.  dp数组的下标j就是说当前背包的容量为j，我们需要做的就是让dp[target] 尽可能的等于target (即sum/2)，这样的话，差值就是sum - dp[target] - dp[target]。
   2.  分成两个子数组，让一个子数组的和尽量接近总和的一半，那另一个也就最大限度地接近总和的一半，那么差值就最小了。
2. 确定递推公式
   1.  和上题相同，dp[j] = max(dp[j], dp[j - nums[i]] + nums[i])
3. dp数组如何初始化
   1.  全部初始化为0，大小为1501，因为stone个数最大是30个，最重的stone是100，所以最大的总重sum是3000，j是背包能容纳的重量，最大应该是sum/2，所以设置dp的大小为1501
4. 确定遍历顺序
   1.  如果使用一维dp数组，物品遍历的for循环放在外层，遍历背包的for循环放在内层，且内层for循环倒序遍历
5. 举例推导dp数组
   1.  举例，输入：[2,4,1,1]，此时target = (2 + 4 + 1 + 1)/2 = 4 ，dp数组状态图如下：
   2. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDBiYjQyOTVmYWZiNzMyYTIyMGIwYmI1YmY5NWM0NWZfZnM4TTE2ZDExNmVjbU9XbDVEOTRVbGZxQ3Y0aWNLQjVfVG9rZW46WEc4cGI1Q1Rkb09jNWF4VTJwNmNnTXRybmhnXzE3MDk3NDcwMTk6MTcwOTc1MDYxOV9WNA)
   3.  最后dp[target]里是容量为target的背包所能背的最大重量。
   4.  那么分成两堆石头，一堆石头的总重量是dp[target]，另一堆就是sum - dp[target]。
   5.  在计算target的时候，target = sum / 2 因为是向下取整，所以sum - dp[target] 一定是大于等于dp[target]的。
   6.  那么相撞之后剩下的最小石头重量就是 (sum - dp[target]) - dp[target]。

### 代码

```C++
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for (int i = 0; i < stones.size(); i++) {
            sum += stones[i];
        }
        vector<int> dp(1501, 0);
        int target = sum / 2;
        for (int i = 0; i < stones.size(); i++) {
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }
};
```

### 时空复杂度

- 时间复杂度：O(m × n) , m是石头总重量（准确的说是总重量的一半），n为石头块数
- 空间复杂度：O(m)

### 学习与小结

还是想不到怎么把问题转化成已经做过的题……

## LeetCode 494.目标和

### 题目

给你一个非负整数数组 `nums` 和一个整数 `target` 。

向数组中的每个整数前添加 `'+'` 或 `'-'` ，然后串联起所有整数，可以构造一个 **表达式** ：

- 例如，`nums = [2, 1]` ，可以在 `2` 之前添加 `'+'` ，在 `1` 之前添加 `'-'` ，然后串联起来得到表达式 `"+2-1"` 。

返回可以通过上述方法构造的、运算结果等于 `target` 的不同 **表达式** 的数目。

> 示例 1：
>
> 输入：nums = [1,1,1,1,1], target = 3 输出：5 解释：一共有 5 种方法让最终目标和为 3 。 -1 + 1 + 1 + 1 + 1 = 3 +1 - 1 + 1 + 1 + 1 = 3 +1 + 1 - 1 + 1 + 1 = 3 +1 + 1 + 1 - 1 + 1 = 3 +1 + 1 + 1 + 1 - 1 = 3
>
> 示例 2：
>
> 输入：nums = [1], target = 1 输出：1

### 思路

大体的思路是正确的，先想到了计算一个新的“target”，像之前两道题一样，分成两个子数组，一个给+，一个给-，这样的话子数组和的绝对值差就是target。但是口算搞错了公式，正确应该是 正 - abs(负)=target，abs(负) = sum - 正。所以正=(sum+target)/2。

这里的正就是要找一个子数组和=正。又归类成了前两题的类似问题。但是dp数组的含义发生了变化，dp[j]意思是：有几种取数方式可以使得和为j。

1. 确定dp数组以及下标的含义

dp[j] 表示：填满j（包括j）这么大容积的包，有dp[j]种方法

1. 确定递推公式

例如：dp[j]，j 为5，

- 已经有一个1（nums[i]） 的话，有 dp[4]种方法 凑成 容量为5的背包。
- 已经有一个2（nums[i]） 的话，有 dp[3]种方法 凑成 容量为5的背包。
- 已经有一个3（nums[i]） 的话，有 dp[2]中方法 凑成 容量为5的背包
- 已经有一个4（nums[i]） 的话，有 dp[1]中方法 凑成 容量为5的背包
- 已经有一个5 （nums[i]）的话，有 dp[0]中方法 凑成 容量为5的背包

那么凑整dp[5]有多少方法呢，也就是把 所有的 dp[j - nums[i]] 累加起来。

所以求组合类问题的公式，都是类似

1. dp数组如何初始化

从递推公式可以看出，在初始化的时候dp[0] 一定要初始化为1，因为dp[0]是在公式中一切递推结果的起源，如果dp[0]是0的话，递推结果将都是0。

如果数组[0] ，target = 0，那么 bagSize = (target + sum) / 2 = 0。 dp[0]也应该是1， 也就是说给数组里的元素 0 前面无论放加法还是减法，都是 1 种方法。

所以本题我们应该初始化 dp[0] 为 1。

dp[j]其他下标对应的数值也应该初始化为0，从递推公式也可以看出，dp[j]要保证是0的初始值，才能正确的由dp[j - nums[i]]推导出来。

1. 确定遍历顺序

对于01背包问题一维dp的遍历，nums放在外循环，target在内循环，且内循环倒序。

1. 举例推导dp数组

输入：nums: [1, 1, 1, 1, 1], target: 3

bagSize = (target+ sum) / 2 = (3 + 5) / 2 = 4

dp数组状态变化如下：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGNhNGE2M2JmNTVmZmUxMGNhM2U1ZjhiOTBjOWM2ZjZfUDJ3SUNvb0pIUkVpV3VwUnNIelo4ck1CSkEwbTdhRWNfVG9rZW46SUMwMGJBSGFBb2pWb1l4S0FWQWNybFk3bkZlXzE3MDk3NDcwMTk6MTcwOTc1MDYxOV9WNA)

(sum+target)/2 看到这个应该立刻想到能不能整除，如果不能整除，但给的都是整数该怎么办？

显然是无解的，所以应该返回0；

另外，如果abs(target)大于sum，也应该无解，返回0

### 代码

```C++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (abs(target) > sum) return 0;
        if ((target + sum) % 2 == 1) return 0;
        int bagSize = (sum + target) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]] ;
            }
        }
        return dp[bagSize];
    }
};
```

### 时空复杂度

时间复杂度： 第一个循环遍历 `nums` 数组来计算总和 `sum`，其时间复杂度为 O(N)，其中 N 是数组 `nums` 的长度。第二个嵌套循环用于填充动态规划数组 `dp`。外部循环遍历 `nums` 数组，内部循环遍历从 `bagSize` 到 `nums[i]` 的所有值。因为内部循环的迭代次数依赖于 `bagSize` 的大小，它最多运行 `bagSize` 次。因此，嵌套循环的总时间复杂度为 O(N * bagSize)，其中 `bagSize` 为 `(sum + target) / 2`。

综上所述，整个函数的时间复杂度为 O(N + N * bagSize)，可以简化为 O(N * bagSize)。

空间复杂度：O(bagSize)，其中 `bagSize` 为 `(sum + target) / 2`。

### 学习与小结

思路比起前两题有进步，但是没有注意到无解的两种情况，手生急需练习。

## LeetCode 474.一和零

### 题目

给你一个二进制字符串数组 `strs` 和两个整数 `m` 和 `n` 。

请你找出并返回 `strs` 的最大子集的长度，该子集中 **最多** 有 `m` 个 `0` 和 `n` 个 `1` 。

如果 `x` 的所有元素也是 `y` 的元素，集合 `x` 是集合 `y` 的 **子集** 。

> 示例 1：
>
> 输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3 输出：4 解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。 其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。
>
> 示例 2：
>
> 输入：strs = ["10", "0", "1"], m = 1, n = 1 输出：2 解释：最大的子集是 {"0", "1"} ，所以答案是 2 。

### 思路

最开始的想法是：dp[i][j] = k : i指string[0:i];j指子串长度;k是pair，存有几个0和1;

但是不好控制最大长度和现在有几个0和1的关系。

而且对于背包问题只知道0,1背包，不知道其他类型。还是没有将问题转化成01背包问题。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MTY5MmY1MzA5MTE5YmQwYTA5Nzc5Mjg1ZWE4NmI1ZGRfYkN4THFwTVVNc2s0eDVvTGxlQVJpTHlKZFo3RGcxcWhfVG9rZW46VHFScWI4WlZKb3JDZ1N4Zng4NWN3OVJkbktiXzE3MDk3NDcwMTk6MTcwOTc1MDYxOV9WNA)

多重背包是每个物品，数量不同的情况。本题中strs 数组里的元素就是物品，每个物品都是一个！而m 和 n相当于是一个背包，两个维度的背包，而不同长度的字符串就是不同大小的待装物品。

动规五部曲：

1. 确定dp数组（dp table）以及下标的含义

dp[i][j]：最多有i个0和j个1的strs的最大子集的大小为dp[i][j]。

1. 递推公式

dp[i][j] 可以由前一个strs里的字符串推导出来，strs里的字符串有zeroNum个0，oneNum个1。dp[i][j] 就可以是 dp[i - zeroNum][j - oneNum] + 1。然后我们在遍历的过程中，取dp[i][j]的最大值。

所以递推公式：dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);

1. dp数组如何初始化

dp[i][j] = 0

1. 确定遍历顺序

01背包一定是外层for循环遍历物品，内层for循环遍历背包容量且从后向前遍历！

物品就是strs里的字符串，背包容量就是题目描述中的m和n。

1. 举例推导dp数组

以输入：["10","0001","111001","1","0"]，m = 3，n = 3为例

最后dp数组的状态如下所示：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NmI4NThiMjlkYjZlYWU1NmZhOWE3MjNiYzhlMjEwZmJfV1lUMmV3eVhVQTNNS21qQ3FLRXF4M1QyWjlVUklZUmhfVG9rZW46Q2p6VGJiS0o0b3NqeVh4WUxpTmNzc1pkblZjXzE3MDk3NDcwMTk6MTcwOTc1MDYxOV9WNA)

### 代码

```C++
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); 
        for (int k = 0; k < strs.size(); k++) {
            int lastZero = 0, lastOne = 0;
            for (int a = 0; a < strs[k].size(); a++) {
                if (strs[k][a] == '0') lastZero++;
                else lastOne++;
            }
            for (int i = m; i >= lastZero; i--) {
                for (int j = n; j >= lastOne; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - lastZero][j - lastOne] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
```

### 时空复杂度

时间复杂度：O((m + n + m * n) * L)，即O(m * n * L)，其中 L 是字符串数组 `strs` 的长度，m 和 n 分别是 0 和 1 的最大数量。

**空间复杂度**：O(m * n)。

### 学习与小结

0-1背包的多种应用，

- [纯 0 - 1 背包 (opens new window)](https://programmercarl.com/背包理论基础01背包-2.html)是求给定背包容量装满背包的最大价值是多少。
- [416. 分割等和子集 (opens new window)](https://programmercarl.com/0416.分割等和子集.html)是求给定背包容量，能不能装满这个背包。
- [1049. 最后一块石头的重量 II (opens new window)](https://programmercarl.com/1049.最后一块石头的重量II.html)是求给定背包容量，尽可能装，最多能装多少
- [494. 目标和 (opens new window)](https://programmercarl.com/0494.目标和.html)是求给定背包容量，装满背包有多少种方法。
- 本题是求给定背包容量，装满背包最多有多少个物品。