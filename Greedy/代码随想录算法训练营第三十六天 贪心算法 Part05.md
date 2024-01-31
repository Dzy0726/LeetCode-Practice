# 代码随想录算法训练营第三十六天| 贪心算法 Part05

## 今日题目

435.[无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/)

763.[划分字母区间](https://leetcode.cn/problems/partition-labels/)

56.[合并区间](https://leetcode.cn/problems/merge-intervals/)

## LeetCode 435. 无重叠区间

### 题目

给定一个区间的集合 `intervals` ，其中 `intervals[i] = [start(i), end(i)]` 。返回 *需要移除区间的最小数量，使剩余区间互不重叠* 。

> 示例 1:
>
> 输入: intervals = [[1,2],[2,3],[3,4],[1,3]] 输出: 1 解释: 移除 [1,3] 后，剩下的区间没有重叠。
>
> 示例 2:
>
> 输入: intervals = [ [1,2], [1,2], [1,2] ] 输出: 2 解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。
>
> 示例 3:
>
> 输入: intervals = [ [1,2], [2,3] ] 输出: 0 解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

### 思路

和打气球的思路差不多，先对坐标数组排序，把intervals[0]记为最开始的重叠区间，遍历数组，如果有重叠count++，并更新二者的重叠区间；没有重叠就更新重叠区间为当前intervals[i]。

### 代码

```C++
class Solution {
public:
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] < b[0];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 0;
        vector<int> overlap = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= overlap[1]) {
                overlap = intervals[i];
                continue;
            }
            overlap[0] = max(overlap[0], intervals[i][0]);
            overlap[1] = min(overlap[1], intervals[i][1]);
            count++;
        }
        return count;
    }
};
```

### 时空复杂度

时间复杂度：

1. 排序：`std::sort` 函数对 `intervals` 数组进行排序，其时间复杂度为 O(NlogN)，其中 N 是 `intervals` 数组的长度。
2. 遍历计算：排序后，算法对排序后的 `intervals` 进行一次遍历，时间复杂度为 O(N)，在遍历过程中，算法更新重叠区间并计算需要移除的区间数量。

总的时间复杂度是 O(NlogN) + O(N)，可以简化为 O(NlogN)。

空间复杂度：

1. 额外的变量：除了输入数组之外，算法使用了固定空间的变量 `overlap` 和 `count`。
2. 排序：排序通常是原地的，不需要额外的空间，但是某些情况下，比如使用递归栈的快速排序，可能需要 O(logN) 的空间复杂度。

总的空间复杂度为 O(logN)，这是因为排序算法在堆栈上的空间消耗。

## LeetCode 763.划分字母区间

### 题目

给你一个字符串 `s` 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。

注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 `s` 。

返回一个表示每个字符串片段的长度的列表。

> 示例 1：
>
> 输入：s = "ababcbacadefegdehijhklij" 输出：[9,7,8] 解释： 划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。 每个字母最多出现在一个片段中。 像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 
>
> 示例 2：
>
> 输入：s = "eccbbbbdec" 输出：[10]

### 思路

通过力扣提示创建了一个map来存放字母最后出现的位置。循环遍历字符串，每次取partition和当前字母最后出现位置的较大值为partition，如果遍历到i和partition相等，说明此处满足一次划分的条件，可以划分。注意对partition的后续处理，要的结果是划分子串的长度，所以后面的partition还需要减去上一个partition，用oldOne来记录上一个partition。

### 代码

```C++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> end;
        for (int i = 0; i < s.size(); i++) {
            end[s[i]] = i;
        }
        vector<int> result;
        int oldOne = 0;
        int partition = 0;
        for (int i = 0; i < s.size(); i++) {
            partition = max(partition, end[s[i]]);
            if (i == partition && end[s[i]] >= partition) {
                result.push_back(partition - oldOne + 1);
                oldOne = partition + 1;
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

1. 第一个循环：遍历字符串 `s` 一次，记录每个字母最后出现的位置，时间复杂度为 O(N)，其中 N 是字符串 `s` 的长度。
2. 第二个循环：再次遍历字符串 `s`，确定分割点，时间复杂度仍为 O(N)。

因此，总的时间复杂度是 O(N) + O(N) = O(N)。

空间复杂度：

1. 哈希表：使用了一个 `unordered_map` 来存储每个字符出现的最后位置。在最坏的情况下，如果字符串包含了所有可能的字符，那么哈希表的空间复杂度为 O(M)，其中 M 是字符集的大小。对于 ASCII 字符来说，M 是常数（最多 128 或 256），但对于 Unicode 字符来说，M 可能很大。
2. 结果数组：结果数组 `result` 存储最终的分割片段长度。在最坏的情况下，如果字符串中的每个字母都是不同的，那么数组的长度可以达到 N。因此，空间复杂度为 O(N)。

综上，总的空间复杂度为 O(N + M)，在字符集大小是常数的情况下可以简化为 O(N)。

### 学习与小结

在遍历的过程中相当于是要找每一个字母的边界，如果找到之前遍历过的所有字母的最远边界，说明这个边界就是分割点了。此时前面出现过所有字母，最远也就到这个边界了。

可以分为如下两步：

- 统计每一个字符最后出现的位置
- 从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjkyZjEyOTVhM2YwMzVkYTcxMjljZWQzOGI3MDgwN2JfeTVJYm4xTzRianhYTUtZZTQ4Y1d4MThnVElUR1h3cHNfVG9rZW46VzdNVWJsRDFWb293a0F4V3duMWNtZXRCbkloXzE3MDY2ODQ0NjU6MTcwNjY4ODA2NV9WNA)

## LeetCode 

### 题目

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [start(i), end(i)]` 。请你合并所有重叠的区间，并返回 *一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间* 。

> 示例 1：
>
> 输入：intervals = [[1,3],[2,6],[8,10],[15,18]] 输出：[[1,6],[8,10],[15,18]] 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
>
> 示例 2：
>
> 输入：intervals = [[1,4],[4,5]] 输出：[[1,5]] 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

### 思路

思路和前面两道重叠区间问题的思路相同，先对原数组排序，取第一个数组为overlap重叠区间，在处理的时候略有不同，之前是更新overlap为重叠的部分，现在是对overlap扩容，让他可以完全覆盖重叠的区间。如果不再有交集就把当前结果加入result，出循环后要把最后一个overlap也加进去。

### 代码

```C++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        vector<int> overlap = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= overlap[1]) {
                overlap[0] = min(overlap[0], intervals[i][0]);
                overlap[1] = max(overlap[1], intervals[i][1]);
            } else {
                result.push_back(overlap);
                overlap = intervals[i];
            }
        }
        result.push_back(overlap);
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

1. **排序**：使用 `std::sort` 对区间进行排序，这是基于比较的排序算法，其时间复杂度是 O(NlogN)，其中 N 是区间 `intervals` 的数量。
2. **合并区间**：一旦数组被排序，算法进行一次线性遍历来合并区间，时间复杂度为 O(N)。

所以，总体时间复杂度是 O(NlogN) + O(N)，可以简化为 O(NlogN)。

空间复杂度：

1. **排序空间复杂度**：在C++中，`std::sort` 对于基本数据类型通常使用的是 introsort 算法（一种结合了快速排序、堆排序和插入排序的排序算法），它的空间复杂度是 O(logN)，主要是由于递归调用栈的开销。
2. **结果数组**：结果数组 `result` 存储合并后的区间，它的空间开销取决于合并后剩余的区间数量。在最坏的情况下，如果没有区间可以合并，空间复杂度为 O(N)。但这不会增加总体空间复杂度，因为这是输出所需的空间。
3. **临时变量**：变量 `overlap` 用于存储当前合并区间，是一个大小固定的数组（长度为 2），因此它的空间贡献是 O(1)。

综上所述，总体空间复杂度是 O(logN) + O(1) + O(N)（输出空间），通常输出空间不计入空间复杂度分析，因此可以简化为 O(logN)。然而，考虑到输出空间，我们可以说算法的空间复杂度是 O(N)，其中 N 是区间的数量。