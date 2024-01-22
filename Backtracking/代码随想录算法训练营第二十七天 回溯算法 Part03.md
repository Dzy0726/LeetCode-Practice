# 代码随想录算法训练营第二十七天| 回溯算法 Part03

## 今日题目

39.[组合总和](https://leetcode.cn/problems/combination-sum/)

40.[组合总和 II](https://leetcode.cn/problems/combination-sum-ii/)

131.[分割回文串](https://leetcode.cn/problems/palindrome-partitioning/)

## LeetCode 39.组合总和

### 题目

给你一个 **无重复元素** 的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为目标数 `target` 的 所有 **不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。

`candidates` 中的 **同一个** 数字可以 **无限制重复被选取** 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 `target` 的不同组合数少于 `150` 个。

```Plaintext
输入：candidates = [2,3,6,7], target = 7输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。
```

### 思路

数组中用到的元素可以重复了，如果当前的路径和等于target就把路径添加到结果中，大于target就返回，小于target则继续递归。

递归三部曲：

1. 参数和返回值：要遍历所有的情况，所以返回值设置为空；参数传入数组和目标值，因为允许重复，所以可以不控制每层遍历的起始位置；
2. 终止条件：当前路径和大于或等于目标值，返回；
3. 单层逻辑：不返回的情况下，递归调用函数，记得回溯。

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backTracking(vector<int>& candidates, int target) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        if (sum > target) return;
        for (int i = 0; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backTracking(candidates, target);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backTracking(candidates, target);
        for (auto& path : result) {
            sort(path.begin(), path.end());
        }
        sort(result.begin(), result.end());
        auto last = unique(result.begin(), result.end());
        result.erase(last, result.end());        
        return result;
    }
};
```

### 学习与小结

1. 对结果去重

   1.  如何对二维数组去重？先排序二维数组中的每个一维数组，然后再排序整个二维数组，使用 `std::unique` 函数去除相邻的重复子数组。当 `std::unique` 被调用后，它会将相邻的重复元素移动到容器的末尾，并返回一个新的迭代器，指向去重后数组中“新的”末尾元素之后的位置。这个返回的迭代器实际上是指向**第一个被重复元素覆盖**的位置。换句话说，从这个迭代器到容器末尾的范围内的元素都是未定义的，并且这部分元素通常包含了一些原始的、未被去重处理的副本。最后再用erase函数，将后面的重复部分删除。

   2. ```C++
      auto last = unique(result.begin(), result.end());
      result.erase(last, result.end());    
      ```

2. 本题可以不去重！

   1.  直接在代码逻辑中避免重复！按照我的代码，每种情况都遍历到，那么示例的情况，会出现[2,3,3],[3,2,3],[3,3,2]三种重复情况，需要用startIndex来控制for循环的起始位置。
   2.  **什么时候用startIndex控制呢？**
   3. 如果是一个集合来求组合的话，就需要startIndex
   4. 如果是多个集合取组合，各个集合之间相互不影响，那么就不用startIndex

这道题是在一个集合中求组合，所以要用startIndex。

有startIndex控制for的起始位置，比如[2,3,3]之后，3开头只会从3和3之后的位置遍历，也就是从[3,3,3]开始，就不会再回去2，这样就避免了重复。

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backTracking(vector<int>& candidates, int target, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        if (sum > target) return;
        for (int i = startIndex; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backTracking(candidates, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backTracking(candidates, target, 0);     
        return result;
    }
};
```

1. 剪枝

   1. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=N2VlZmQ1ZGZmMTU1MDI1MGE2NTE1MjcyMDQ0MTNhOTNfU045b0dKN0p1M096b1FCWHZvdkhzVGo5R3ZsRXZxVndfVG9rZW46V2I4emJzME91b1FreDd4Snk1ZWM3WFNCblJlXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

   2.  当sum在上层中已经大于target，但是还要进入下一层才能return，进入下一层的递归调用其实没有必要，所以从这里入手剪枝，在for循环发现sum+candidates[i]已经大于target就不调用函数了。

   3. ```C++
      class Solution {
      public:
          vector<vector<int>> result;
          vector<int> path;
          int sum = 0;
          void backTracking(vector<int>& candidates, int target, int startIndex) {
              if (sum == target) {
                  result.push_back(path);
                  return;
              }
              if (sum > target) return;
              for (int i = startIndex; i < candidates.size() && sum+candidates[i] <= target; i++) {
                  path.push_back(candidates[i]);
                  sum += candidates[i];
                  backTracking(candidates, target, i);
                  sum -= candidates[i];
                  path.pop_back();
              }
          }
          vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
              backTracking(candidates, target, 0);     
              return result;
          }
      };
      ```

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2Q3NWRmNzAwNzlkY2Q0N2Y2MjZkYmRlYzlmNjY5ZjBfb0oxS01aYW83YjU1amdUZUExdXpLcFp6Z2RhMUpaYU9fVG9rZW46UkEyV2JSWFg1b2tGS0R4dWpZdGM4TDUwbnplXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

## LeetCode 40.组合总数II

### 题目

给定一个候选人编号的集合 `candidates` 和一个目标数 `target` ，找出 `candidates` 中所有可以使数字和为 `target` 的组合。

`candidates` 中的每个数字在每个组合中只能使用 **一次** 。

**注意：**解集不能包含重复的组合。 

```Plaintext
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```

### 思路

和上题一样，第一次做我在全部回溯结束后，对结果数组进行了去重，可以过掉172/177个用例，卡在了全是1的用例，超出内存限制。

去重又成了一个问题，想到了三数之和四数之和，先把数组排序，如果i大于i-1的值，就跳过本次循环。这里也可以先对数组进行排序，如果i大于startIndex且i和i-1的值相同，就跳过本次循环。从文字很抽象难理解，可以看一组图来模拟这个过程：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MTMxNWU3OWMzOTQ5OTMzOTAxNzJlNjVmNjcwNjk2Y2JfSDRtc1c1UllGM3BNSU9XRnptazB3UzlxeDJVcFk5OVFfVG9rZW46UDR6c2J3am1ybzhCMHZ4bmtXOWMySnNHbmNiXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

一直到startIndex = 9，都只有一个操作就是把当前candidates[i]加入path，递归；直到i = 9，此时sum == target，return上一层，startIndex = 9，i++后变为10，此时的path是前九个1，不包括startIndex指向的1，如果不去重的话，会把i=10指向的1依旧加入path，导致重复，所以加入了判断：if (i > startIndex && candidates[i] == candidates[i - 1])，满足这个条件，就跳过本次循环。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MjRiMTM4ZGM2MDYwYWVjNWRjYWNiZDNhMDFiZmY5MzNfUmpMTXhOS1M4QTRKbjdPSFQ4UXFVblZMRGFNMHlRbHlfVG9rZW46SXhoRWI4S3ppb2M3dTV4RWFjNmNMVnQwbkdnXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backTracking(vector<int>& candidates, int target, int startIndex) {
        if (sum > target) return;
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size(); i++) {
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }
            path.push_back(candidates[i]);
            sum += candidates[i];
            backTracking(candidates, target, i + 1);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backTracking(candidates, target, 0);
        return result;
    }
};
```

### 学习与小结

代码虽然通过了，但去重的逻辑还是要好好研究清楚。

看看卡哥自创的“树枝去重”和“树层去重”：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=N2FiNTBiZGJlMzhjMTQ3MWE2YTBkZTU0YWNlOTQ3OTRfMzcxR290WXA5d0tNZ0swdzNORGZHajg0b0RKRk04THJfVG9rZW46UVE5NGJYTnE1b1VVY2R4VmxzUGNHYkZ3bmxoXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

树枝就是纵向的，树层就是横向的，纵向的元素是允许重复的（candidates的元素），而横向是不能重复的，就按path数组的第一个位置来看，path[0] = 1的时候已经遍历过了（最左边这一个树枝），当第二个树枝又是path[0] = 1，就要去重，因为后续结果很可能重复。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MGMwOWMyYjgzNzZhY2QwNjIzZDMwOTE3OWY2MmJjOGVfWHZVYWNLRENrY3h6b3MzQXRNS0U4eWpSYUFxUDJxeVNfVG9rZW46RTk2YWJJZlV1b3I1N0t4ZEhidWNTUU9sbkFnXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

used数组可能会更加直观，加入到path就改used为true，如果candidates[i] == candidates[i -1 ]且used[i-1]==true，说明是同一树枝；如果是false，说明是同一树层，同一树层和紧邻的前一个值相等，就是重复。（所以要先对candidates进行排序）

## LeetCode 131.分割回文串

### 题目

给你一个字符串 `s`，请你将 `s` 分割成一些子串，使每个子串都是 **回文串** 。返回 `s` 所有可能的分割方案。

**回文串** 是正着读和反着读都一样的字符串。

> 输入：s = "aab" 输出：[["a","a","b"],["aa","b"]]

### 思路

这道题没有思路，想不通子串长度不同是怎么取到的……

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YjMyN2I2YjVhZTYxODQ5NTM5MjA2YzM2OTVkYzM3ZDlfMEFITEhoS1MydVF5UVpGbDF3VVkwdDJicGk1ZWFQM0hfVG9rZW46R0VhUWJRSzBQb1ZRNEt4M0xXTWNxMlJRbk5iXzE3MDU4OTMxMDk6MTcwNTg5NjcwOV9WNA)

根据上图，每次切割就是在剩下的子串划出切割线。可以抽象成从剩余字符中再选取几个。

比如aab中先选1个->a/，

再在ab中选1个->a/a/，再在b中选一个->a/a/b/；

再在ab中选2个->a/ab/；

先选2个->aa/

再在b中选一个->aa/b/；

先选3个->aab/

由此画出树状结构并完成递归回溯，发现叶子节点就是切割线切到了字符串最后。

回溯三部曲：

首先要两个全局变量，result存放结果，path存放路径，也就是图中的一个树枝；

1. 参数及返回值：需要遍历整个树，返回值为空；传入的参数除了字符串外，还需要一个startIndex记录切割的位置，看有没有切割到末尾；
2. 终止条件：如果切割到末尾，则添加结果并返回；
3. 单层递归逻辑：for循环遍历，看当前切割的子串是不是回文串，如果是，继续遍历；不是则退出此次循环。

### 代码

```C++
class Solution {
public:
    bool isPalindrome(string s, int begin, int end) {
        for (int i = begin, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) return false;
        }
        return true;
    }
    vector<vector<string>> result;
    vector<string> path;
    void backtracking(string s, int startIndex) {
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome(s, startIndex, i)) {
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            } else {
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
    }
    vector<vector<string>> partition(string s) {
        backtracking(s, 0);
        return result;
    }
};
```

### 学习与小结

- 切割问题可以抽象为组合问题：每次取1、2、3等等，for是横向，递归是纵向，for控制取1,2,3……递归控制取1的1的1，取1的1的2……
- 如何模拟那些切割线：关于模拟切割线，其实就是index是上一层已经确定了的分割线，i是这一层试图寻找的新分割线
- 切割问题中递归如何终止：切割线画到了字符串的末尾
- 在递归循环中如何截取子串：i+1，表示从下一个位置开始
- 如何判断回文