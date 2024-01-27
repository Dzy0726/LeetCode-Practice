# 代码随想录算法训练营第三十二天| 贪心算法 Part02

## 今日题目

122.[买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)

55.[跳跃游戏](https://leetcode.cn/problems/jump-game/)

45.[跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/)

## LeetCode 122.买卖股票的最佳时机 II

### 题目

给你一个整数数组 `prices` ，其中 `prices[i]` 表示某支股票第 `i` 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 **最多** 只能持有 **一股** 股票。你也可以先购买，然后在 **同一天** 出售。

返回 *你能获得的* ***最大*** *利润* 。

> 示例 1：
>
> 输入：prices = [7,1,5,3,6,4] 输出：7 解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。     总利润为 4 + 3 = 7 。
>
> 示例 2：
>
> 输入：prices = [1,2,3,4,5] 输出：4 解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。     总利润为 4 。
>
> 示例 3：
>
> 输入：prices = [7,6,4,3,1] 输出：0 解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。

### 思路

示例一发现只要第二天比第一天高就可以卖出，然后将和累加起来；示例二虽然说第一天买入，第五天卖出有最大利润，但是发现前一天买第二天卖依旧可以取得最大利润；于是就写了个只要今天比昨天高，就买了卖，没想到竟然通过了……

看评论区大家的讨论，本题的股票允许当天卖出再买入，所以示例二中，第一天卖第五天卖和每天买隔天卖，再买再卖是一样的，每天局限于眼前先拿到利润，因为能看到后一天（或者说是能看到前一天的价，就像拥有回到昨天的超能力）这样买股票是稳赚不赔的。

### 代码

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        int count = 0;
        for (int i = 1; i < prices.size(); i++) {
            count = prices[i] - prices[i - 1];
            if (count > 0) {
                result += count;
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(1).

### 学习与小结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzI4ZTI5MTc5N2E3OWQ3NzI1NzZkY2RkZWJjZDlhODVfdmRXaTZRNWZ3TUVndk9peEx2ZDdodGdZR3pZRERtaGlfVG9rZW46UFFpSWJoamJob01Gckh4SXQySmNja2NvbmFnXzE3MDYzNDM0OTI6MTcwNjM0NzA5Ml9WNA)

从图中可以发现，其实我们需要收集每天的正利润就可以，收集正利润的区间，就是股票买卖的区间，而我们只需要关注最终利润，不需要记录区间。

那么只收集正利润就是贪心所贪的地方！

局部最优：收集每天的正利润，全局最优：求得最大利润。

## LeetCode 55.跳跃游戏

### 题目

给你一个非负整数数组 `nums` ，你最初位于数组的 **第一个下标** 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 `true` ；否则，返回 `false` 。

> 示例 1：
>
> 输入：nums = [2,3,1,1,4] 输出：true 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
>
> 示例 2：
>
> 输入：nums = [3,2,1,0,4] 输出：false 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

### 思路

最开始的做法是只跳最大的step，可以通过157/172个用例；第二次用回溯法做，在75个用例时超时了……

### 学习

当前位置元素如果是 3，我究竟是跳一步呢，还是两步呢，还是三步呢，究竟跳几步才是最优呢？

其实跳几步无所谓，关键在于可跳的覆盖范围！

一语点醒梦中人！为什么要纠结于跳几步呢？不管是跳几步，当前元素是3，他最起码有一种办法可以到达下标为3的位置，0-3是他的覆盖范围。所以问题就转化为这个“覆盖范围”能不能覆盖数组的最后一个下标。加入跳一步到了4，那么覆盖范围就是1+4=5，比之前的3大，可以更新这个覆盖范围与数组长度比较。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTM3MWI4NmZmZmUwMjU0NjA5YjBjOThmZDE0MjdiNDlfem02MVAxV01RZUMwY2lkUzMwbWMxV0EwbHM5bzdYaFRfVG9rZW46RHRPNmJLVnpmbzdqUGN4cVZSRWNnbjJBbm9uXzE3MDYzNDM0OTI6MTcwNjM0NzA5Ml9WNA)

贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点。

### 代码

```C++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = nums[0];
        for (int i = 0; i <= cover; i++) {
            if (cover >= nums.size() - 1) return true;
            int newCover = i + nums[i];
            cover = cover > newCover ? cover : newCover;
        }
        return false;
    }
};
```

为什么for循环不从1开始呢？已经取了0的值？因为碰到了最后一个测试用例：nums= [0]……

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(1).

### 小结

这道题目关键点在于：不用拘泥于每次究竟跳几步，**而是看覆盖范围，覆盖范围内一定是可以跳过来的**，不用管是怎么跳的。

## LeetCode 45.跳跃游戏II

### 题目

给定一个长度为 `n` 的 **0 索引**整数数组 `nums`。初始位置为 `nums[0]`。

每个元素 `nums[i]` 表示从索引 `i` 向前跳转的最大长度。换句话说，如果你在 `nums[i]` 处，你可以跳转到任意 `nums[i + j]` 处:

- `0 <= j <= nums[i]` 
- `i + j < n`

返回到达 `nums[n - 1]` 的最小跳跃次数。生成的测试用例可以到达 `nums[n - 1]`。

> 示例 1:
>
> 输入: nums = [2,3,1,1,4] 输出: 2 解释: 跳到最后一个位置的最小跳跃数是 2。     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
>
> 示例 2:
>
> 输入: nums = [2,3,0,1,4] 输出: 2

### 思路

回溯法果然超时了……能过73/109个用例……

还是可以想出贪心解法的。顾名思义要找局部最优解，所以每到一个新的位置，就要看当前能跳的最大的范围，然后更新当前最大范围，并记录此时的i，作为下一次跳的起点。每次将当前cover找完一遍，就count++，说明跳了一次，同时更新cover和i，表示下一跳从i开始，可以跳的最大范围是cover，直到cover覆盖了数组最后一个位置，此时跳出循环。

### 代码

```C++
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int cover = nums[0];
        int count = 1;
        int newCover = cover;
        int newStart = 0;
        for (int i = 0; i <= cover; i++) {
            if (cover >= nums.size() - 1) {
                break;
            }
            if (nums[i] + i > newCover) {
                newCover = nums[i] + i;
                newStart = i;
            }
            if (i == cover) {
                cover = newCover;
                count++;
                i = newStart;
            }
        }
        return count;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(1).

### 学习与小结

思路感觉还是有一点乱，看看卡哥怎么说：

贪心的思路，局部最优：当前可移动距离尽可能多走，如果还没到终点，步数再加一。整体最优：一步尽可能多走，从而达到最少步数。

**要从覆盖范围出发，不管怎么跳，覆盖范围内一定是可以跳到的，以最小的步数增加覆盖范围，覆盖范围一旦覆盖了终点，得到的就是最少步数！**

**这里需要统计两个覆盖范围，当前这一步的最大覆盖和下一步最大覆盖。**

发现可以不更新i的位置，因为每次更新cover时，i已经到达当前这个节点可以跳到的最远距离，如果更新i，i一定是向前走或者不动的，所以直接继续循环就行。

我加上i其实还是关心具体是怎么跳的，跳到了哪，还是没有抽象成能跳到的范围是多大。这道题只要关心当前能到的范围有多大和到达此范围需要跳几步就行，只要范围覆盖了末尾位置，就可以跳出并且返回步数。

```C++
class Solution {
public:
    int jump(vector<int>& nums) {
        int current_end = 0; // 当前跳跃能到达的最远边界
        int next_end = 0; // 下一跳可以到达的最远位置
        int steps = 0; // 跳跃次数
        // 遍历数组元素，但不需要访问最后一个元素，因为在到达最后一个元素之前我们就已经跳跃了
        for (int i = 0; i < nums.size() - 1; ++i) {
            next_end = max(next_end, i + nums[i]); // 更新下一跳可达的最远位置
            // 当我们到达当前跳跃的边界时，我们进行跳跃，并更新当前的边界
            if (i == current_end) {
                current_end = next_end;
                ++steps;
                // 如果当前边界已经可以到达数组的最后一个位置，则结束循环
                if (current_end >= nums.size() - 1) break;
            }
        }
        return steps;
    }
};
```