# 代码随想录算法训练营第五十八天| 动态规划 Part15

## 今日题目

392.[判断子序列](https://leetcode.cn/problems/is-subsequence/)

115.[不同的子序列](https://leetcode.cn/problems/distinct-subsequences/)

## LeetCode 392.判断子序列

### 题目

给定字符串 **s** 和 **t** ，判断 **s** 是否为 **t** 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，`"ace"`是`"abcde"`的一个子序列，而`"aec"`不是）。

**进阶：**

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

> 示例 1：
>
> 输入：s = "abc", t = "ahbgdc" 输出：true
>
> 示例 2：
>
> 输入：s = "axc", t = "ahbgdc" 输出：false

### 思路

双指针，逐个比较s和j的每一位，最后如果负责s的指针到了末尾，返回true；否则返回false。

### 代码

```C++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        if (i == s.size()) return true;
        else return false;
    }
};
```

Dp:

```C++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i < s.size() + 1; i++) {
            for (int j = 1; j < t.size() + 1; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[s.size()][t.size()] == s.size();
    }
};
```

### 时空复杂度

时间复杂度：双指针时间复杂度为O(n)，dp为O(n * m)

空间复杂度：双指针空间复杂度为O(1)，dp为O(n * m)

### 学习与小结

发现和[1143.最长公共子序列 (opens new window)](https://programmercarl.com/1143.最长公共子序列.html)的递推公式基本那就是一样的，区别就是本题如果删元素一定是字符串t，而1143.最长公共子序列是两个字符串都可以删元素。1143那道题是dp=dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])。

暂时没体验到什么是**编辑距离...**

## LeetCode 115.不同的子序列

### 题目

给你两个字符串 `s` 和 `t` ，统计并返回在 `s` 的 **子序列** 中 `t` 出现的个数，结果需要对 10(9) + 7 取模。

> 示例 1：
>
> ```Plaintext
> 输入：s = "rabbbit", t = "rabbit"输出：3
> 解释：
> 如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
> rabbbit
> rabbbit
> rabbbit
> ```
>
> 示例 2：
>
> ```Plaintext
> 输入：s = "babgbag", t = "bag"
> 输出：5
> 解释：
> 如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。 
> babgbag
> babgbag
> babgbag
> babgbag
> babgbag
> ```

### 思路

没做出来这个题，第一次做基本没有什么想法。

首先明确**dp数组的含义**，dp[i][j] = k表示s字符串的0~i-1部分包含k个t字符串的0~j-1部分。所以最终返回dp的最后一个元素的值就是答案。

**那么****dp****数组怎么递推？**

这一类问题，基本是要分析两种情况

- s[i - 1] 与 t[j - 1]相等
- s[i - 1] 与 t[j - 1] 不相等

当s[i - 1] 与 t[j - 1]相等时，dp[i][j]可以**有两部分**组成。

一部分是用s[i - 1]来匹配，那么个数为dp[i - 1][j - 1]。即不需要考虑当前s子串和t子串的最后一位字母，所以只需要 dp[i-1][j-1]。

如果二者相等了，不需要在dp[i - 1][j - 1]加一，因为现在dp数组的含义不是说相同子串的长度，而是有几种构成方式。所以如果此时末尾相同，那构成方式的个数就和没有这一位时是一样的，也就是dp[i - 1][j - 1]；

不容易想到的就是不用s[i - 1]来匹配，个数为dp[i - 1][j]。为什么还要考虑不用s[i - 1]来匹配？

例如s：bagg和t：bag ，s[3]和t[2]是相同的，但是字符串s也可以不用s[3]来匹配，即用s[0]s[1]s[2]组成的bag。

当然也可以用s[3]来匹配，即：s[0]s[1]s[3]组成的bag。

所以dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]；

当s[i - 1]与t[j - 1]不相等时，dp[i][j]只有一部分组成，不用s[i - 1]来匹配（就是模拟在s中删除这个元素），即：dp[i - 1][j]，所以递推公式为：dp[i][j] = dp[i - 1][j];

为什么只考虑 “不用s[i - 1]来匹配” 这种情况， 不考虑 “不用t[j - 1]来匹配” 的情况呢？

我们求的是s 中有多少个t，而不是求t中有多少个s，所以只考虑s中删除元素的情况，即不用s[i - 1]来匹配的情况。

**dp****数组如何初始化？**

从递推公式dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; 和 dp[i][j] = dp[i - 1][j]; 中可以看出dp[i][j] 是从上方和左上方推导而来，如图，那么 dp[i][0] 和dp[0][j]是一定要初始化的。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OWQxNDU3OWMyZjI4YzBkM2RmNTM2ZjIwZTljOGVlZDlfbENHVHp3dUdjUE1hTXl2eE13TVpKVGJTM25INTJReTJfVG9rZW46Qk9vZGJMRWdNb1BnRml4WTFCVWNacW05bmRiXzE3MTA1MDM1NzU6MTcxMDUwNzE3NV9WNA)

每次当初始化的时候，都要回顾一下dp[i][j]的定义，不要凭感觉初始化。

dp[i][0]表示什么呢？

dp[i][0] 表示：以i-1为结尾的s可以随便删除元素，出现空字符串的个数。

那么dp[i][0]一定都是1，因为也就是把以i-1为结尾的s，删除所有元素，出现空字符串的个数就是1。

再来看dp[0][j]，dp[0][j]：空字符串s可以随便删除元素，出现以j-1为结尾的字符串t的个数。

那么dp[0][j]一定都是0，s无论如何也变成不了t。

最后就要看一个特殊位置了，即：dp[0][0] 应该是多少。

dp[0][0]应该是1，空字符串s，可以删除0个元素，变成空字符串t。

**确定遍历顺序**

从递推公式dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; 和 dp[i][j] = dp[i - 1][j]; 中可以看出dp[i][j]都是根据左上方和正上方推出来的。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NGE5M2MxMmNkNDFkYzgzODRiZDI2NDY4YmU3YjhiMGJfc0gxSGZJQW5zZjNxek82WkRpbDRGVXhFYmhqaGFqQzJfVG9rZW46WHNDb2J1bHJMb1EzbWN4VUg2S2NsZXphbkxjXzE3MTA1MDM1NzU6MTcxMDUwNzE3NV9WNA)

### 代码

```C++
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1, 0));
        for (int i = 0; i < s.size() + 1; i++) {
            dp[i][0] = 1;
        } 
        for (int i = 1; i < s.size() + 1; i++) {
            for (int j = 1; j < t.size() + 1; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n * m).

空间复杂度：空间复杂度为O(n * m).