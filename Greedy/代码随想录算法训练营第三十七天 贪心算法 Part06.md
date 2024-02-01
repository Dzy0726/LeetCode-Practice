# 代码随想录算法训练营第三十七天| 贪心算法 Part06

## 今日题目

738.[单调递增的数字](https://leetcode.cn/problems/monotone-increasing-digits/)

## LeetCode 738.单调递增的数字

### 题目

当且仅当每个相邻位数上的数字 `x` 和 `y` 满足 `x <= y` 时，我们称这个整数是**单调递增**的。

给定一个整数 `n` ，返回 *小于或等于* *`n`* *的最大数字，且数字呈* ***单调递增*** 。

> 示例 1:
>
> 输入: n = 10 输出: 9
>
> 示例 2:
>
> 输入: n = 1234 输出: 1234
>
> 示例 3:
>
> 输入: n = 332 输出: 299

### 思路

整体是用字符串操作来处理数字，首先判断原数字是否是单调递增的，如果是直接返回原数字，如果不是，则从末位向前修改，每修改一位就判定一下是不是单调递增的，不是就接着修改。比如332，不是单调递增，第一次修改为329，不是单调递增，继续修改为299是单调递增。

修改的规则就是将当前位改为9，前一位在原来的基础上减1。

### 代码

```C++
class Solution {
public:
    bool isIncrease(string num) {
        for (int i = 0; i < num.size() - 1; i++) {
            if (num[i] > num[i + 1]) return false;
        }
        return true;
    }
    int monotoneIncreasingDigits(int n) {
        string num = to_string(n);
        if (isIncrease(num)) return n;
        int i = num.size() - 1;
        while (!isIncrease(num) && i > 0) {
            num[i] = '9';
            int pre = num[i - 1] - '0';
            pre -= 1;
            num[i - 1] = pre + '0';
            i--;
        }
        int result = stoi(num);
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n^2).

空间复杂度：空间复杂度为O(n).

### 学习与小结

因为使用了函数判断是否单调递增，每次调用这个函数的时间复杂度都是O(n)，所以时间复杂度较高，可以在边比较边修改，一次做到又判断又修改：

```C++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string strNum = to_string(N);
        // flag用来标记赋值9从哪里开始
        // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
        int flag = strNum.size();
        for (int i = strNum.size() - 1; i > 0; i--) {
            if (strNum[i - 1] > strNum[i] ) {
                flag = i;
                strNum[i - 1]--;
            }
        }
        for (int i = flag; i < strNum.size(); i++) {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }
};
```

只要前一位比后一位大，就记录后一位为要改为9的位置，前一位减1；遍历一次后，从flag开始都改成9.具体过程是：

332 -> 322 -> 222 -> 292 -> 299

**要记住****int****和string互转的函数：to_string(), stoi()。**

**int****和****char****互转只要让int + '0'或者char - '0' 即可。**