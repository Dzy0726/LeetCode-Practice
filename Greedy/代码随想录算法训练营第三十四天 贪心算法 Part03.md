# 代码随想录算法训练营第三十四天| 贪心算法 Part03

## 今日题目

1005.[K 次取反后最大化的数组和](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/)

134.[加油站](https://leetcode.cn/problems/gas-station/)

135.[分发糖果](https://leetcode.cn/problems/candy/)

## LeetCode 1005.K次取反后最大化的数组和

### 题目

给你一个整数数组 `nums` 和一个整数 `k` ，按以下方法修改该数组：

- 选择某个下标 `i` 并将 `nums[i]` 替换为 `-nums[i]` 。

重复这个过程恰好 `k` 次。可以多次选择同一个下标 `i` 。

以这种方式修改数组后，返回数组 **可能的最大和** 。

> 示例 1：
>
> 输入：nums = [4,2,3], k = 1 输出：5 解释：选择下标 1 ，nums 变为 [4,-2,3] 。
>
> 示例 2：
>
> 输入：nums = [3,-1,0,2], k = 3 输出：6 解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
>
> 示例 3：
>
> 输入：nums = [2,-3,-1,5,-4], k = 2 输出：13 解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。

### 思路

每次调整就把数组中最小的给调整，这样保证和最大。所以先对数组排序，对nums[0]调整即可，这道题还是非常简单的。

### 代码

```C++
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        while (k--) {
            sort(nums.begin(), nums.end());
            nums[0] = -nums[0];
        }
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;
    }
};
```

### 时空复杂度

时间复杂度：

1. 每次调用 `sort(nums.begin(), nums.end());` 的时间复杂度是 `O(NlogN)`，其中 `N` 是 `nums` 数组的长度。这是因为 `sort()` 函数通常采用快速排序算法。
2. 这个排序操作会在 `while` 循环中执行 `k` 次，因此这部分的总时间复杂度是 `O(k * NlogN)`。
3. 在 `while` 循环之后，代码中有一个 `for` 循环用于计算数组中所有元素的和。这个循环的时间复杂度是 `O(N)`，因为它会遍历数组一次。

因此，总的时间复杂度是排序时间和求和时间的总和：`O(k * NlogN + N)`。

空间复杂度：空间复杂度为O(1).

## LeetCode 134.加油站

### 题目

在一条环路上有 `n` 个加油站，其中第 `i` 个加油站有汽油 `gas[i]` 升。

你有一辆油箱容量无限的的汽车，从第 `i` 个加油站开往第 `i+1` 个加油站需要消耗汽油 `cost[i]` 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 `gas` 和 `cost` ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 `-1` 。如果存在解，则 **保证** 它是 **唯一** 的。

> 示例 1:
>
> 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2] 输出: 3 解释: 从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油 开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油 开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油 开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油 开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油 开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。 因此，3 可为起始索引。
>
> 示例 2:
>
> 输入: gas = [2,3,4], cost = [3,4,3] 输出: -1 解释: 你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。 我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油 开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油 开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油 你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。 因此，无论怎样，你都不可能绕环路行驶一周。

### 思路

最开始想到的是选取到达目的地后邮箱剩余的油最多的点为起点，比如gas = [1,2,3,4,5], cost = [3,4,5,1,2]中，选择i=3，剩余油量3为起点，但是发现gas =[5,8,2,8],cost =[6,5,6,6]时，选择i = 1剩余油量最多，但是无法完成循环；于是又把所有可能的起点加入到一个数组，遍历这个数组找出能完成循环的点就return，最后返回-1，显然超时了；又想到选到达目的地后加上油，剩余油量最多的点为起点，但是碰到了gas =[5,5,1,3,4],cost =[8,1,7,1,1],选i = 4为起点，也无法完成循环。没有做出来……

### 代码

最后的错误代码：

```C++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = -1;
        int remain = 0;
        for (int i = 0; i < gas.size(); i++) {
            int next = (i + 1) % gas.size();
            if (gas[i] - cost[i] >= 0 && gas[i] - cost[i] + gas[next] > remain) {
                remain = gas[i] - cost[i] + gas[next];
                start = i;
            }
        }
        int next = (start + 1) % gas.size();
        while (next != start) {
            remain -= cost[next];
            if (remain < 0) return -1;
            next = (next + 1) % gas.size();
            remain += gas[next];
        }
        return start;
    }
};
```

### 学习与小结

1. 贪心算法

   1.  如果总油量减去总消耗大于等于零那么一定可以跑完一圈，说明 各个站点的加油站 剩油量rest[i]相加一定是大于等于零的。每个加油站的剩余量rest[i]为gas[i] - cost[i]。i从0开始累加rest[i]，和记为curSum，一旦curSum小于零，说明[0, i]区间都不能作为起始位置，因为这个区间选择任何一个位置作为起点，到i这里都会断油，那么起始位置从i+1算起，再从0计算curSum。

   2.  **A到不了C，那么一定不存在AC中间一个点B可以到C，因为如果B可以到C，A可以到B，那么A就可以到C。**

   3.  局部最优：当前累加rest[i]的和curSum一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。

   4.  全局最优：找到可以跑一圈的起始位置。

   5. ```C++
      class Solution {
      public:
          int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
              int sum = 0;
              int curSum = 0;
              int start = 0;
              for (int i = 0; i < gas.size(); i++) {
                  sum += gas[i] - cost[i];
                  curSum += gas[i] - cost[i];
                  if (curSum < 0) {
                      start = i + 1;
                      curSum = 0;
                  }
              }
              if (sum < 0) return -1;
              return start;
          }
      };
      ```

2. 妙解

   1.  到达minIndex的位置能使得油量最紧缺，那么minIndex就应该是整个旅程的最后一站，相应的minIndex+1的位置就是起点。sum>=0才能保证整个过程的供油量满足耗油量，即有解。

   2.  minIndex表示油量最紧缺的时候，如果sum >=0,就说明油量足够到下一个站点，就不用给minIndex赋值。eg：到达每个位置油量都充足，sum >=0恒成立。那minIndex=-1恒成立，最后结果返回0，结果符合题意。如果没有 && sum < 0这个条件。那第一次循环中if条件一定位true，minIndex会变成0，最后结果返回1，结果不符合题意。

   3. ```C++
      class Solution {
      public:
          int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
              int sum = 0;
              int min = INT32_MAX;
              int minIndex = -1;
              for (int i = 0; i < gas.size(); i++) {
                  sum += gas[i] - cost[i];
                  if (sum < 0 && sum < min) {
                      min = sum;
                      minIndex = i;
                  }
              }
              if (sum < 0) return -1;
              return (minIndex + 1) % gas.length;
          }
      };
      ```

## LeetCode 135.分发糖果

### 题目

`n` 个孩子站成一排。给你一个整数数组 `ratings` 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

- 每个孩子至少分配到 `1` 个糖果。
- 相邻两个孩子评分更高的孩子会获得更多的糖果。

请你给每个孩子分发糖果，计算并返回需要准备的 **最少糖果数目** 。

> 示例 1：
>
> 输入：ratings = [1,0,2] 输出：5 解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
>
> 示例 2：
>
> 输入：ratings = [1,2,2] 输出：4 解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。

### 思路

这道题没做出来，不知道如何同时处理两边的情况。比如例子1,4,3,2,1，如果只是局部选4最大，给4两个，那么也会给3两个，那4又要增加1，于是无解……

**这道题目一定是要确定一边之后，再确定另一边，例如比较每一个孩子的左边，然后再比较右边，如果两边一起考虑一定会顾此失彼。**

先从前往后确定一遍，再从后往前确定一遍，每个孩子选取给的多的那种情况为最终结果。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzMzMjg3OGQwMjA2YWE2ZWM5YWUyMTBjZWViNzA4NDBfa0VkYkQ2ZkZ2dExkazZibFd3TGlUWVg4emhvZHYyRzRfVG9rZW46VFltTGJoUVNpb0xuSGF4S3ZZT2Nndk45bkdjXzE3MDY1MzEwNTU6MTcwNjUzNDY1NV9WNA)

如上图，只要右边孩子大于左边孩子，就给右边孩子比左边孩子多1的糖果；

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YWEwNTE4YmRmNzkxOTNjYmY3MTYyMjdlZGJjOTE3YmNfNXdmaFpReUhad0hta2JSSXlYUmVLaHl4b0RZMXFPWkRfVG9rZW46RFhhaGI3RlFabzRzN0N4Z1ZlR2NDUVRMbnRmXzE3MDY1MzEwNTU6MTcwNjUzNDY1NV9WNA)

再从后往前来一次，只要左边的比右边大，就给左边的多一个糖果。对于每个孩子选取最多可以拿到的糖果数，比如i=5在第一轮拿到1个，在第二轮拿到2个，最终就给他2个。

### 代码

```C++
class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candies(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }
        int sum = 0;
        for (auto candy : candies) {
            sum += candy;
        }
        return sum;
    }
};
```

### 学习与小结

采用了两次贪心的策略：

- 一次是从左到右遍历，只比较右边孩子评分比左边大的情况。
- 一次是从右到左遍历，只比较左边孩子评分比右边大的情况。

如果在考虑局部的时候想两边兼顾，就会顾此失彼。