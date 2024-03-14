# 代码随想录算法训练营第五十六天| 动态规划 Part13

## 今日题目

300.[最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)

674.[最长连续递增序列](https://leetcode.cn/problems/longest-continuous-increasing-subsequence/)

718.[最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)

## LeetCode 300.最长递增子序列

### 题目

给你一个整数数组 `nums` ，找到其中最长严格递增子序列的长度。

**子序列** 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列.

> 示例 1：
>
> 输入：nums = [10,9,2,5,3,7,101,18] 输出：4 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
>
> 示例 2：
>
> 输入：nums = [0,1,0,3,2,3] 输出：4
>
> 示例 3：
>
> 输入：nums = [7,7,7,7,7,7,7] 输出：1

### 思路

dp[i]表示到i时，最长子序列的长度。dp数组的含义非常容易想到，难在如何状态转移。

[2,5,3]，到i指向3时，其实最长子序列应该是2,3，长度为2，而不是继承于dp[n-1]的2.

其实从这里可以略微的感受到对于每个i，要从头开始遍历一次，看看前面哪个比他小，比如j比它小，然后用dp[j]+1和当前的dp[i]比较，取较大值。

所以状态转移公式就是在两层循环内，对于i来说就是在0~i-1这几个数内找出比他小的数，dp[i] = max(dp[i], dp[j] + 1).

初始化的话dp数组全部为1，因为最小子序列就是自己本身。

最终返回dp数组中最大的数，可以在循环中比较，也可以最后比较整个数组。

### 代码

```C++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

### 时空复杂度

时间复杂度：

1. 外层循环遍历了 `nums` 数组一次，循环次数为 `n`（`nums.size()`）。
2. 内层循环在外层循环的每次迭代中最多执行 `i` 次，也就是说，内层循环的执行次数是一个从 `1` 增加到 `n-1` 的序列。因此，内层循环总的执行次数是 `1 + 2 + ... + (n-1)`，这是一个等差数列求和，和为 `(n-1)*n/2`，也就是 `O(n^2/2)`。

总的时间复杂度是`O(n^2)`。

空间复杂度：空间复杂度为O(n).

### 学习与小结

最长子序列的动态规划问题也是第一次见，希望后面可以越做越好。

## LeetCode 674.最长连续递增序列

### 题目

给定一个未经排序的整数数组，找到最长且 **连续递增的子序列**，并返回该序列的长度。

**连续递增的子序列** 可以由两个下标 `l` 和 `r`（`l < r`）确定，如果对于每个 `l <= i < r`，都有 `nums[i] < nums[i + 1]` ，那么子序列 `[nums[l], nums[l + 1], ..., nums[r - 1], nums[r]]` 就是连续递增子序列。

> 示例 1：
>
> 输入：nums = [1,3,5,4,7] 输出：3 解释：最长连续递增序列是 [1,3,5], 长度为3。 尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。 
>
> 示例 2：
>
> 输入：nums = [2,2,2,2,2] 输出：1 解释：最长连续递增序列是 [2], 长度为1。

### 思路

有了上一题的铺垫，这道题非常简单了，要求连续的最长子序列，dp数组的含义不变，状态转移只和前一个值有关，只要当前值比前一个值大，就可以根据前一个的dp值+1来得到当前的dp值。

**不连续递增子序列的跟前0-i 个状态有关，连续递增的子序列只跟前一个状态有关。**

### 代码

```C++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(n).

### 学习与小结

关于*max_element(dp.begin(), dp.end())函数的底层实现：

`std::max_element` 是 C++ 标准模板库（STL）算法中的一个函数，它用于在给定范围内查找最大元素。

1. **初始化：** 首先，`std::max_element` 函数会接受两个迭代器参数，这两个迭代器定义了一个容器的范围（从 `dp.begin()` 到 `dp.end()`）。函数开始时会将第一个迭代器指向的元素设为当前找到的最大元素。
2. **迭代比较：** 然后，函数从范围的起始位置开始，逐个迭代元素，使用迭代器向前移动。
3. **更新最大值：** 对于迭代器指向的每一个元素，函数会和当前记录的最大值进行比较。如果当前元素比最大值大，就更新最大值为当前元素。
4. **返回结果：** 当迭代完成整个范围后，函数返回一个指向所找到的最大元素的迭代器。

伪代码如下：

```C++
template <typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last; // 如果范围为空，直接返回last

    ForwardIterator largest = first; // 初始化最大元素为第一个元素
    ++first; // 从下一个元素开始遍历

    // 遍历给定范围内的所有元素
    for (; first != last; ++first) {
        // 如果当前元素大于记录的最大元素，更新最大元素
        if (*largest < *first) {
            largest = first;
        }
    }

    return largest; // 返回最大元素的迭代器
}
```

## LeetCode 718.最长重复子数组

### 题目

给两个整数数组 `nums1` 和 `nums2` ，返回 *两个数组中* ***公共的*** *、长度最长的子数组的长度* 。

> 示例 1：
>
> 输入：nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7] 输出：3 解释：长度最长的公共子数组是 [3,2,1] 。
>
> 示例 2：
>
> 输入：nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0] 输出：5

### 思路

题目中说的子数组，其实就是**连续子序列**。要求两个数组中最长重复子数组，如果是暴力的解法 只需要先两层for循环确定两个数组起始位置，然后再来一个循环可以是for或者while，来从两个起始位置开始比较，取得重复子数组的长度。时间复杂度为O(n^3)。

最长重复子数组=最长连续子序列。先牢记这一点，如果当前比较的两个数不等，那么就算前面全部相等，到这里也不是最长连续子序列了。

用二维数组来处理，dp[i][j] = k的**含义**是nums[0:i-1]和nums[0:j-1]的最长重复子序列的长度是k。为什么是i-1和j-1不是i和j呢？当然可以，就是实现起来麻烦一些。如果定义 dp[i][j]为以下标i为结尾的A，和以下标j为结尾的B，那么第一行和第一列毕竟要进行初始化，如果nums1[i] 与 nums2[0] 相同的话，对应的 dp[i][0]就要初始为1， 因为此时最长重复子数组为1。 nums2[j]与nums1[0]相同的话，同理。但是用i-1和j-1时，dp二维数组的第一行和第一列直接初始化为0即可，因为表示nums1和nums2下表为-1位置的数组和其他对应部分的最长连续子序列，当然是0.

dp[i][j]的值依赖于nums1[i-1]和nums2[j-1]是否相等，如果二者不相等，那么就算前面是相同的连续子序列，到这一位也不相等了，所以为0；如果二者相等，那么看前面有几位连续相等，也就是dp[i-1][j-1]的值为多少，在这个基础上加1即可。

**所以状态转移公式为：**

If nums1[i-1] == nums2[j-1]: dp[i][j] = dp[i-1][j-1] +1 

**初始化**的时候将整个二维数组初始化为0，所以i和j从1开始遍历，逐个比较。

**举例推导****dp****数组**

拿示例1中，A: [1,2,3,2,1]，B: [3,2,1,4,7]为例，画一个dp数组的状态变化，如下：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MWI0OGI1NmQ2MWVhNzdjZDllNjg5MTc0NDA2OTE0ODlfNTNnMHowZWpvazVtV3l5MVd4eG01dzgxQXl0WDR2eUxfVG9rZW46WDI0emJON2Y0b0ptdGt4QjRuTmNWamQ4bnRkXzE3MTAzODcyNTY6MTcxMDM5MDg1Nl9WNA)

### 代码

```C++
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        int result = 0;
        for (int i = 1; i < nums1.size() + 1; i++) {
            for (int j = 1; j < nums2.size() + 1; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                if (dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n*m)

空间复杂度：空间复杂度为O(n*m)

### 学习与小结

可以看出dp[i][j]都是由dp[i - 1][j - 1]推出。那么压缩为一维数组，也就是dp[j]都是由dp[j - 1]推出。

也就是相当于可以把上一层dp[i - 1][j]拷贝到下一层dp[i][j]来继续用。

此时遍历B数组的时候，就要从后向前遍历，这样避免重复覆盖。

```C++
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<int> dp(vector<int>(B.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= A.size(); i++) {
            for (int j = B.size(); j > 0; j--) {
                if (A[i - 1] == B[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                } else dp[j] = 0; // 注意这里不相等的时候要有赋0的操作
                if (dp[j] > result) result = dp[j];
            }
        }
        return result;
    }
};
```