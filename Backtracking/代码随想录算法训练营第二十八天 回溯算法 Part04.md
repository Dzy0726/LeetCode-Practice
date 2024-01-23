# 代码随想录算法训练营第二十八天| 回溯算法 Part04

## 今日题目

93.[复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/)

78.[子集](https://leetcode.cn/problems/subsets/)

90.[子集 II](https://leetcode.cn/problems/subsets-ii/)

## LeetCode 93.复原IP地址

### 题目

**有效** **IP** **地址** 正好由四个整数（每个整数位于 `0` 到 `255` 之间组成，且不能含有前导 `0`），整数之间用 `'.'` 分隔。

- 例如：`"0.1.2.201"` 和` "192.168.1.1"` 是 **有效** IP 地址，但是 `"0.011.255.245"`、`"192.168.1.312"` 和 `"192.168@1.1"` 是 **无效** IP 地址。

给定一个只包含数字的字符串 `s` ，用以表示一个 IP 地址，返回所有可能的**有效 IP 地址**，这些地址可以通过在 `s` 中插入 `'.'` 来形成。你 **不能** 重新排序或删除 `s` 中的任何数字。你可以按 **任何** 顺序返回答案。

> 示例 1：
>
> 输入：s = "25525511135" 输出：["255.255.11.135","255.255.111.35"]
>
> 示例 2：
>
> 输入：s = "0000" 输出：["0.0.0.0"]
>
> 示例 3：
>
> 输入：s = "101023" 输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

### 思路

和昨天分割回文串的题目思路相通，分割回文串是在哪里加个切线，并且切线数量不固定；这道题是在哪里加个点（切线），点的数量是固定的，只能是三个，多于少于3都不行。

递归三部曲：

1. 参数及返回值：参数需要传入处理的字符串和for循环递归的起始位置；依然是遍历整个树（所有情况），所以返回值为空；
2. 终止条件：当点已经有三个终止，这个时候来判断第四部分的ip是否合法，如果合法就加入到结果中再返回，不合法直接返回；
3. 单层递归逻辑：这里的处理逻辑是不新建一个path，直接在源字符串上用insert点和erase点来处理。用path不知道何时该插入这个点，很容易插入的点过多，不好控制点的插入和删除；用源字符串就可以想成插入隔板，改变插入隔板的位置；
4. IP地址是否合法：
   1. 开头不能是0，但是可以只有一个0作为一部分：011.1.1.1非法，0.1.1.1合法；
   2. 数字不能大于255；
   3. 不能有除了数字之外的其他字符

### 代码

```C++
class Solution {
public:
    vector<string> result;
    int count = 0;
    bool isValid(const string &s, int start, int end) {
        if (start > end) return false;
        if (s[start] == '0' && start != end) return false;
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') return false;
            num = num * 10 + (s[i] - '0');
            if (num > 255) return false;
        }
        return true;
    }

    void backtracking(string s, int startIndex) {
        if (count == 3) {
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
            }
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                count++;
                backtracking(s, i + 2);
                count--;
                s.erase(s.begin() + i + 1);
            } else {
                break;
            }
        }

    }
    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0);
        return result;
    }
};
```

### 学习与小结

字符串操作：

在指定位置插入：s.insert(要插入的位置, 要插入的字符)

删除指定位置元素：s.erase(要删除的位置)

以上两个位置都必须是迭代器。

## LeetCode 78.子集

### 题目

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

> 示例 1：
>
> 输入：nums = [1,2,3] 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
>
> 示例 2：
>
> 输入：nums = [0] 输出：[[],[0]]

### **思路**

题很好理解，也很好想，每次递归先把新元素加入path，再直接把path加入result，这样遍历整个树的时候，每个节点都会加进去，而不只是叶子节点。

最后要记得添加空集~

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        if (startIndex >= nums.size()) return;

        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        result.push_back(vector<int>());
        return result;
    }
};
```

### 学习与小结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzllMmUxNTY5ZmFmZDIyNmRlMDdiN2FmYjE0MTZiZjlfb2YxdnZDWXB2b2tKakJZOElBZmtQYVNBRW5CWmlVMVdfVG9rZW46RkgzZWJ4YlRib1VEUVp4Q054Z2MwcUNFbmZmXzE3MDYwMTk0MzA6MTcwNjAyMzAzMF9WNA)

要清楚子集问题和组合问题、分割问题的的区别，子集是收集树形结构中树的所有节点的结果。

而组合问题、分割问题是收集树形结构中叶子节点的结果。

## LeetCode 90.子集Ⅱ

### 题目

给你一个整数数组 `nums` ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

> 示例 1：
>
> 输入：nums = [1,2,2] 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
>
> 示例 2：
>
> 输入：nums = [0] 输出：[[],[0]]

### 思路

这题是子集和组合总数的结合，要考虑到一个去重的问题。前面两题做好，这道题自然很简单。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTk2MDQ3ZWRhZjUyNGI0YzVmMWRkZmY4MmQwNDllNTNfNkkyUnFBbjFZSmdNYzh2djVoc0dCYjJpck9wSm9pWmVfVG9rZW46SXlWR2JvZlZRb2xmMFR4TlBBT2NCVjRKbjllXzE3MDYwMTk0MzA6MTcwNjAyMzAzMF9WNA)

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        if (startIndex >= nums.size()) return;
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > startIndex && nums[i] == nums[i - 1]) {
                continue;
            }
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return result;
    }
};
```