# 代码随想录算法训练营第八天| 字符串 Part01

## 今日题目

344.[反转字符串](https://leetcode.cn/problems/reverse-string/)

541.[反转字符串 II](https://leetcode.cn/problems/reverse-string-ii/)

卡码网54.[替换数字](https://kamacoder.com/problempage.php?pid=1064)

151.[反转字符串中的单词](https://leetcode.cn/problems/reverse-words-in-a-string/)

卡码网55.[右旋字符串](https://kamacoder.com/problempage.php?pid=1065)

## LeetCode 344.反转字符串

### 题目

编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 `s` 的形式给出。

不要给另外的数组分配额外的空间，你必须**[原地](https://baike.baidu.com/item/原地算法)****修改输入数组**、使用 O(1) 的额外空间解决这一问题。

**示例 1：**

**输入：**s = ["h","e","l","l","o"] **输出：**["o","l","l","e","h"]

**示例 2：**

**输入：**s = ["H","a","n","n","a","h"] **输出：**["h","a","n","n","a","H"]

### 思路

题目要求原地逆置，所以直接两两交换数组元素即可。要注意控制i的范围，不然交换了一次又换回来了……直到打印出i和j才发现。

### 代码

```C++
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0; i < s.size()/2; i++) {
            int j = s.size() - 1 - i;
            swap(s[i],s[j]);
        }
    }
};
```

### 时空复杂度

时间复杂度：遍历了一次数组，时间复杂度为O(n).

空间复杂度：原地逆置，所以空间复杂度为O(1).

### 学习与小结

这道题其实就是库函数reverse的实现，EZPZ。

## LeetCode 541. 反转字符串II

### 题目

给定一个字符串 `s` 和一个整数 `k`，从字符串开头算起，每计数至 `2k` 个字符，就反转这 `2k` 字符中的前 `k` 个字符。

- 如果剩余字符少于 `k` 个，则将剩余字符全部反转。
- 如果剩余字符小于 `2k` 但大于或等于 `k` 个，则反转前 `k` 个字符，其余字符保持原样。

**示例 1：**

**输入：**s = "abcdefg", k = 2 **输出：**"bacdfeg"

**示例 2：**

**输入：**s = "abcd", k = 2 **输出：**"bacd"

### 思路

将字符串划分，每隔2k就需要逆置这2k中的前k个字符，所以先看整个字符串需要这样操作几次：`count = length / (2 * k)`，再用i控制每次逆置的范围，将主体部分按要求完成操作，

最后看余数：`comp = length % (2 * k)`在哪个范围，执行对应的操作即可。

`myReverse`作用是不借助库函数实现局部字符串的逆置。

### 代码

```C++
class Solution {
public:
    void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseStr(string s, int k) {
        int length = s.size();
        int count = length / (2 * k);
        int comp = length % (2 * k);
        int i = 0;
        while (i < length && count > 0) {
            myReverse(i, i + k - 1, s);
            count--;
            i += 2 * k;
        }
        if (comp >= k && comp < 2 * k) {
            myReverse(i, i + k - 1, s);
            i += k;
        } else {
            myReverse(i, length - 1, s);
        }
        return s;
    }
};
```

### 时空复杂度

时间复杂度：主体部分逆置了n/2长度的字符串，余数部分最多逆置了k长度的字符串，时间复杂度为O(n).

空间复杂度：涉及的操作都是原地操作，所以空间复杂度为O(1).

### 学习与小结

在处理最后剩余字符时，可以将大于等于k但小于2k的部分与前面逢2k逆置k的部分合并，因为都是要逆置k个数。当i+k不越界时，就逆置k位，然后i向后移动2k；对于不足k的部分单独处理。

```C++
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            // 1. 每隔 2k 个字符的前 k 个字符进行反转
            // 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
            if (i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k );
            } else {
                // 3. 剩余字符少于 k 个，则将剩余字符全部反转。
                reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
};
```

代码非常简洁，但是优化的步骤不容易想到。按照题目分类模拟还是最容易想到的思路。

## 卡码网 54.替换数字

### 题目

###### 题目描述

给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，将字符串中的字母字符保持不变，而将每个数字字符替换为number。 例如，对于输入字符串 "a1b2c3"，函数应该将其转换为 "anumberbnumbercnumber"。

###### 输入描述

输入一个字符串 s,s 仅包含小写字母和数字字符。

###### 输出描述

打印一个新的字符串，其中每个数字字符都被替换为了number

###### 输入示例

a1b2c3

###### 输出示例

anumberbnumbercnumber

### 思路

遍历字符串s，当找到数字就将number追加到新字符串result末尾，不是数字就将当前字符加到result末尾。

### 代码

```C++
#include <iostream>
using namespace std;
int main() {
    string s;
    cin >> s;
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result.append("number");
        } else {
            result.push_back(s[i]);
        }
    }
    cout << result << endl;
    return 0;
}
```

### 时空复杂度

时间复杂度：遍历字符串，时间复杂度为O(n).

空间复杂度：新建一个字符串，空间复杂度为O(n).

### 学习与小结

1. 字符可以直接判断其是否是数字：`s[i] >= '0' && s[i] <= '9'`，不需要使用ASCII。

2. `append` 方法没有直接接受单个字符作为参数的重载版本，添加单个字符到字符串中需要使用`push_back`。

3. 有没有不适用额外空间的方法？

   1. 首先将字符串“扩容”到替换number后的大小：一次遍历统计数字的个数count，再在原来长度的基础上加上`count * 5`，扩容用到的函数：` s.resize(s.size() + count * 5)`；

   2. 又见**双指针**！从后向前遍历字符串，如果遇到不是数字就放到新长度的末尾，是数字就逐一输入number。

   3. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTM3NTJmNTE0OWQxYzM3MjZjNzlhMzA2MzlhNzE5NjhfZUdoNTRjY25LNUdzQzF5eUZYYjVDcDk5Sko2T3YydHlfVG9rZW46Q1pnZ2IyeThHb1VpNmN4aHp1aGN0cWJtbnhoXzE3MDQyNjQyMDA6MTcwNDI2NzgwMF9WNA)

   4. 为什么不从前往后呢？从前往后需要移动的字符显然更多，每次找到数字，要将剩余字符串整体向后移动5位，才能空出一个number的位置，不仅从思路上还是从实现上都更复杂。

      1. ```C++
         #include <iostream>
         
         using namespace std;
         
         int main() {
             string s;
             cin >> s;
             int oldSize = s.size();
             int count = 0;
             for (int i = 0; i < s.size(); i++) {
                 if (s[i] >= '0' && s[i] <= '9') {
                     count++;
                 }
             }
             s.resize(s.size() + count * 5);
             int newSize = s.size();
             for (int i = oldSize - 1, j = newSize - 1; i < j; i--, j--) {
                 if (s[i] < '0' || s[i] > '9') {
                     s[j] = s[i];
                 } else {
                     s[j] = 'r';
                     s[j - 1] = 'e';
                     s[j - 2] = 'b';
                     s[j - 3] = 'm';
                     s[j - 4] = 'u';
                     s[j - 5] = 'n';
                     j -= 5;
                 }
             }
             cout << s << endl;
             return 0;
         }
         ```

## LeetCode 151.反转字符串中的单词

### 题目

给你一个字符串 `s` ，请你反转字符串中 **单词** 的顺序。

**单词** 是由非空格字符组成的字符串。`s` 中使用至少一个空格将字符串中的 **单词** 分隔开。

返回 **单词** 顺序颠倒且 **单词** 之间用单个空格连接的结果字符串。

**注意：**输入字符串 `s`中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

**示例 1：**

**输入：**s = "the sky is blue" **输出：**"blue is sky the"

**示例 2：**

**输入：**s = "  hello world  " **输出：**"world hello" **解释：**反转后的字符串中不能存在前导空格和尾随空格。

**示例 3：**

**输入：**s = "a good   example" **输出：**"example good a" **解释：**如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。

### 思路

没有想到不借助辅助空间的解法，总体思路是倒着遍历字符串，碰到单词将其append到result的末尾。其余的就是关于空格的细节处理。

首先如何确定添加哪几位到result？使用了双指针。倒着遍历时，因为有尾部空格的存在，所以需要找到第一个不为空格的字符，将j固定于此，i继续向前寻找，找到第一个为空格的字符，那么(i+1,j)就是一个要添加的单词。既要让i找到第一个不为空格的位置，又要让i找到第一个为空格的位置，这不是难为i吗？所以引入了一个布尔变量stop，初始为false，表示没有找到单词。当i找到第一个不为空格的位置时，stop改为true，表示现在找到一个单词，i应该去寻找空格啦！

找到单词如何处理？先将找到的这个单词加入到result，再在后面加一个空格，然后将stop改为false，表示i的任务变更为去寻找第一个不为空格的位置（寻找单词的末尾），将j移动到当前i的位置，准备和i一起向前移动，直至找到单词末尾，如此循环。

代码逻辑不够严谨，可以想到的问题：每次加一个单词就在后面添加空格，那么最后一个单词后面仍然有空格，不符合题目“没有尾端空格”的要求，所以在最后加一步去掉尾端空格的处理。

经过调试出现的问题：原字符串是一个非常标准的字符串，没有多余空格和尾端空格，这样在i=0时，不能将最后一个单词加入result，所以增加了判断，如果结束循环时stop==true，表示仍有“未竟的事业”，需要再做一次增加操作。

### 代码

```C++
class Solution {
public:
    string reverseWords(string s) {
        string result;
        int i = s.size() - 1;
        int j = i;
        bool stop = false;
        while (i >= 0) {
            if (s[i] == ' ' && stop == false) {
                i--;
                j--;
            } else if (s[i] == ' ' && stop == true) {
                
                result.append(s, i + 1, j - i);
                result.push_back(' ');
                stop = false;
                i--;
                j = i;
            } else {
                i--;
                stop = true;
            }
        }
        if (stop == 1) {
            result.append(s, i + 1, j - i);
        }
        if (result[result.size() - 1] == ' ') {
            result.resize(result.size() - 1);
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：遍历了字符串，时间复杂度为O(n).

空间复杂度：新建result大小大致与原字符串大小相同，所以空间复杂度为O(n).

### 学习与小结

不小心把这道题做成了水题，还是得想想空间复杂度为O(1)的解法。

代码随想录的讲解中提到的思路在我脑海里一闪而过：

- 移除多余空格
- 将整个字符串反转
- 将每个单词反转

但是卡在了移除多余空格这里。

其实移除多余空格和Day 01中移除元素思路互通，只不过将target设置为“多余空格”。难点在于如何保留两个单词之间的空格？

首先找到不为空的位置，如果现在不是在开头，那么说明已经结束了上一个单词，所以需要加一个空格。下面while循环结束的条件是遇到了空位置，结合起来看就是遇到了空位置不在赋值，上一个单词结束；又找到一个不为空的位置，说明下一个单词应该开始，所以需要加一个空格。

1. 如果 `fastIndex` 指向的字符不是空格，则表示找到了一个单词的开始。
2. 在添加非空格字符之前，如果 `slowIndex` 不为 0，表示之前已经处理了一些字符，需要在单词之间插入一个空格。

```C++
    void removeSpace(string& s) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < s.size(); fastIndex++) {
            if (s[fastIndex] != ' ') {
                if (slowIndex != 0) {
                    s[slowIndex++] = ' ';
                }
                while (fastIndex < s.size() && s[fastIndex] != ' ') {
                    s[slowIndex++] = s[fastIndex++];
                }
            }
        }
        s.resize(slowIndex);
    }
```

其他要注意的是：除了遇到空格要反转当前单词，到达末尾也要反转当前的单词，不然还需要在循环外多一步操作。整体代码如下：

```C++
class Solution {
public:
    void removeSpace(string& s) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < s.size(); fastIndex++) {
            if (s[fastIndex] != ' ') {
                if (slowIndex != 0) {
                    s[slowIndex++] = ' ';
                }
                while (fastIndex < s.size() && s[fastIndex] != ' ') {
                    s[slowIndex++] = s[fastIndex++];
                }
            }
        }
        s.resize(slowIndex);
    }

    void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    string reverseWords(string s) {
        removeSpace(s);
        myReverse(0, s.size() - 1, s);
        int start = 0;
        for (int i = 0; i <= s.size(); i++) {
            if (s[i] == ' ' || i == s.size() ) {
                myReverse(start, i - 1, s);
                start = i + 1;
            }
        }
        return s;
    }
};
```

## 卡码网 55.右旋字符串

### 题目

###### 题目描述

字符串的右旋转操作是把字符串尾部的若干个字符转移到字符串的前面。给定一个字符串 s 和一个正整数 k，请编写一个函数，将字符串中的后面 k 个字符移到字符串的前面，实现字符串的右旋转操作。

例如，对于输入字符串 "abcdefg" 和整数 2，函数应该将其转换为 "fgabcde"。

###### 输入描述

输入共包含两行，第一行为一个正整数 k，代表右旋转的位数。第二行为字符串 s，代表需要旋转的字符串。

###### 输出描述

输出共一行，为进行了右旋转操作后的字符串。

###### 输入示例

2 abcdefg

###### 输出示例

fgabcde

### 思路

思路非常巧妙，但第一做没有想到。

可以将字符串整体先逆置，如abcdefg逆置为gfedcba，然后根据k的值，再分成两个串局部逆置，fg + abcdef，即可完成。

也可以先局部逆置，再整体逆置，结果相同。

### 代码

```C++
#include <iostream>

using namespace std;

void myReverse(int start, int end, string &s) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
int main(){
    int k;
    string s;
    cin >> k;
    cin >> s;
    myReverse(0, s.size() - 1 - k, s);
    myReverse(s.size() - k, s.size() - 1, s);
    myReverse(0, s.size() - 1, s);
    cout << s << endl;
}
```

### 时空复杂度

时间复杂度：

- 总时间复杂度是三次 `myReverse` 调用的时间复杂度之和：
  - 第一次 `myReverse` 调用：O(m)，其中 m 是 `s.size() - 1 - k`。
  - 第二次 `myReverse` 调用：O(k)，其中 k 是需要旋转的字符数量。
  - 第三次 `myReverse` 调用：O(n)，其中 n 是 `s.size()`。
- 因此，总时间复杂度是 O(m) + O(k) + O(n)，由于 m、k 和 n 都与字符串 `s` 的大小线性相关，所以这就简化为 O(n)。

空间复杂度：

- 原串操作，O(1)。

### 学习与小结

左旋右旋是一样的，比较新奇的思路，学习记忆~

先整体逆置再局部逆置是很好的思路，今天的后两道题都用到了这样的思路。

从替换数字可以学到：s.resize、**双指针**的新应用。