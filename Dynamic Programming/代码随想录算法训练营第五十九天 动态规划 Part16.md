# 代码随想录算法训练营第五十九天| 动态规划 Part16

## 今日题目

583.[两个字符串的删除操作](https://leetcode.cn/problems/delete-operation-for-two-strings/)

72.[编辑距离](https://leetcode.cn/problems/edit-distance/)

## LeetCode 583.两个字符串的删除操作

### 题目

给定两个单词 `word1` 和 `word2` ，返回使得 `word1` 和  `word2` **相同**所需的**最小步数**。

**每步** 可以删除任意一个字符串中的一个字符。

> 示例 1：
>
> 输入: word1 = "sea", word2 = "eat" 输出: 2 解释: 第一步将 "sea" 变为 "ea" ，第二步将 "eat "变为 "ea"
>
> 示例  2:
>
> 输入：word1 = "leetcode", word2 = "etco" 输出：4

### 思路

首先确定dp数组的含义，这里我用的是dp[i][j] = k表示word1的0~i-1部分和word2的0~j-1部分最少要k步才能变成相同的。

递推公式：

首先也是需要判断当前末位是否相同，即word1[i - 1] == word2[j - 1]：

如果相等，那么就说明这一步可以不做处理，即直接选用dp[i - 1][j - 1]，也可以删除其中的一个，比如删除word1或word2的末尾，三个值中选最小值，即dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));

如果末位不相同，那么就是要从不包含末位的状态（dp[i - 1][j - 1]）+2，和单独删一个的状态+1三者比较，取最小值。dp[i][j] = min(dp[i - 1][j - 1] + 2, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));

初始化时按照dp的定义，整个dp数组的第一行和第一列是从0逐个递增，可以理解为要从某个字符串变成空字符串要删几步。

遍历的顺序由递推公式可以看出来是从上到下，从左到右遍历。

以word1:"sea"，word2:"eat"为例，推导dp数组状态图如下：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTFjOWZlMzgwMmVhNjAyMzJjYTYzNmNjYTQyMjE3MzdfSzFDS2JBUFVrQXhBdjA5eGg1VHliaVo0dFVzZUk0UElfVG9rZW46TG84U2I5Q2I1b0ZjMFh4a2tyc2NBNWFEbndiXzE3MTA1MDc2MjU6MTcxMDUxMTIyNV9WNA)

### 代码

```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i < word1.size() + 1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i < word2.size() + 1; i++) {
            dp[0][i] = i;
        }

        for (int i = 1; i < word1.size() + 1; i++) {
            for (int j = 1; j < word2.size() + 1; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1] + 2, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n * m).

空间复杂度：空间复杂度为O(n * m).

### 学习与小结

本题和[动态规划：1143.最长公共子序列 (opens new window)](https://programmercarl.com/1143.最长公共子序列.html)基本相同，只要求出两个字符串的最长公共子序列长度即可，那么除了最长公共子序列之外的字符都是必须删除的，最后用两个字符串的总长度减去两个最长公共子序列的长度就是删除的最少步数。

```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1, 0));
        for (int i=1; i<=word1.size(); i++){
            for (int j=1; j<=word2.size(); j++){
                if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return word1.size()+word2.size()-dp[word1.size()][word2.size()]*2;
    }
};
```

## LeetCode 72.编辑距离

### 题目

给你两个单词 `word1` 和 `word2`， *请返回将* *`word1`* *转换成* *`word2`* *所使用的最少操作数*  。

你可以对一个单词进行如下三种操作：

- 插入一个字符
- 删除一个字符
- 替换一个字符

> 示例 1：
>
> 输入：word1 = "horse", word2 = "ros" 输出：3 解释： horse -> rorse (将 'h' 替换为 'r') rorse -> rose (删除 'r') rose -> ros (删除 'e')
>
> 示例 2：
>
> 输入：word1 = "intention", word2 = "execution" 输出：5 解释： intention -> inention (删除 't') inention -> enention (将 'i' 替换为 'e') enention -> exention (将 'n' 替换为 'x') exention -> exection (将 'n' 替换为 'c') exection -> execution (插入 'u')

### 思路

首先确定dp数组的含义，这里我用的是dp[i][j] = k表示word1的0~i-1部分变成word2的0~j-1部分最少要k步。

递推公式：

首先也是需要判断当前末位是否相同，即word1[i - 1] == word2[j - 1]：

如果相等，那么就说明这一步可以不做处理，即直接选用dp[i - 1][j - 1]，也可以删除当前word1[i-1]，直接用dp[i-1][j]+1，即 dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j] + 1);

如果末位不相同，那么就是要从不包含末位的状态，和单独删一个的状态三者比较，取最小值再+1。                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;

初始化时按照dp的定义，整个dp数组的第一行和第一列是从0逐个递增，可以理解为要从某个字符串变成空字符串要删几步。

遍历的顺序由递推公式可以看出来是从上到下，从左到右遍历。

### 代码

```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i < word1.size() + 1; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j < word2.size() + 1; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i < word1.size() + 1; i++) {
            for (int j = 1; j < word2.size() + 1; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j] + 1);
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n * m).

空间复杂度：空间复杂度为O(n * m).

### 学习与小结

看了题解，发现自己的思路并不是完全正确，在处理递推公式时，**应该按照下面的思路和逻辑来处理**

```Plain
if (word1[i - 1] == word2[j - 1])
    不操作
if (word1[i - 1] != word2[j - 1])
    增
    删
    换
```

`word1[i - 1]` 与 `word2[j - 1]`相等了，那么就不用编辑了，以下标i-2为结尾的字符串word1和以下标j-2为结尾的字符串`word2`的最近编辑距离`dp[i - 1][j - 1]`就是 `dp[i][j]`了。

`if (word1[i - 1] != word2[j - 1])`，此时就需要编辑了，如何编辑呢？

- 操作一：word1删除一个元素，那么就是以下标i - 2为结尾的word1与j-1为结尾的word2的最近编辑距离再加上一个操作。

即 `dp[i][j] = dp[i - 1][j] + 1;`

- 操作二：word1添加一个元素，那么就是以下标i - 1为结尾的word1与j-2为结尾的word2的最近编辑距离再加上一个操作。

即 `dp[i][j] = dp[i][j - 1] + 1;`

word1添加一个元素，相当于word2删除一个元素，例如 `word1 = "a" ，word2 = "ad"`，`word1`添加元素`'d'` 和 `word2`删除一个元素`'d'`，变成`word1="ad", word2="a"`， 最终的操作数是一样！ dp数组如下图所示意的：

```Plain
            a                         a     d
   +-----+-----+             +-----+-----+-----+
   |  0  |  1  |             |  0  |  1  |  2  |
   +-----+-----+   ===>      +-----+-----+-----+
 a |  1  |  0  |           a |  1  |  0  |  1  |
   +-----+-----+             +-----+-----+-----+
 d |  2  |  1  |
   +-----+-----+
```

操作三：替换元素，`word1`替换`word1[i - 1]`，使其与`word2[j - 1]`相同，此时不用增删加元素。

所以 `dp[i][j] = dp[i - 1][j - 1] + 1;`

综上，当 `if (word1[i - 1] != word2[j - 1])` 时取最小的，即：`dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;`

这样的话瞬间思路就很清晰，状态转移非常清楚。

难点是想明白**word1添加一个元素，相当于word2删除一个元素，他们的操作数是一样的。**

以示例1为例，输入：`word1 = "horse", word2 = "ros"`为例，dp矩阵状态图如下：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NWRmMDEzNzJmYTJmY2EwMmExYzgxYzcxMzUwNWE0ZjhfUXhwUHBXdksyeHZObzZUbHZ2R1JrRm9RWGZoczBlZFNfVG9rZW46UGR5RmJKNEZVbzhtWDJ4OGVFVWNva3p0bnplXzE3MTA1MDc2MjU6MTcxMDUxMTIyNV9WNA)

```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```