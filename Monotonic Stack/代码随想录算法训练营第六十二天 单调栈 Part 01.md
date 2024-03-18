# 代码随想录算法训练营第六十二天| 单调栈 Part 01

## 今日题目

739.[每日温度](https://leetcode.cn/problems/daily-temperatures/)

496.[下一个更大元素 I](https://leetcode.cn/problems/next-greater-element-i/)

## LeetCode 739.每日温度 

### 题目

给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

> 示例 1:
>
> 输入: temperatures = [73,74,75,71,69,72,76,73] 输出: [1,1,4,2,1,1,0,0]
>
> 示例 2:
>
> 输入: temperatures = [30,40,50,60] 输出: [1,1,1,0]
>
> 示例 3:
>
> 输入: temperatures = [30,60,90] 输出: [1,1,0]

### 思路

暴力解法果然超时哈哈~

怎么能想到用单调栈呢？ 什么时候用单调栈呢？

通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了。时间复杂度为O(n)。

单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素高的元素，优点是整个数组只需要遍历一次。

更直白来说，就是用一个栈来记录我们遍历过的元素，因为我们遍历数组的时候，我们不知道之前都遍历了哪些元素，以至于遍历一个元素找不到是不是之前遍历过一个更小的，所以我们需要用一个容器（这里用单调栈）来记录我们遍历过的元素。

在使用单调栈的时候首先要明确如下几点：

1. 单调栈里存放的元素是什么？

单调栈里只需要存放元素的下标i就可以了，如果需要使用对应的元素，直接T[i]就可以获取。

1. 单调栈里元素是递增呢？ 还是递减呢？

使用递增循序（再强调一下是指从栈头到栈底的顺序），因为只有递增的时候，栈里要加入一个元素i的时候，才知道栈顶元素在数组中右面第一个比栈顶元素大的元素是i。

使用单调栈主要有三个判断条件。

- 当前遍历的元素T[i]小于栈顶元素T[st.top()]的情况
- 当前遍历的元素T[i]等于栈顶元素T[st.top()]的情况
- 当前遍历的元素T[i]大于栈顶元素T[st.top()]的情况

当前元素小于等于栈顶，就不作操作，只是把当前元素入栈；如果当前元素大于栈顶，说明栈顶的结果有了更新，找到了比他大的元素，那么先计算二者之间的距离，再弹出栈顶，将新元素入栈。

### 代码

暴力法：

```C++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++) {
            for (int j = i + 1; j < temperatures.size(); j++) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    break;
                }
            }
        }
        return result;
    }
};
```

单调栈：

```C++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        vector<int> result(temperatures.size(), 0);
        st.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(1).

### 学习与小结

做起来感觉有点像滑动窗口最大值，自定义了队列，然后每次入队时将队里比他小的先出队，然后将他入队。

[代码随想录算法训练营第十三天| 栈与队列 Part03](https://pkdwxagc9o.feishu.cn/wiki/IybHwl87HicYDnkmYHPcMBspnKs?fromScene=spaceOverview)

## LeetCode 496.下一个更大元素I

### 题目

`nums1` 中数字 `x` 的 **下一个更大元素** 是指 `x` 在 `nums2` 中对应位置 **右侧** 的 **第一个** 比 `x` 大的元素。

给你两个 **没有重复元素** 的数组 `nums1` 和 `nums2` ，下标从 **0** 开始计数，其中`nums1` 是 `nums2` 的子集。

对于每个 `0 <= i < nums1.length` ，找出满足 `nums1[i] == nums2[j]` 的下标 `j` ，并且在 `nums2` 确定 `nums2[j]` 的 **下一个更大元素** 。如果不存在下一个更大元素，那么本次查询的答案是 `-1` 。

返回一个长度为 `nums1.length` 的数组 `ans` 作为答案，满足 `ans[i]` 是如上所述的 **下一个更大元素** 。

> 示例 1：
>
> 输入：nums1 = [4,1,2], nums2 = [1,3,4,2]. 输出：[-1,3,-1] 解释：nums1 中每个值的下一个更大元素如下所述： 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。 1 ，用加粗斜体标识，nums2 = [*1*,3,4,2]。下一个更大元素是 3 。 2 ，用加粗斜体标识，nums2 = [1,3,4,*2*]。不存在下一个更大元素，所以答案是 -1 。
>
> 示例 2：
>
> 输入：nums1 = [2,4], nums2 = [1,2,3,4]. 输出：[3,-1] 解释：nums1 中每个值的下一个更大元素如下所述： 2 ，用加粗斜体标识，nums2 = [1,*2*,3,4]。下一个更大元素是 3 。 4 ，用加粗斜体标识，nums2 = [1,2,3,*4*]。不存在下一个更大元素，所以答案是 -1 。

### 思路

对于nums2基本和上题一样，求出一个数组resIdx，resIdx[i]表示比nums2[i]大的第一个元素的值是resIdx[i]。

然后寻找nums1[i]在nums2中的下标j，将result[i]赋值为resIdx[j]即可。

### 代码

```C++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> resIdx(nums2.size(), 0);
        vector<int> result(nums1.size(), -1);
        st.push(0);
        for (int i = 1; i < nums2.size(); i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                resIdx[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        for (int i = 0; i < nums1.size(); i++) {
            int index = -1;
            // 这段用哈希表优化性能
            for (int j = 0; j < nums2.size(); j++) {
                if (nums1[i] == nums2[j]) {
                    index = j;
                    break;
                }
            }
            if (resIdx[index] != 0) {
                result[i] = nums2[resIdx[index]];
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n+m).

空间复杂度：空间复杂度为O(n+m).

### 学习与小结

注意题目中说是两个没有重复元素 的数组 nums1 和 nums2。

没有重复元素，我们就可以用map来做映射了。根据数值快速找到下标，还可以判断nums2[i]是否在nums1中出现过。

```C++
unordered_map<int, int> umap; // key:下标元素，value：下标
for (int i = 0; i < nums1.size(); i++) {
    umap[nums1[i]] = i;
}
```