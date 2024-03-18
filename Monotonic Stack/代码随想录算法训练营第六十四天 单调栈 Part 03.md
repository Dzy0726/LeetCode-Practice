# 代码随想录算法训练营第六十四天| 单调栈 Part 03

## 今日题目

84.[柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)

## LeetCode 84.柱状图中最大的矩形

### 题目

给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

> 示例 1:
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=N2U5MzYzYjJkM2EyNWU2MGY0YzQ4N2JjMjRiMmY5MDZfZjhKTzVhMmFQSTdqQUp1czdncDIzVTZld3A1cEJrZWFfVG9rZW46VjBoYmI1NXBsb1p3bTN4c3Aya2MzWmRkbjFmXzE3MTA3NTE1OTA6MTcxMDc1NTE5MF9WNA)
>
> 输入：heights = [2,1,5,6,2,3] 输出：10 解释：最大的矩形为图中红色区域，面积为 10
>
> 示例 2：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTA5YjA0NzhkMmU0YWU2MWI3YmNiNzQ3MmNkZWEyMmFfc295Uk9Ga1JOU0RSc2pQTG4wa3piWWxaM1ozbmZMN01fVG9rZW46SWY2Z2JUVmdIb3RvZnd4VHF6MGNLSFhrbnFkXzE3MTA3NTE1OTA6MTcxMDc1NTE5MF9WNA)
>
> 输入： heights = [2,4] 输出： 4

### 思路

和接雨水一样，但是一上来就没想到怎么来求这个矩形。

求矩形的方法应该是：以当前这一列为基准，向左右找到第一个比他低的，为什么找比他低的？因为如果左右比他高，说明可以以他的高度贯穿，求面积时的h用的就是当前这列的高，现在是求这个高度最多能有多宽，所以左右找到第一个没他高的，二者之差减1就是当前高度最长的宽，也就是当前高度最大的面积。

依旧可以用暴力思想加双指针优化，两个数组分别记录左边第一个最低i的下标和右边第一个低于i的下标，然后用height[i]*（right-left-1）得到面积，比较后得到最大的面积。

怎么用单调栈呢？和接雨水比基本相同，42. 接雨水是找每个柱子左右两边第一个大于该柱子高度的柱子，而本题是找每个柱子左右两边第一个小于该柱子的柱子。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZmVjMzNiMTBiNzI5NDM0MWE2NjQ1ZDI4YmM0NDkwMWRfREdVeWJqb0ZjUTZuRnVuVW5wQkVXYVNJUzZYTU05c0hfVG9rZW46TkVXSmJPcmVtb0tkOXF4djJHMWN0ZW5xbm1iXzE3MTA3NTE1OTA6MTcxMDc1NTE5MF9WNA)

所以栈顶应该是当前最小的，如果height[i]比栈顶小，就要进行一次计算，

heights[st.top]是矩形的高，i是右边第一个没他高的下标，取了top后pop一次，然后新的top是左边第一个没他高的下标，于是可以计算面积：

int high = heights[mid];

int wide = i - st.top() - 1;

到这里基本与接雨水思路相同，接下里就是判断三种情况。

那么这道题不一样的点在于：在heights数组收尾+0.

如果数组本身就是升序的，例如[2,4,6,8]，那么入栈之后 都是单调递减，一直都没有走情况三计算结果的哪一步，所以最后输出的就是0了。那么**结尾加一个0**，就会让栈里的所有元素，走到情况三的逻辑。

如果数组本身是降序的，例如 [8,6,4,2]，在 8 入栈后，6 开始与8 进行比较，此时我们得到 mid（8），rigt（6），但是得不到 left。（mid、left，right 都是对应版本一里的逻辑）因为将8弹出之后，栈里没有元素了，那么为了避免空栈取值，直接跳过了计算结果的逻辑。之后又将6 加入栈（此时8已经弹出了），然后 就是 4 与 栈口元素 8 进行比较，周而复始，那么计算的最后结果resutl就是0。

**所以我们需要在 height数组前后各加一个元素0。**

### 代码

```C++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        stack<int> st;
        st.push(0);
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    int high = heights[mid];
                    int wide = i - st.top() - 1;
                    result = max(result, wide * high);
                }
                st.push(i);
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

接雨水的双指针是按列接雨水，单调栈是按行接雨水；接雨水计算是找到左右两边第一个比当前高的，形成凹槽，然后计算雨水；

矩形面积是找到左右两边第一个比当前柱子低的，确定宽度的范围，求出当前最大的面积。