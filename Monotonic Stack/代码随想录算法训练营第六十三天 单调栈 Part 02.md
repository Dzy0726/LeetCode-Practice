# 代码随想录算法训练营第六十三天| 单调栈 Part 02

## 今日题目

503.[下一个更大元素 II](https://leetcode.cn/problems/next-greater-element-ii/)

42.[接雨水](https://leetcode.cn/problems/trapping-rain-water/)

## LeetCode 503.下一个更大元素II

### 题目

给定一个循环数组 `nums` （ `nums[nums.length - 1]` 的下一个元素是 `nums[0]` ），返回 *`nums`* *中每个元素的* ***下一个更大元素*** 。

数字 `x` 的 **下一个更大的元素** 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 `-1` 。

> 示例 1:
>
> 输入: nums = [1,2,1] 输出: [2,-1,2] 解释: 第一个 1 的下一个更大的数是 2； 数字 2 找不到下一个更大的数；  第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
>
> 示例 2:
>
> 输入: nums = [1,2,3,4,3] 输出: [2,3,4,-1,4]

### 思路

和单调栈第一题一模一样，多了个循环数组的处理，我第一想法就是将原数组复制成原理的两倍，然后得到结果，再将结果缩减到原来的大小即可。

这种写法确实比较直观，但做了很多无用操作，例如修改了nums数组，而且最后还要把result数组resize回去。

resize倒是不费时间，是O(1)的操作，但扩充nums数组相当于多了一个O(n)的操作。

其实也可以不扩充nums，而是在遍历的过程中模拟走了两边nums。

### 代码

```C++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size() * 2, -1);
        vector<int> nums2(nums.size() * 2);
        copy(nums.begin(), nums.end(), nums2.begin());
        copy(nums.begin(), nums.end(), nums2.begin() + nums.size());
        // nums.insert(nums.end(), nums.begin(), nums.end());
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                result[st.top()] = nums2[i];
                st.pop();
            }
            st.push(i);
        }
        result.resize(nums.size());
        return result;
    }
};
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size(), -1);
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(2n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

用取余操作想到了，但是写的时候分心了就给忘记了……还是不够熟练，应该很快反应过来用取余操作模拟遍历两次的效果。

## LeetCode 42.接雨水

### 题目

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDQ2MDE0ZGY1NDM3ZDk0NDgxNTE1NjhjOTdmNGI3OTBfYnI5cERkYkRiaWVEOVE4VkxRWmdFQ0dwdndUZXFRMDZfVG9rZW46Q2VEYWJCb1hxb0U0d0t4ZGM5c2NFUGd2bjZkXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)
>
> 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1] 输出：6 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
>
> 示例 2：
>
> 输入：height = [4,2,0,3,2,5] 输出：9

### 思路

终于到接雨水了！

有两种思路，一种是双指针法，一种是单调栈法。

在具体说解法之前，先看下怎么样才能接到雨水。当一个格子的左右两边都比他高的时候，就可以接到雨水，那么能接到多少呢？就是左右两边较低的减去当前的高度，再乘宽度。这是用列的视角来看的，一列列计算每列能接多少雨水。所以可以遍历整个数组，每次都求出左右两边哪边较低，然后宽度为1，计算。

暴力法的时间复杂度是O(n^2)，会超时，所以要对暴力法进行优化，也就是双指针优化法：思路不变，但是用一次遍历求出每个位置左边的最高的高度，用一次遍历求出右边的最高的高度，不再是每次循环都找两边的最高的高度。

那么如何使用新学的单调栈呢？

通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了。

而接雨水这道题目，我们正需要寻找一个元素，右边最大元素以及左边最大元素，来计算雨水面积。

但是单调栈是根据行来计算接雨水的量：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTQ0NDRhZjIxNGNhODAyMDgzNzliMTVjYWMyMzc0YWRfSU1iSkN5THhRYUhtQ2RBQ0l2aVhQZHlBWlA4RnRubW1fVG9rZW46SDIzYWJVWDlSbzhNV2Z4NkNoVGNpc1BRbk1wXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

单调栈内元素的顺序从大到小还是从小到大呢？

从栈头（元素从栈头弹出）到栈底的顺序应该是从小到大的顺序。

因为一旦发现添加的柱子高度大于栈头元素了，此时就出现凹槽了，栈头元素就是凹槽底部的柱子，栈头**第二个元素**就是凹槽左边的柱子，而添加的元素就是凹槽右边的柱子。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjJkMjM1ZTAzMGY5YjA4NTZkNWIwYWM1MDM0ODljODVfU0dTbTFSVnRSSUkxbWwzQ0VsYzFtZHNKR1Q3QjFyaGJfVG9rZW46TEcyZGJwUHZxb2pYR1B4VXI0R2MxTk1vbjlkXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

遇到相同的元素，更新栈内下标，就是将栈里元素（旧下标）弹出，将新元素（新下标）加入栈中。例如 5 5 1 3 这种情况。如果添加第二个5的时候就应该将第一个5的下标弹出，把第二个5添加到栈中。因为我们要求宽度的时候 如果遇到相同高度的柱子，需要使用最右边的柱子来计算宽度。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGQwOTJkNmMxMTRmNjY1OGI5ZDJhMDUyMzU3OGViOGNfTmRvTVhoc29Gb2hNM09XUVB5WklMTlJlc01pWms1TjBfVG9rZW46UzVIb2JDamg2b2JsQ1d4VmV3Z2NCMHJTbnViXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

如果当前遍历的元素（柱子）高度大于栈顶元素的高度，此时就出现凹槽了，取栈顶元素，将栈顶元素弹出，这个就是凹槽的底部，也就是中间位置，下标记为mid，对应的高度为height[mid]

此时的栈顶元素st.top()，就是凹槽的左边位置，下标为st.top()，对应的高度为height[st.top()]

当前遍历的元素i，就是凹槽右边的位置，下标为i，对应的高度为height[i]

那么雨水高度是 min(凹槽左边高度, 凹槽右边高度) - 凹槽底部高度，代码为：`int h = min(height[st.top()], height[i]) - height[mid];`

雨水的宽度是 凹槽右边的下标 - 凹槽左边的下标 - 1（因为只求中间宽度），代码为：`int w = i - st.top() - 1 ;`

当前凹槽雨水的体积就是：`h * w`。

### 代码

双指针优化法：

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        maxLeft[0] = height[0];
        for (int i = 1; i < height.size(); i++) {
            maxLeft[i] = max(maxLeft[i - 1], height[i]);
        }
        maxRight[height.size() - 1] = height[height.size() - 1];
        for (int i = height.size() - 2; i >= 0; i--) {
            maxRight[i] = max(maxRight[i + 1], height[i]);
        }
        for (int i = 1; i < height.size() - 1 ; i++) {
            int current = min(maxLeft[i], maxRight[i]) - height[i];
            if (current > 0) sum += current;
        }
        return sum;
    }
};
```

单调栈法：

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int sum = 0;
        st.push(0);
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            } else if (height[i] == height[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int high =
                            min(height[st.top()], height[i]) - height[mid];
                        int wide = i - st.top() - 1;
                        sum += high * wide;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};
```

### 时空复杂度今日题目

503.[下一个更大元素 II](https://leetcode.cn/problems/next-greater-element-ii/)

42.[接雨水](https://leetcode.cn/problems/trapping-rain-water/)

## LeetCode 503.下一个更大元素II

### 题目

给定一个循环数组 `nums` （ `nums[nums.length - 1]` 的下一个元素是 `nums[0]` ），返回 *`nums`* *中每个元素的* ***下一个更大元素*** 。

数字 `x` 的 **下一个更大的元素** 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 `-1` 。

> 示例 1:
>
> 输入: nums = [1,2,1] 输出: [2,-1,2] 解释: 第一个 1 的下一个更大的数是 2； 数字 2 找不到下一个更大的数；  第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
>
> 示例 2:
>
> 输入: nums = [1,2,3,4,3] 输出: [2,3,4,-1,4]

### 思路

和单调栈第一题一模一样，多了个循环数组的处理，我第一想法就是将原数组复制成原理的两倍，然后得到结果，再将结果缩减到原来的大小即可。

这种写法确实比较直观，但做了很多无用操作，例如修改了nums数组，而且最后还要把result数组resize回去。

resize倒是不费时间，是O(1)的操作，但扩充nums数组相当于多了一个O(n)的操作。

其实也可以不扩充nums，而是在遍历的过程中模拟走了两边nums。

### 代码

```C++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size() * 2, -1);
        vector<int> nums2(nums.size() * 2);
        copy(nums.begin(), nums.end(), nums2.begin());
        copy(nums.begin(), nums.end(), nums2.begin() + nums.size());
        // nums.insert(nums.end(), nums.begin(), nums.end());
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                result[st.top()] = nums2[i];
                st.pop();
            }
            st.push(i);
        }
        result.resize(nums.size());
        return result;
    }
};
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size(), -1);
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(2n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

用取余操作想到了，但是写的时候分心了就给忘记了……还是不够熟练，应该很快反应过来用取余操作模拟遍历两次的效果。

## LeetCode 42.接雨水

### 题目

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDQ2MDE0ZGY1NDM3ZDk0NDgxNTE1NjhjOTdmNGI3OTBfYnI5cERkYkRiaWVEOVE4VkxRWmdFQ0dwdndUZXFRMDZfVG9rZW46Q2VEYWJCb1hxb0U0d0t4ZGM5c2NFUGd2bjZkXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)
>
> 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1] 输出：6 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
>
> 示例 2：
>
> 输入：height = [4,2,0,3,2,5] 输出：9

### 思路

终于到接雨水了！

有两种思路，一种是双指针法，一种是单调栈法。

在具体说解法之前，先看下怎么样才能接到雨水。当一个格子的左右两边都比他高的时候，就可以接到雨水，那么能接到多少呢？就是左右两边较低的减去当前的高度，再乘宽度。这是用列的视角来看的，一列列计算每列能接多少雨水。所以可以遍历整个数组，每次都求出左右两边哪边较低，然后宽度为1，计算。

暴力法的时间复杂度是O(n^2)，会超时，所以要对暴力法进行优化，也就是双指针优化法：思路不变，但是用一次遍历求出每个位置左边的最高的高度，用一次遍历求出右边的最高的高度，不再是每次循环都找两边的最高的高度。

那么如何使用新学的单调栈呢？

通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了。

而接雨水这道题目，我们正需要寻找一个元素，右边最大元素以及左边最大元素，来计算雨水面积。

但是单调栈是根据行来计算接雨水的量：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTQ0NDRhZjIxNGNhODAyMDgzNzliMTVjYWMyMzc0YWRfSU1iSkN5THhRYUhtQ2RBQ0l2aVhQZHlBWlA4RnRubW1fVG9rZW46SDIzYWJVWDlSbzhNV2Z4NkNoVGNpc1BRbk1wXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

单调栈内元素的顺序从大到小还是从小到大呢？

从栈头（元素从栈头弹出）到栈底的顺序应该是从小到大的顺序。

因为一旦发现添加的柱子高度大于栈头元素了，此时就出现凹槽了，栈头元素就是凹槽底部的柱子，栈头**第二个元素**就是凹槽左边的柱子，而添加的元素就是凹槽右边的柱子。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjJkMjM1ZTAzMGY5YjA4NTZkNWIwYWM1MDM0ODljODVfU0dTbTFSVnRSSUkxbWwzQ0VsYzFtZHNKR1Q3QjFyaGJfVG9rZW46TEcyZGJwUHZxb2pYR1B4VXI0R2MxTk1vbjlkXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

遇到相同的元素，更新栈内下标，就是将栈里元素（旧下标）弹出，将新元素（新下标）加入栈中。例如 5 5 1 3 这种情况。如果添加第二个5的时候就应该将第一个5的下标弹出，把第二个5添加到栈中。因为我们要求宽度的时候 如果遇到相同高度的柱子，需要使用最右边的柱子来计算宽度。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGQwOTJkNmMxMTRmNjY1OGI5ZDJhMDUyMzU3OGViOGNfTmRvTVhoc29Gb2hNM09XUVB5WklMTlJlc01pWms1TjBfVG9rZW46UzVIb2JDamg2b2JsQ1d4VmV3Z2NCMHJTbnViXzE3MTA3NDQ5MTY6MTcxMDc0ODUxNl9WNA)

如果当前遍历的元素（柱子）高度大于栈顶元素的高度，此时就出现凹槽了，取栈顶元素，将栈顶元素弹出，这个就是凹槽的底部，也就是中间位置，下标记为mid，对应的高度为height[mid]

此时的栈顶元素st.top()，就是凹槽的左边位置，下标为st.top()，对应的高度为height[st.top()]

当前遍历的元素i，就是凹槽右边的位置，下标为i，对应的高度为height[i]

那么雨水高度是 min(凹槽左边高度, 凹槽右边高度) - 凹槽底部高度，代码为：`int h = min(height[st.top()], height[i]) - height[mid];`

雨水的宽度是 凹槽右边的下标 - 凹槽左边的下标 - 1（因为只求中间宽度），代码为：`int w = i - st.top() - 1 ;`

当前凹槽雨水的体积就是：`h * w`。

### 代码

双指针优化法：

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        maxLeft[0] = height[0];
        for (int i = 1; i < height.size(); i++) {
            maxLeft[i] = max(maxLeft[i - 1], height[i]);
        }
        maxRight[height.size() - 1] = height[height.size() - 1];
        for (int i = height.size() - 2; i >= 0; i--) {
            maxRight[i] = max(maxRight[i + 1], height[i]);
        }
        for (int i = 1; i < height.size() - 1 ; i++) {
            int current = min(maxLeft[i], maxRight[i]) - height[i];
            if (current > 0) sum += current;
        }
        return sum;
    }
};
```

单调栈法：

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int sum = 0;
        st.push(0);
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            } else if (height[i] == height[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int high =
                            min(height[st.top()], height[i]) - height[mid];
                        int wide = i - st.top() - 1;
                        sum += high * wide;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};
```

### 时空复杂度

双指针：

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

单调栈：

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

首先弄清楚怎么计算雨水的量；双指针法按列接，比较好理解，容易想到；单调栈按行接，不是很好想到，尤其是计算雨水量的时候，要计算宽度和高度，宽度这里很容易被忽略或者搞错，应该多举几个例子来验证，比如中间有连续好几个相同高度时。

双指针：

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

单调栈：

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

首先弄清楚怎么计算雨水的量；双指针法按列接，比较好理解，容易想到；单调栈按行接，不是很好想到，尤其是计算雨水量的时候，要计算宽度和高度，宽度这里很容易被忽略或者搞错，应该多举几个例子来验证，比如中间有连续好几个相同高度时。