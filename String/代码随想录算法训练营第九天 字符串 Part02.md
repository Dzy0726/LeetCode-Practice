# 代码随想录算法训练营第九天| 字符串 Part02

## 今日题目

28.[找出字符串中第一个匹配项的下标](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)

459.[重复的子字符串](https://leetcode.cn/problems/repeated-substring-pattern/)

## LeetCode 28.找出字符串中第一个匹配项的下标

### 题目

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串的第一个匹配项的下标（下标从 0 开始）。如果 `needle` 不是 `haystack` 的一部分，则返回  `-1` 。

**示例 1：**

**输入：**haystack = "sadbutsad", needle = "sad" **输出：**0 **解释：**"sad" 在下标 0 和 6 处匹配。 第一个匹配项的下标是 0 ，所以返回 0 。

**示例 2：**

**输入：**haystack = "leetcode", needle = "leeto" **输出：**-1 **解释：**"leeto" 没有在 "leetcode" 中出现，所以返回 -1 。

### 思路

KMP算法还是来了，鉴于它的威名，我给它三分薄面，先学再做避免浪费太多时间。

为什么会有KMP算法呢？考虑这道题的暴力解法，用两层循环一一比较两个字符串的每个字符是否相等，这样的话最坏情况下的时间复杂度是O(m*n)，m和n分别为两个字串的长度。而且，像heystack = abcdacbxabcd，needle = abcdabcd这组，当匹配到最后needle最后一位时，发现x和d不匹配，按照暴力解法就需要再heystack中回溯到第一个b，在needle中回溯到第一个a，即在heystack中，i从7回溯到1，在needle中j从7回溯到0。但是观察发现，在x与d匹配失败之前，x的前三位是abc，needle开头的三位也是abc，如果可以直接让x与needle中j=3的d比较，是不是就省去了heystack中的回溯？于是就有了KMP算法。

KMP算法的关键是next数组，或者说在匹配失败时，如何确定heystack不回溯的情况下，needle回溯到哪一位来和当前heystack的这位来进行匹配。这就要看needle中是否有既是前缀又是后缀的部分，比如abcdabc这个子串，显然abc就既是该串的前缀，又是该串的后缀。还是回到刚才的例子，heystack = abcdacbxabcd，needle = abcdabcd，当x与d匹配失败时，x与d之前已经匹配成功abc，而needle中d之前的子串是abcdabc，该串的最长公共前后缀是abc，说明子串的前缀也有abc部分，这就无需再比较，heystack不需要再回溯到开头，直接让x与前缀abc的后一位进行比较即可，可以省去大量的比较次数。

体会到了next数组的优点，那么我们如何用代码得到呢？这感觉是整个KMP算法中最难的一部分。先来一些大佬的理解：

> 每次求next【i】，可看作前缀与后缀的一次匹配，在该过程中就可以用上之前所求的next，若匹配失败，则像模式串与父串匹配一样，将指针移到next【j-1】上。
>
> 求next过程实际上是dp（动态规划），只与前一个状态有关：
>
> 若不匹配，一直往前退到0或匹配为止
>
> 若匹配，则将之前的结果传递：
>
> 因为之前的结果不为0时，前后缀有相等的部分，所以j所指的实际是与当前值相等的前缀，可视为将前缀从前面拖了过来，就不必将指针从前缀开始匹配了，所以之前的结果是可以传递的。

考虑字符串abcdabca，j=0，i=1，next[j]=0，这是next数组的初始情况。现在i和j不匹配（b和a），所以next[1]=0，i++;i=2和j仍然不匹配（c和a），next[2]=0，i++；直到i=4时，此时j=0，next数组前几位全为0，但是i和j匹配了（都是a），next[4]=j++=1，i和j同时加一；这个1代表什么？比如abcdax.....和abcdab......匹配，匹配到x和b(第二个)时匹配失败，但next[5]=1，说明有公共前后缀长度为1，就跳过了a的匹配，直接匹配x和b(第一个)。

i=5，j=1，又匹配，next[5]=j++=2，i和j同时加一；

i=6，j=2，又匹配，next[6]=j++=3，i和j同时加一；

i=7，j=3，不匹配，j返回到next[j-1]=0，然后匹配，所以next[7]=j+1=1.

再来一次：

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| a    | a    | b    | a    | a    | b    | a    | a    | a    |
| 0    | 1    | 0    | 1    | 2    | 3    | 4    | 5    | 2    |

初始：i=1，j=0，next[0]=0，第一次匹配s[i]=s[j]，所以next[i]=j+1=1，i++，j++；

i=2，j=1，s[i]=s[j]，所以j的下一个位置是它前面那个位置的next值，j=next[j-1]=0，然后s[i]=s[j]仍然成立，所以next[2]=0，i++；

i=3，j=0，s[i]=s[j]，next[i]=j+1=1，i++，j++；

i=4，j=1，s[i]=s[j]，next[i]=j+1=2，i++，j++；

i=5，j=2，s[i]=s[j]，next[i]=j+1=3，i++，j++；

i=6，j=3，s[i]=s[j]，next[i]=j+1=4，i++，j++；

i=7，j=4，s[i]=s[j]，next[i]=j+1=5，i++，j++；

i=8，j=5，s[i]!=s[j]，j=next[j-1]=2，s[i]!=s[j]仍然成立，j=next[j-1]=1，s[i]=s[j]，next[i]=j+1=2，结束。

有了next数组，就可以进行文本串和模式串的比较了。文本串不回溯，当匹配失败时，模式串的指针回到当前位置前一个的next数组的值，就是上面提到的：j=next[j-1]。

### 代码

```C++
class Solution {
public:
    void getNext(int *next, string s) {
        int j = 0, i = 1;
        next[0] = 0;
        for (;i < s.size(); i++) {
            while (j > 0 && s[j] != s[i] ) {
                j = next[j - 1];
            }
            if (s[j] == s[i]) {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size()) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
```

### 时空复杂度

时间复杂度：构建next数组的时间复杂度与模式串长度有关，为O(m)，匹配过程时间复杂度与文本串长度有关，为O(n)，所以整体的时间复杂度为O(m+n).

空间复杂度：next数组长度，所以空间复杂度为O(m).

### 学习与小结

next数组有很多种写法，有的是直接按”前一位“写，有的是将原始next数组整体右移一位，看别人的代码时不要混淆。不用代码找next数组还是比较简单，要是写代码的话，先模拟一遍理清思路，再根据模拟的过程慢慢调整代码，直至AC。

## LeetCode 459.重复的子字符串

### 题目

给定一个非空的字符串 `s` ，检查是否可以通过由它的一个子串重复多次构成。

**示例 1:**

**输入:** s = "abab" **输出:** true **解释:** 可由子串 "ab" 重复两次构成。

**示例 2:**

**输入:** s = "aba" **输出:** false

**示例 3:**

**输入:** s = "abcabcabcabc" **输出:** true **解释:** 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)

### 思路

刚做完KMP，分析了以上三个示例，初步思路是求出s的next数组，如果next长度可以整除next数组的最后一个值，那么就说明它符合条件。但其实并不能直接这么做，以示例三为例，next的最后一个值为9而非6，next的值为当前不匹配时返回到哪里开始进行下次匹配，并不能说明最长重复子串的长度。

但是大致思路是可行的：在由重复子串组成的字符串中，最长相等前后缀不包含的子串就是最小重复子串。而最长相等前后缀的值就是不减一版本next数组的最后一个值。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTEwY2UzNWI0MzFkODg0M2E3OTQwZjdjOTk1MWMxZjBfUmpJSEFKWVVBdVVnZzd2aVR5UmVCTDNEeTNuNWhUQ2hfVG9rZW46WTJVcWJVamJSb0h4U3F4aEtjVGNxM3BZbndjXzE3MDQzNDE2ODM6MTcwNDM0NTI4M19WNA)

假设一个字符串由重复元素组成，且重复元素的长度为x，假设重复n次，那么原字符串长度为nx，最长公共前后缀的长度为mx，且有n-m=1.

再加上之前的判断，如果重复元素能被字符串的长度整除，就说明他是由重复元素组成。

### 代码

```C++
class Solution {
public:
    void getNext(int *next, string s) {
        int j = 0, i = 1;
        next[0] = 0;
        for (;i < s.size(); i++) {
            while (j > 0 && s[j] != s[i] ) {
                j = next[j - 1];
            }
            if (s[j] == s[i]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s) {
        int next[s.size()];
        getNext(next, s);
        if ((next[s.size() - 1] > 0) && (s.size() % (s.size() - next[s.size() - 1]) == 0)){
            return true;
        } else {
            return false;
        }
    }
};
```

### 时空复杂度

时间复杂度：构建next数组时间复杂度为O(n).

空间复杂度：构建next数组，所以空间复杂度为O(n).

### 学习与小结

通过代码随想录又学到了一个极为巧妙的解法：如果一个字符串是由重复元素构成的，那么无论它由重复元素构成几次，必定能写成由两个重复元素构成的形式。举例：字符串abababab由4个ab重复构成，它同时也能写成由两个abab重复构成。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NWFkNGI1MmZlNjQ1MTllNGQ4OTIwMDJiMzNjY2UwODRfeTIzSndmdnFkMEJjWGFSMW1SQkpRWjZqVWwwSWphSk1fVG9rZW46WEU4N2JyZm9Qb05BUEZ4T1owSmNzV2RvbjkyXzE3MDQzNDE2ODM6MTcwNDM0NTI4M19WNA)

那么在字符串s后面再接一个s，在中间部分就又会出现一个s，这个s是由第一个s的后半段加上第二个s的前半段组成：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTg5NTg2ZWIwODRlMDlkMWJlMjJmOGIxYjkxNmMzNGZfcWpkV09JOFJZOXhKQXlVY0IwN3V2Vks0MmJkZFlmTzVfVG9rZW46TlVtM2JHWGZBb0tDZzJ4Zkw4VmNWbTlYbmFkXzE3MDQzNDE2ODM6MTcwNDM0NTI4M19WNA)

所以判断思路就有了：只要是s+s中仍然出现了s，就是由重复元素构成的。当前，还需要在拼接后把拼接字符串的首尾元素去掉，防止检测到是原来的s。

```C++
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string t = s + s;
        t.erase(t.begin());
        t.erase(t.end() - 1);
        if (t.find(s) != std::string::npos)  {
            return true; 
        }
        return false;
    }
};
```

在 C++ 中，你可以使用 `std::string` 类的成员函数 `find` 来查找一个子串。这个函数在 `string` 头文件中定义，即 `<string>`。

- `find` 函数返回子串 `to_find` 在 `str` 中首次出现的位置（索引）。
- 如果 `find` 函数没有找到子串，它会返回一个特殊的常量 `std::string::npos`，这表示没有找到匹配的子串。
- 通常情况下，`std::string::find` 函数的时间复杂度可能会是 O(n*m) ，其中 n 是字符串（主字符串）的长度，而 m 是要搜索的子串的长度。