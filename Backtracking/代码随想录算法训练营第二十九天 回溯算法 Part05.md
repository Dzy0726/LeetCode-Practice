# 代码随想录算法训练营第二十九天| 回溯算法 Part05

## 今日题目

491.[非递减子序列](https://leetcode.cn/problems/non-decreasing-subsequences/)

46.[全排列](https://leetcode.cn/problems/permutations/)

47.[全排列 II](https://leetcode.cn/problems/permutations-ii/)

## LeetCode 491.非递减子序列

### 题目

给你一个整数数组 `nums` ，找出并返回所有该数组中不同的递增子序列，递增子序列中 **至少有两个元素** 。你可以按 **任意顺序** 返回答案。

数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。

> 输入：nums = [4,6,7,7] 输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

### 思路

画出树形结构，发现既不是全部节点也不是叶子节点，可以看做是数量大于等于2的全部节点，但是要去重。根据这个思路，先把所有数量大于等于2的节点加入到result，再去重，通过。

递归三部曲：

1. 参数及返回值：依旧要遍历整个树，返回空；参数为传入的数组和for循环遍历的起始位置；
2. 终止条件：如果起始位置已经到达nums末尾，说明nums中元素已经不够两个，返回；
3. 单层递归逻辑：如果此时path的大小大于等于2，就把当前的path加入到result；for循环中如果path大小为0，就加入到path，说明此时是第一个元素；如果path大小不为0，则要用nums[i]与path的末尾比较大小，看是否递增，是的话加入path递归，不是的话跳过本次循环。

最后对result去重，竟然通过了……

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        if (path.size() >= 2) {
            result.push_back(path);
        }
        if (startIndex >= nums.size()) {
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            if (path.size() == 0) {
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            } else {
                if (nums[i] >= path[path.size() - 1]) {
                    path.push_back(nums[i]);
                    backtracking(nums, i + 1);
                    path.pop_back();
                }
            }
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        sort(result.begin(), result.end());
        auto it = unique(result.begin(), result.end());
        result.erase(it, result.end());
        return result;
    }
};
```

### 学习与小结

思路还是不够清晰，对树层树枝处理都不到位，学习一下规范的解法：

递归三部曲：

1. 参数及返回值：本题求子序列，很明显一个元素不能重复使用，所以需要startIndex，调整下一层递归的起始位置。

2. 终止条件：本题其实类似求子集问题，也是要遍历树形结构找每一个节点，所以可以不加终止条件，startIndex每次都会加1，并不会无限递归。

3. 单层搜索逻辑

   1.  同一父节点下的同层上使用过的元素就不能再使用了：

   2. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZWRiMDliMTg2ZWRjZTk4MWYwMzYyMjAwMTkwMGJkZjhfbk5oS2NPMTBZZ0l5T3hOYkw5OVQzR3NIUlJwMTNQeDFfVG9rZW46VlRUU2JOQkplb28wbUd4YWhjMWN6VFpkbjZjXzE3MDYwNzg2MjQ6MTcwNjA4MjIyNF9WNA)

   3.  需要用一个数组来记录本层元素是否使用过，但这里就不能和之前一样排序后来比较，因为题目不能对原数组排序。

   4. ```C++
      class Solution {
      public:
          vector<vector<int>> result;
          vector<int> path;
          void backtracking(vector<int>& nums, int startIndex) {
              if (startIndex > nums.size()) return;
              if (path.size() >= 2) result.push_back(path);
              int used[201] = {0};
              for (int i = startIndex; i < nums.size(); i++) {
                  if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) continue;
                  path.push_back(nums[i]);
                  used[nums[i] + 100] = 1;
                  backtracking(nums, i + 1);
                  path.pop_back();
              }
          }
          vector<vector<int>> findSubsequences(vector<int>& nums) {
              backtracking(nums, 0);
              return result;
          }
      };
      ```

## LeetCode 46.全排列

### 题目

给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。

> 示例 1：
>
> 输入：nums = [1,2,3] 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

### 思路

全排列就不需要控制循环的起始位置了，每次都要从剩下的数组中把每个元素都取一遍，所以我更新了nums数组的值，让每次递归的nums数组是“剩余值”。

1. 参数和返回值：遍历整个树形结构，返回值为空；参数为可以修改的数组；
2. 终止条件：提前记录原始数组的大小，如果path的大小和原始数组的大小相同，说明完成了一次全排列，将结果添加并返回；
3. 单层递归逻辑：先把当前数字加入path，再把它从nums中删除，进入递归，递归结束后再把它加进nums，并在path中也删掉他。回溯两个地方。

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int size = 0;
    void backtracking(vector<int>& nums) {
        if (path.size() == size) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            int tmp = nums[i];
            path.push_back(nums[i]);
            nums.erase(nums.begin() + i);
            backtracking(nums);
            nums.insert(nums.begin() + i, tmp);
            path.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        size = nums.size();
        backtracking(nums);
        return result;
    }
};
```

### 学习与小结

代码随想录的办法是使用used数组来记录nums中哪些已经用过了，用过的数字直接跳过，这样可以不修改nums数组。

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
```

## LeetCode 47.全排列 II

### 题目

给定一个可包含重复数字的序列 `nums` ，***按任意顺序*** 返回所有不重复的全排列。

> 输入：nums = [1,1,2] 输出： [[1,1,2], [1,2,1], [2,1,1]]

### 思路

和上一道题相比，多了重复元素这一点，对于重复元素的处理，先把数组排序，然后对树层去重，如果nums[i] == nums[i - 1] && used[i - 1] == false，说明即将要处理的nums[i]已经和前面重复了，这次就不需要再处理，跳过即可。

### 代码

```C++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) continue;
            if (used[i] == true) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
```

### 学习与小结

这题做的还不错，思路清晰，图也画的没问题~used数组真好用

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NDAzNTE2NWFlMjIzNzFlZjYyNDU0YWRmOTEyZmUxOThfMTUza3BKdUlta1ExZFFkY250cjF2SnlTTGRybVB0ZlRfVG9rZW46UDR0d2JUSUlqbzdQZFN4R3cyU2NEdTFWbkFoXzE3MDYwNzg2MjQ6MTcwNjA4MjIyNF9WNA)