# **代码随想录算法训练营第二天| 数组Part02**

## 今日题目

977.[有序数组的平方](https://leetcode.cn/problems/squares-of-a-sorted-array/)

209.[长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/)

59.[螺旋矩阵II](https://leetcode.cn/problems/spiral-matrix-ii/)

## LeetCode 977. 有序数组的平方

给你一个按 **非递减顺序** 排序的整数数组 `nums`，返回 **每个数字的平方** 组成的新数组，要求也按 **非递减顺序** 排序。

**示例 1：**

```
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
```

**示例 2：**

```
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
```

### 思路

第一思路是暴力法，先求平方，再排序，但由于排序的存在，时间复杂度肯定到不了O(n)。接着就想到昨天的双指针法，注意到最大值肯定是数组两边的一个值，从而想到左右两个指针，找到当前最大值后往中间逐步靠拢。

### 代码

```c++
class Solution {
public:
    int square(int n) {
        return n*n;
    }

    vector<int> sortedSquares(vector<int>& nums) {
        int length = nums.size();
        vector <int> result(length);
        int leftIndex = 0, rightIndex = length - 1;
        int index = length - 1;
        while (leftIndex <= rightIndex) {
            if (square(nums[leftIndex]) < square(nums[rightIndex])) {
                result[index--] = square(nums[rightIndex]);
                rightIndex--;
            } else {
                result[index--] = square(nums[leftIndex]);
                leftIndex++;
            }
        }
        //result[index] = square(nums[leftIndex]);
        return result;
    }
};
```

### 时空复杂度

- 时间复杂度：循环过程中每个元素遍历了一次，时间复杂度为O(n).
- 空间复杂度：新建了一个长度为n的vector，所以空间复杂度为O(n).

### 出现的问题

第一次提交关注的测试用例正负数都有，当时为了让空间复杂度为O(1)，在找到最大值后就地更换，即如果在数组最右侧找到了最大平方，直接将该下标的值换位其平方；如果在数组最左侧找到了最大平方，就先把当前最右侧的值换到最左侧，再用最大平方覆盖最右侧。这样就导致了只有右边的指针在移动，左边的指针几乎不移动，所以在面对数组都是负数的情况，就会发生错误。

### 学习

该题思路还是非常简单清晰的，唯一要注意的就是跳出循环的条件，是`left <= right`还是`left < right`？其实是可以等于的，当只剩最后一个元素时，就是left==right的情况。如果写了`left < right`，那么还需要在循环结束后，把最小平方加入到结果数组的首位。

### 小结

暴力法中快排的复杂度是O(nlogn)，在题目没有特殊强调原地置换时，可以适当多用一些空间，没必要非要将空间复杂度限制到O(1).

## LeetCode 209. 长度最小的子数组

给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**

找出该数组中满足其总和大于等于 `target` 的长度最小的 **连续子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

**示例 1：**

```
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

**示例 2：**

```
输入：target = 4, nums = [1,4,4]
输出：1
```

**示例 3：**

```
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

### 思路

这道题做过，但是这次仍然没有AC，滑动窗口在脑子里也只剩下四个字了，有种无力感啊啊啊T_T……

### 代码

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i = 0, sum = 0;
        int result = INT32_MAX;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= target) {
                result = result < (j - i + 1) ? result : (j - i + 1);
                sum -= nums[i];
                i++;
            }
        }
        if (result == INT32_MAX) {
            result = 0;
        }
        return result;
    }
};
```

### 时空复杂度

- 时间复杂度：虽然是for循环中一个while循环，但是其实每个元素在滑动窗后进来操作一次，出去操作一次，每个元素都是被操作两次，所以时间复杂度是 2 × n 也就是O(n).
- 空间复杂度：O(1).

### 学习

一个for循环，循环变量j指的是窗口的终止位置。起始位置和终止位置初始为0，然后终止位置j开始向右移动，每次移动就将num[j]加入到sum中，然后去比较是否大于等于target。如果大于target，先记录下现在的子数组的长度，并判断是否小于已有的最小长度，如果现在是最小的子数组，就更新result。然后再把初始位置的值从sum中剔除掉，并且让起始指针向右移动。那么这个比较是在while还是在if中呢？

如果是if的话，现在sum已经大于等于target，在if内进行i++，结束if后，在for循环进行了j++，那么相当于i和j同时右移一位，窗口大小不变，所以用if的话窗口大小只能是一直增加或保持不变，并没有做到滑动窗口。

比如target为100，nums:[1,2,3,4,5,100,5,4,3,2,1]，i=0，j=5时sum大于target，如果是if，那么i=1，j=6，窗口大小仍然不变，但是真正的最小子数组长度应该变短了。而用while的话，只要sum大于target，起始指针i可以一直右移，不断缩小窗口大小，也不断更新result。这样才在真正意义上做到了**滑动窗口**。

引用Leetcode一位coder的解释：

> 可以理解为左右指针中间窗口的sum为两指针的“共同财产”，就是右指针一直在努力工作挣钱，好不容易共同财产大过target，记录一下两指针之间的距离，结果左指针就开始得瑟挥霍，不停花钱（往右移动），结果花钱一直花到sum又小过target，此时右指针不得不再次出来工作，不停向右移动，周而复始，最后取左右指针离得最近的时候

### 小结

滑动窗口代码非常简洁，当下理解了会觉得没什么难度，但是可能几个月后又遗忘了怎么写。遇见子串问题，子数组问题，优先去想滑动窗口。



## LeetCode 59. 螺旋矩阵 II

### 题目

给你一个正整数 `n` ，生成一个包含 `1` 到 `n2` 所有元素，且元素按顺时针顺序螺旋排列的 `n x n` 正方形矩阵 `matrix` 。

**示例 1：**

```
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
```

**示例 2：**

```
输入：n = 1
输出：[[1]]
```

### 思路

生成螺旋矩阵时要控制好循环的边界，模拟转圈有四个方向的赋值，必须要让四个方向的赋值统一起来。第一次提交用到了edge和start两个变量，edge用来控制在本次循环中，前两个方向的最大边界，即从左到右，从上到下的边界；start确定本次循环中i，j开始的位置，以及后两个方向的边界，即从右到左，从下到上的边界。最后还要看n是奇数还是偶数，是奇数需要将中间位置填充。

### 代码

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int i, j, count = 1;
        int edge = n - 1;
        int start = 0;
        vector<vector<int>> matrix(n, vector<int>(n));
        while (count < n*n) {
            for (i = start, j = start; j < edge; j++) {
                matrix[i][j] = count++;
            }
            for(; i < edge; i++) {
                matrix[i][j] = count++;
            }
            for (; j > start; j--) {
                matrix[i][j] = count++;
            }
            for (; i > start; i--) {
                matrix[i][j] = count++;
            }
            edge = edge - 1;
            start = start + 1;
        } 
        if (n % 2 != 0) {
            matrix[start][start] = n * n;
        }
        return matrix;  
    }
};
```

### 时空复杂度

- 时间复杂度：给数组赋值相当于遍历了一次二维数组，O(n^2).
- 空间复杂度：几个边界变量等，空间复杂度O(1).

### 出现的问题

这个题画图画了很久，比起之前做，进步在有意识的去控制边界。出现的一个小问题是：以n=5为例，第一次循环（第一圈）每个方向要填充四个值，第二次循环变成了两个值，导致在控制edge时，直接让`edge=edge-2`，没有注意到起始位置也加了一，所以edge减一就可以。对edge这个变量的含义还是有些混淆，其实edge就是模拟转圈中最右和最下的边界，而start不仅可以作为起始位置，也能作为最左和最上的边界。

### 学习

在判断跳出循环条件时，我选择了count大于等于n方，即除了奇数正中间的格子其余格子均被填充即跳出循环。而代码随想录中给出的代码是循环的圈数，这是我一开始没想到的。通过枚举也可以发现，给定数字n，最终循环圈数就是n/2，向下取整，n为3就是循环1圈，n为5就是循环两圈。

### 小结

经过这道题，我对**循环不变量**的理解进一步加深。本题中不变量就是指对于每条边的处理规则，是左闭右闭还是左闭右开。在这道题中显然是不方便进行左闭右闭，与之相比，左闭右开更符合模拟转圈的过程。
