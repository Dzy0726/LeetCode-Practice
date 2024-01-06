# 代码随想录算法训练营第十一天| 栈与队列 Part02

## 今日题目

20.[有效的括号](https://leetcode.cn/problems/valid-parentheses/)

1047.[删除字符串中的所有相邻重复项](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/)

150.[逆波兰表达式求值](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)

## LeetCode 20.有效的括号

### 题目

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

> 示例 1：
>
> 输入：s = "()" 输出：true
>
> 示例 2：
>
> 输入：s = "()[]{}" 输出：true
>
> 示例 3：
>
> 输入：s = "(]" 输出：false

### 思路

这道题主要考察栈的应用，思路比较简单，遍历字符串，碰到左括号就入栈，碰到右括号就检查栈顶元素是否与当前右括号匹配，如果不匹配就返回false，匹配就将栈顶元素出栈，继续遍历。

### 代码

```C++
class Solution {
public:
    bool isValid(string s) {
        stack <char> bracket;
        unordered_map<char, char> map = {
        {'}', '{'},
        {']', '['},
        {')', '('}
    };
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                bracket.push(s[i]);
            } else {
                if (bracket.empty()) {
                    return false;
                }
                if (map[s[i]] != bracket.top()) {
                    return false;
                } else {
                    bracket.pop();
                }               
            }
        }
        if (!bracket.empty()) {
            return false;
        }
        return true;
    }
};
```

### 时空复杂度

时间复杂度：遍历一次字符串，时间复杂度为O(n).

空间复杂度：新建了一个栈，最坏情况全部是左括号，此时栈的长度为字符串长度，所以空间复杂度为O(n).

### 学习与小结

1. C++中map的自定义：不可以用冒号，要用逗号和单引号：

   1. ```C++
      unordered_map<char, char> map = {
              {'}', '{'},
              {']', '['},
              {')', '('}
       };
      ```

2. 注意一些特殊情况的处理，如用例：

   1. s = "[";

      s = "]";

      s = "){";

   2. 第一种情况需要处理遍历完字符串后，栈仍然不为空，说明有括号没有匹配，返回false；

   3. 第二种情况需要处理遍历字符串时，遇到右括号但此时栈为空，说明该括号无法匹配，返回false；

3. **在写题之前应该想清楚上述的三种情况，左括号多余，右括号多余，括号不匹配，这样写代码才有的放矢，而不是杂乱无章。**

4. 根据卡哥的讲解，另一种思路是遇到左括号，将其对应的右括号入栈，遇到右括号只要看此时栈顶是否与该右括号相同即可。这样可以省去map的使用。

   1. ```C++
      class Solution {
      public:
          bool isValid(string s) {
              if (s.size() % 2 != 0) return false; // 如果s的长度为奇数，一定不符合要求
              stack<char> st;
              for (int i = 0; i < s.size(); i++) {
                  if (s[i] == '(') st.push(')');
                  else if (s[i] == '{') st.push('}');
                  else if (s[i] == '[') st.push(']');
                  // 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
                  // 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
                  else if (st.empty() || st.top() != s[i]) return false;
                  else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
              }
              // 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
              return st.empty();
          }
      };
      ```

## LeetCode 1047.删除字符串中所有相邻重复项

### 题目

给出由小写字母组成的字符串 `S`，**重复项删除操作**会选择两个相邻且相同的字母，并删除它们。

在 S 上反复执行重复项删除操作，直到无法继续删除。

在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。

> 示例：
>
> 输入："abbaca" 输出："ca" 解释： 例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。

### 思路

第一次思路是递归调用一个函数，这个函数每次将相邻的相同字符删除，直至不能删除。但是很快反应过来今天是“栈和队列”！所以马上想到栈的使用，只要当前元素和栈顶元素相同就把栈顶元素删除，这样只需要一次遍历即可。

### 代码

```C++
class Solution {
public:
    string removeDuplicates(string s) {
        stack <char> st;
        for (int i = 0; i < s.size(); i++) {
            if (st.empty()) {
                st.push(s[i]);
            } else {
                if (s[i] == st.top()) {
                    st.pop();
                } else {
                    st.push(s[i]);
                }
            }
        }
        string res;
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

### 时空复杂度

时间复杂度：遍历了一次字符串，时间复杂度为O(n).

空间复杂度：新建了栈存放字符串的每个字符，最坏情况下其长度为字符串的长度，所以空间复杂度为O(n).

### 学习与小结

从代码随想录看到了第二种解法：直接用字符串当栈，这样可以省去最后栈转为字符串再逆置的操作，空间复杂度也会降低为O(1).

```C++
class Solution {
public:
    string removeDuplicates(string S) {
        string result;
        for(char s : S) {
            if(result.empty() || result.back() != s) {
                result.push_back(s);
            }
            else {
                result.pop_back();
            }
        }
        return result;
    }
};
```

这里使用了back()函数判断最后一位的值，pop_back()函数删除最后的值，这些都是string的用法，要熟练掌握，熟悉使用方式。

1. reverse

   1.  std::reverse 不是 std::string 的成员函数，而是 <algorithm> 库中的函数。它可以用来反转任何容器的元素顺序。

   2. ```C++
      std::string str = "example";
      std::reverse(str.begin(), str.end()); // 反转字符串
      ```

2. pop_back

   1.  pop_back 成员函数用于移除 std::string 对象末尾的字符。这个操作会减少字符串的长度。

   2. ```C++
      std::string str = "example";
      str.pop_back(); // 移除末尾字符，str 变为 "exampl"
      ```

3. back

   1.  back 成员函数用于访问 std::string 对象末尾的字符，但不移除它。这个函数返回的是对最后一个字符的引用。

   2. ```C++
      std::string str = "example";
      char lastChar = str.back(); // 获取末尾字符，lastChar 为 'e'
      std::cout << lastChar << std::endl;
      ```

4. size 和 length

size() 和 length() 函数返回字符串中字符的数量。

```C++
std::string str = "example";
std::cout << str.size();    // 输出: 7
std::cout << str.length();  // 输出: 7
```

1. empty

empty() 函数检查字符串是否为空（长度为 0）。

```C++
std::string str = "";
std::cout << str.empty();  // 输出: 1 (true)
```

1. append 和 +=

append() 函数或者使用 += 运算符可以将字符或字符串附加到现有字符串的末尾。

```C++
std::string str = "ex";
str.append("ample"); // str 现在为 "example"
str += "!";         // str 现在为 "example!"
```

1. substr

substr() 函数用于获取字符串的子字符串。

```C++
std::string str = "example";
std::string sub = str.substr(2, 4); // 从索引 2 开始获取长度为 4 的子字符串，sub 为 "ampl"
```

1. find

find() 函数用于在字符串中查找子字符串或字符的位置。

```C++
std::string str = "example";
size_t pos = str.find("am"); // pos 为 "am" 开始的索引，即 2
```

1. replace

replace() 函数用于替换字符串中的某个部分。

```C++
std::string str = "example";
str.replace(2, 2, "AM"); // 替换从索引 2 开始的长度为 2 的部分，str 变为 "exAMple"
```

1. erase

erase() 函数用于移除字符串中的字符。

```C++
std::string str = "example";
str.erase(1, 3); // 从索引 1 开始移除长度为 3 的部分，str 变为 "eple"
```

1. c_str

返回一个指向以空字符终止的字符数组的指针，该数组包含与字符串对象相同的序列。

```C++
std::string str = "example";
const char* cstr = str.c_str();
```

1. data

返回一个指针，指向字符串的第一个字符。这个方法类似于 c_str，但是返回的数组可能不是以空字符终止的。

```C++
std::string str = "example";
const char* data = str.data();
```

1. front

返回对字符串的第一个字符的引用。

```C++
std::string str = "example";
char& firstChar = str.front();
```

1. insert

插入字符或字符串到当前字符串的指定位置。

```C++
std::string str = "ample";
str.insert(0, "ex"); // str 现在是 "example"
```

1. compare

比较当前字符串和其他字符串。

```C++
std::string str1 = "hello";
std::string str2 = "world";
int result = str1.compare(str2); // result < 0, 因为 "hello" 小于 "world"
```

1. clear

清除字符串内容，使其变为空字符串。

```C++
std::string str = "example";
str.clear(); // str 现在是 ""
```

1. resize

改变字符串的长度，可以增加或者减少字符数量。

```C++
std::string str = "example";
str.resize(4); // str 现在是 "exam"
```

1. swap

交换两个字符串的内容。

```C++
std::string str1 = "hello";
std::string str2 = "world";
str1.swap(str2); // str1 现在是 "world", str2 现在是 "hello"
```

1. begin / end

返回一个迭代器，分别指向字符串的开始和结束。

```C++
std::string str = "example";
for (auto it = str.begin(); it != str.end(); ++it) {
    // 迭代字符串
}
```

1. rbegin / rend

返回一个反向迭代器，分别指向字符串的末尾和开头。

```C++
std::string str = "example";
for (auto it = str.rbegin(); it != str.rend(); ++it) {
    // 反向迭代字符串
}
```

1. operator[]

提供对指定位置字符的访问。

```C++
std::string str = "example";
char e = str[1]; // e 现在是 'x'
```

1. at

与 operator[] 类似，但是 at 方法提供边界检查，如果索引超出范围，会抛出一个 std::out_of_range 异常。

```C++
std::string str = "example";
char e = str.at(1); // e 现在是 'x'
```

## LeetCode 150. 逆波兰表达式求值

### 题目

给你一个字符串数组 `tokens` ，表示一个根据 [逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437) 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

**注意：**

- 有效的算符为 `'+'`、`'-'`、`'*'` 和 `'/'` 。
- 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
- 两个整数之间的除法总是 **向零截断** 。
- 表达式中不含除零运算。
- 输入是一个根据逆波兰表示法表示的算术表达式。
- 答案及所有中间计算结果可以用 **32 位** 整数表示。

> 示例 1：
>
> 输入：tokens = ["2","1","+","3","*"] 输出：9 解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
>
> 示例 2：
>
> 输入：tokens = ["4","13","5","/","+"] 输出：6 解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
>
> 示例 3：
>
> 输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"] 输出：22 解释：该算式转化为常见的中缀算术表达式为：  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5 = ((10 * (6 / (12 * -11))) + 17) + 5 = ((10 * (6 / -132)) + 17) + 5 = ((10 * 0) + 17) + 5 = (0 + 17) + 5 = 17 + 5 = 22

### 思路

经典的栈的应用题目，思路非常简单，遇到数字就压入数字栈，遇到字符就从数字栈中取出两个数字，先取出的数为右操作数，后取出的数为左操作数，进行对应的运算后再将结果压入栈中。最后返回栈顶元素。本题的用例比较有人情味，所以没有处理除以0、字符数组前两个元素为运算符等异常情况。

### 代码

```C++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
                tokens[i] == "/") {
                int right = nums.top(); // 取出第一个数
                nums.pop();
                int left = nums.top(); // 取出第二个数
                nums.pop();
                if (tokens[i] == "+") {
                    nums.push(left + right);
                } else if (tokens[i] == "-") {
                    nums.push(left - right);
                } else if (tokens[i] == "*") {
                    nums.push(left * right);
                } else {
                    nums.push(left / right);
                }
            } else {
                nums.push(std::stoi(tokens[i]));
            }
        }
        return nums.top();
    }
};
```

### 时空复杂度

时间复杂度：遍历了字符串数组，时间复杂度为O(n).

空间复杂度：新建了数字栈，所以空间复杂度为O(n).