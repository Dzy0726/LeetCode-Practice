# 代码随想录算法训练营第六十天| 动态规划 Part17

## 今日题目

647.[回文子串](https://leetcode.cn/problems/palindromic-substrings/)

516.[最长回文子序列](https://leetcode.cn/problems/longest-palindromic-subsequence/)

## LeetCode 647.回文子串

### 题目

给你一个字符串 `s` ，请你统计并返回这个字符串中 **回文子串** 的数目。

**回文字符串** 是正着读和倒过来读一样的字符串。

**子字符串** 是字符串中的由连续字符组成的一个序列。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

> 示例 1：
>
> 输入：s = "abc" 输出：3 解释：三个回文子串: "a", "b", "c"
>
> 示例 2：
>
> 输入：s = "aaa" 输出：6 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

### 思路

之前的dp数组都是题目要求什么，就让dp数组的含义是什么，然后一步步找到递推公式。但是这道题如果是让dp[i]表示0-i子串中回文子串的数目，找不到递推公式，到了每个新的位置i都得判断好几个子串。

考虑到对于一个字符串是不是回文串，从中间开始向两边，两两比较，如果相等就是回文字符串。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=M2Q5YzZlOWUxYjkwODdlZDM2MjA2M2YzZmZhZTNlMTVfSVN0bXZBZEVGRUU5VlBKU3ZjcUo5d1Z3b001RVhWVFZfVG9rZW46SjRGTWJ4ZGRkb25Xc3p4TEpPVWNKMENFbmRmXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

我们在判断字符串S是否是回文，那么如果我们知道 s[1]，s[2]，s[3] 这个子串是回文的，那么只需要比较 s[0]和s[4]这两个元素是否相同，如果相同的话，这个字符串s 就是回文串。

那么此时我们是不是能找到一种递归关系，也就是判断一个子字符串（字符串的下表范围[i,j]）是否回文，依赖于，子字符串（下表范围[i + 1, j - 1]）） 是否是回文。

所以为了明确这种递归关系，我们的dp数组是要定义成一位二维dp数组。

布尔类型的dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串，如果是dp[i][j]为true，否则为false。

当s[i]与s[j]不相等，dp[i][j]一定是false。

当s[i]与s[j]相等时，有如下三种情况

- 情况一：下标i 与 j相同，同一个字符例如a，当然是回文子串
- 情况二：下标i 与 j相差为1，例如aa，也是回文子串
- 情况三：下标：i 与 j相差大于1的时候，例如cabac，此时s[i]与s[j]已经相同了，我们看i到j区间是不是回文子串就看aba是不是回文就可以了，那么aba的区间就是 i+1 与 j-1区间，这个区间是不是回文就看dp[i + 1][j - 1]是否为true。

dp数组全部初始化为false。

那么dp数组如何遍历？

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Nzk5N2ZkMWUzNDU2YTQ5ZjdlODI4MmUzMmZhYmM4YzhfTkNSOVVSNHVRY0prVTk3bERsUnVucUFteVVmNVFFNkNfVG9rZW46RVUxd2JWcVR0b0UwM0x4YWlTZWN1ZzRFbk1oXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

如果这矩阵是从上到下，从左到右遍历，那么会用到没有计算过的dp[i + 1][j - 1]，也就是根据不确定是不是回文的区间[i+1,j-1]，来判断了[i,j]是不是回文，那结果一定是不对的。所以一定要**从下到上，从左到右遍历**，这样保证dp[i + 1][j - 1]都是经过计算的。

举例，输入："aaa"，dp[i][j]状态如下：

图中有6个true，所以就是有6个回文子串。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGI5ODZhNzFlN2VhMjMwMmEwOGVkMzdkYzA0ZDQ4NWFfY05GV2M1THFKeGYxYlVTSWdic3dib2NSSVMyOE8yanZfVG9rZW46T0xxZmJwbnJJbzZDaGJ4Nm9SYmNsVVF1bkFCXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

注意因为dp[i][j]的定义，所以j一定是大于等于i的，那么在填充dp[i][j]的时候一定是只填充右上半部分。

### 代码

```C++
class Solution {
public:
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    if (j - i < 2) {
                        dp[i][j] = true;
                        result++;
                    } else if (dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                        result++;
                    }
                }
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n^2).

空间复杂度：空间复杂度为O(n^2).

### 学习与小结

回文子串的性质就是对称的，从中间向两边“扩散”，也可以利用这个性质，用双指针来判断，这样可以优化空间复杂度。

## LeetCode 516.最长回文子序列

### 题目

给你一个字符串 `s` ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

> 示例 1：
>
> 输入：s = "bbbab" 输出：4 解释：一个可能的最长回文子序列为 "bbbb" 。
>
> 示例 2：
>
> 输入：s = "cbbd" 输出：2 解释：一个可能的最长回文子序列为 "bb" 。

### 思路

根据上题举一反三，dp数组的含义是i-j子串的最长回文子序列的长度，最终返回dp[0][s.size() - 1]，表示整个字符串的最长回文子序列。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDEyYTczZWU1M2QzYjQzY2MwNWRkMTZmMGI4NjQ3YTdfUVhwUFZaU0tGdkRCOU9UUDFIVTd4QmtzaHR0NjZYZU5fVG9rZW46Vm9yTWI3WVNvb1BnNGl4MzhRa2NtMFpEbnplXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

如果s[i]与s[j]相同，那么dp[i][j] = dp[i + 1][j - 1] + 2;

如果s[i]与s[j]不相同，**说明s[i]和s[j]的同时加入 并不能增加[i,j]区间回文子序列的长度，那么分别加入s[i]、s[j]看看哪一个可以组成最长的回文子序列**。

加入s[j]的回文子序列长度为dp[i + 1][j]。

加入s[i]的回文子序列长度为dp[i][j - 1]。

那么dp[i][j]一定是取最大的，即：dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2RhNWFiODNiOWI3ZjMxMTY2NTE3ZWFlNzI0NDg1OWRfWUd1SFNCNjdCZXdxWUNwYlBHNmwySWtyMWc4YjQ5NGhfVG9rZW46U2N1S2JEQlZab2g1OTd4cHFTWmN3MVFkbnNmXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

初始化时就全部初始化为0。

从递归公式中，可以看出，dp[i][j] 依赖于 dp[i + 1][j - 1] ，dp[i + 1][j] 和 dp[i][j - 1]，如图：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MmEyZjJlNzgzMTk4MmRkNTgyNjdjMzQ3MDhjMjZlMmFfeWlxdXVGdW5JN2psYWQ5ajFQNXRsNDdaTFdaZ0FaeDNfVG9rZW46TEQ5TGJpM1RFb01yYkR4YlM5M2NzWTBWblBlXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

所以遍历i的时候一定要从下到上遍历，这样才能保证下一行的数据是经过计算的。

j的话，可以正常从左向右遍历。

输入s:"cbbd" 为例，dp数组状态如图：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Yjc4ZjhiMDAzNTZlMDJjNjhhNTU2NzJmYTUyYjhjNTNfSVJKbTNyVDVZeER4emNNcWd6bWQzdjhjd1hiWXpYbHNfVG9rZW46RlA2MWJKeEdVbzFMOVR4ZHdZcGN2cGpnbnViXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)

红色框即：dp[0][s.size() - 1]; 为最终结果。

### 代码

```C++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    if (j - i < 2) {
                        dp[i][j] = j - i + 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n^2).

空间复杂度：空间复杂度为O(n^2).

### 动态规划总结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NzRkZmY0MTcwMjUxMGUxZGRjODM4MzQwYjU1NjM4MzhfeDFKeGxTT0VzQ3JTNTBpYjE2RWhtMzVUajlIeFNqQ0lfVG9rZW46QmtwMWJ2U3pvb1BFTE14a0wyZ2NZV2ZlbmpiXzE3MTA3MjkwNjI6MTcxMDczMjY2Ml9WNA)