# 代码随想录算法训练营第二十五天| 回溯算法 Part02

## 今日题目

216.[组合总和 III](https://leetcode.cn/problems/combination-sum-iii/)

17.[电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/)

## LeetCode 216.组合总和Ⅲ

### 题目

找出所有相加之和为 `n` 的 `k` 个数的组合，且满足下列条件：

- 只使用数字1到9
- 每个数字 **最多使用一次** 

返回 *所有可能的有效组合的列表* 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。

> 输入: *k* = 3, *n* = 9 输出: [[1,2,6], [1,3,5], [2,3,4]] 解释: 1 + 2 + 6 = 9 1 + 3 + 5 = 9 2 + 3 + 4 = 9 没有其他符合的组合了。

### 思路

用全局变量result记录最终的结果，path记录当前的路径，sum记录当前的路径和。

1. 参数及返回类型：参数传入k，n，和当前开始的位置，返回值为空，因为要遍历整个树；
2. 终止条件：path大小为k终止
3. 单层逻辑：每次将当前i加入path，并将值加入sum，递归，回溯。

想了半天没想出怎么剪枝……

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void findSum(int k, int n, int start) {
        if (path.size() == k) {
            if (sum == n) {
                result.push_back(path);
            }
            return;
        }
        for (int i = start; i <= 9; i++) {
            sum += i;
            path.push_back(i);
            findSum(k, n, i + 1);
            path.pop_back();
            sum -= i;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        findSum(k, n, 1);
        return result;
    }
};
```

### 学习与小结

剪枝其实可以想到，当sum已经大于n时，可以剪去后面多余的操作，因为后面的i比当前更大。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTE3OGU2N2EyNzA5NmZiYzZmOGYwODg3ZGRlNzkzY2FfTXRLbVh2TlRhUXN3cnRLbTVRQ21aZ0pLVVpVbGZqUTZfVG9rZW46QzAwbGJNQkxhbzlSTm14UEJHV2M3Ym95bkdkXzE3MDU3MjEwMTk6MTcwNTcyNDYxOV9WNA)

比如已经找到了1，3，当i++变为4，sum = 1 + 4 = 5 > 4，所以可以跳出这个循环，后面的5，6，7，8，9就都不用看了，肯定比当前更大。

昨天77题的剪枝也可以在本题使用，当前剩下的数已经不够k个了：

现在已经用了几个数：path.size()

还剩几个：9 - i + 1（9是我们本题数组的大小，1-9）

判断够不够k个：9 - i + 1 + path.size() >= k 就够

综上所述，剪枝如下：

```C++
class Solution {
private:
    vector<vector<int>> result; // 存放结果集
    vector<int> path; // 符合条件的结果
    void backtracking(int targetSum, int k, int sum, int startIndex) {
        if (sum > targetSum) { // 剪枝操作
            return; 
        }
        if (path.size() == k) {
            if (sum == targetSum) result.push_back(path);
            return; // 如果path.size() == k 但sum != targetSum 直接返回
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { // 剪枝
            sum += i; // 处理
            path.push_back(i); // 处理
            backtracking(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
            sum -= i; // 回溯
            path.pop_back(); // 回溯
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(n, k, 0, 1);
        return result;
    }
};
```

这道题其实一开始没注意到我们数组的大小是9，只能从9个数中选。将n设置成了遍历的边界，导致超时。

## LeetCode 17.电话号码的字母组合

### 题目

给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。答案可以按 **任意顺序** 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MWNiM2VlOWE0NmYxZmNiYTE4ODRiMGVlNjEzMWNkYTlfOU1RWlBtUFhWYnI4OXpWakdaNXM1dVl5V09MbnhmWHBfVG9rZW46QmVtZmJzZVdmb3ZLN2p4VTF4WWNRWmw0bm9nXzE3MDU3MjEwMTk6MTcwNTcyNDYxOV9WNA)

> 输入：digits = "23" 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

### 思路

首先用map来存数字和字母的映射，key为string，value为string数组。

用result存放结果，path存放当前的暂时路径。

我想的是这样的一棵树：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGFhOGViODNmNGIxZTY4Mzc1NGJmYTcwZTU5ZTU4YTZfdWk3dlp6N0JpWG9wNEY2UUZYczBpNmNXRUdzb2haTHFfVG9rZW46R2NaaGJkZnhvb1g3Sm54VmxuVGNuR1RTblFmXzE3MDU3MjEwMTk6MTcwNTcyNDYxOV9WNA)

1. 参数及返回类型：传入原始的数组和指示位置；这个**index**是记录遍历第几个数字了，就是用来遍历digits的（题目中给出数字字符串），同时index也表示树的深度。
2. 终止条件：path的大小和digits大小相同，说明每个号码都取了对应字母之一加入到了path中；
3. 单层逻辑：先在map找到一个key（比如上图的2、3、4），然后遍历它的value数组（比如2对应的a,b,c），遍历数组时，先将数组的一个元素append到path，然后递归遍历，将指向digits的位置加1，方便找到下一个数字，之后回溯。

> 首先要取index指向的数字，并找到对应的字符集（手机键盘的字符集）。
>
> 然后for循环来处理这个字符集

语言能力好匮乏哈哈，不知道怎么表达自己想的东西，来看看卡哥的图和解释：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NGUyMWEyYWI2NTQ4MGU4YjczZDk3ODlmN2IwYjFiNjFfZ0tGUGh6WkJ0aFIxWGttemRaVjl3dWJzYVVSQjBXcThfVG9rZW46U2FxUWJnQTFhbzVyeUt4WTA5aWNRSU9pbnloXzE3MDU3MjEwMTk6MTcwNTcyNDYxOV9WNA)

这里和之前两题不同的点在于，之前数组是公用的，都是从1-n中选出数字，而这道题，每个数字对应的字母数组不同。回到数学上看，之前是从一个集合中选出k个不同的数字，一般有$$C_{n}^{k} $$种情况；而这道题要在n个集合中，选出n个数字，每个集合的大小是3或4，比如示例中的digits = 23，有$$C_{3}^{1} * C_{3}^{1}$$种情况。

### 代码

```C++
class Solution {
public:
    vector<string> result;
    string path;
    unordered_map <string, vector<string>> myMap = {
        {"2", {"a", "b", "c"}},
        {"3", {"d", "e", "f"}},
        {"4", {"g", "h", "i"}},
        {"5", {"j", "k", "l"}},
        {"6", {"m", "n", "o"}},
        {"7", {"p", "q", "r", "s"}},
        {"8", {"t", "u", "v"}},
        {"9", {"w", "x", "y", "z"}},
    };
    void backTracking(string digits, int start) {
        if (path.size() == digits.size()) {
            result.push_back(path);
            return;
        }
        auto it = myMap.find(string(1,digits[start]));
        for (int i = 0; i < it ->second.size(); i++) {
            path.append(it -> second[i]);
            backTracking(digits, start + 1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return result;
        backTracking(digits, 0);
        return result;
    }
};
```

### 时空复杂度

时间复杂度: O(3^m * 4^n)，其中 m 是对应四个字母的数字个数，n 是对应三个字母的数字个数

空间复杂度: O(3^m * 4^n)

- `path` 变量存储了一个中间结果，其空间复杂度为 `O(m+n)`，因为它最长与数字字符串的长度相同。
- `result` 变量存储了所有可能的字母组合，其数量为 `O(3^m + 4^n)`。
- 回溯算法的递归栈空间复杂度为 `O(m+n)`，因为递归的深度等于数字字符串的长度。

综上所述，空间复杂度为`O(3^m + 4^n)`

### 学习与小结

还是很开心这道题可以一下想到正确的思路~由此可以看出画图的重要性！

回溯算法不好一下子把参数、流程想的齐全，可以边写代码边画图，不断完善代码，跑通几个常见的测试用例，再去考虑特殊情况。