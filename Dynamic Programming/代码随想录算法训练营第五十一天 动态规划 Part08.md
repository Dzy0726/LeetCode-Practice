# 代码随想录算法训练营第五十一天| 动态规划 Part08

## 今日题目

139.[单词拆分](https://leetcode.cn/problems/word-break/)

## LeetCode 139.单词拆分

### 题目

给你一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 `s` 则返回 `true`。

**注意：**不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

> 示例 1：
>
> 输入: s = "leetcode", wordDict = ["leet", "code"] 输出: true 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
>
> 示例 2：
>
> 输入: s = "applepenapple", wordDict = ["apple", "pen"] 输出: true 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。     注意，你可以重复使用字典中的单词。
>
> 示例 3：
>
> 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"] 输出: false

### 思路

判断出可以用完全背包来做，想到了dp的值的含义是true or false，即之前的组成部分是否满足条件，但是没有想出来怎么去检验s。

一般的背包问题，i会作为背包物品的下标，j会作为背包的容量等限制。

这个题背包的物品：单词存放在vector中，可以无限次使用。

主要思想是切割字符串s，生成不同的子串，看子串是否在wordDict中出现过，如果出现过，且这个子串之前的部分也出现过，就把这个位置标记为true；表示这么切割到目前有解，否则标记为false。

所以i，j用来切割字符串s，j作为起始位置，i作为子串终止位置，s.substr(j, i-j)就是子串sub，然后再看sub是否在wordDict中。

所以可以把wordDict转化为一个哈希表，便于查找。

1. 确定dp数组以及下标的含义

dp[i] : dp[i]为true，表示s.substr(0,i)可以拆分为一个或多个在字典中出现的单词。

1. 确定递推公式

如果确定dp[j] 是true，且 [j, i] 这个区间的子串出现在字典里，那么dp[i]一定是true。（j < i ）。

dp[j]=true说明[0,j]这个区间里的子串可以拆分成一个或多个在字典中出现的单词，加上[j, i] 这个区间的子串出现在字典里，所以dp[i]为true。

所以递推公式是 if([j, i] 这个区间的子串出现在字典里 && dp[j]是true) 那么 dp[i] = true。

1. dp数组如何初始化

从递推公式中可以看出，dp[i] 的状态依靠 dp[j]是否为true，那么dp[0]就是递推的根基，dp[0]一定要为true，否则递推下去后面都都是false了。

1. **确定遍历顺序**

题目中说是拆分为一个或多个在字典中出现的单词，所以这是完全背包。

还要讨论两层for循环的前后顺序。

如果求组合数就是外层for循环遍历物品，内层for遍历背包。

如果求排列数就是外层for遍历背包，内层for循环遍历物品。

而本题其实我们求的是排列数，为什么呢。 拿 s = "applepenapple", wordDict = ["apple", "pen"] 举例。

"apple", "pen" 是物品，那么我们要求 物品的组合一定是 "apple" + "pen" + "apple" 才能组成 "applepenapple"。

"apple" + "apple" + "pen" 或者 "pen" + "apple" + "apple" 是不可以的，那么我们就是强调物品之间顺序。

所以说，本题一定是 先遍历 背包，再遍历物品。

1. 举例推导dp[i]

以输入: s = "leetcode", wordDict = ["leet", "code"]为例，dp状态如图：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2IyMWJhZTliMWI5ZmUxYzZhZjYyNzZiZjE3MjBiMDNfYlZHQzFnQ1dQQlprOVlYcFNOTVFGTHNmbmdTZ3RDS3pfVG9rZW46RjFqS2JXQkNlbzhCMFN4a2VUN2M0c0ZJbmljXzE3MDk3OTA0NjQ6MTcwOTc5NDA2NF9WNA)

### 代码

```C++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> word(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i < s.length() + 1; i++) {
            for (int j = 0; j < i; j++) {
                string sub = s.substr(j, i - j);
                if (word.find(sub) != word.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.length()];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n^3)，因为substr返回子串的副本是O(n)的复杂度（这里的n是substring的长度）

空间复杂度：空间复杂度为O(n).

### 学习与小结

关于遍历顺序，说明为什么先遍历物品不行：

使用用例：s = "applepenapple", wordDict = ["apple", "pen"]，对应的dp数组状态如下：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YzQ2YWU4OTlkMjNjZTg5NmYxNzk3MWM0YmFhOTYxMDJfTFFhRk1SR1BhOHNJYnVGa0lTMjdDWVlkMkRqMkRXUWRfVG9rZW46S1ZJN2JnMnJKb2duWkJ4WHZhZGNnTHVlbmpoXzE3MDk3OTA0NjQ6MTcwOTc5NDA2NF9WNA)

最后dp[s.size()] = 0 即 dp[13] = 0 ，而不是1，因为先用 "apple" 去遍历的时候，dp[8]并没有被赋值为1 （还没用"pen"），所以 dp[13]也不能变成1。

除非是先用 "apple" 遍历一遍，再用 "pen" 遍历，此时 dp[8]已经是1，**最后再用 "apple" 去遍历**，dp[13]才能是1。

而正常的先物品后背包的流程是apple遍历一次，pen遍历一次就结束了。