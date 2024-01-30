# 代码随想录算法训练营第三十五天| 贪心算法 Part04

## 今日题目

860.[柠檬水找零](https://leetcode.cn/problems/lemonade-change/)

406.[根据身高重建队列](https://leetcode.cn/problems/queue-reconstruction-by-height/)

452.[用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)

## LeetCode 860.柠檬水找零

### 题目

在柠檬水摊上，每一杯柠檬水的售价为 `5` 美元。顾客排队购买你的产品，（按账单 `bills` 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 `5` 美元、`10` 美元或 `20` 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 `5` 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 `bills` ，其中 `bills[i]` 是第 `i` 位顾客付的账。如果你能给每位顾客正确找零，返回 `true` ，否则返回 `false` 。

> 示例 1：
>
> 输入：bills = [5,5,5,10,20] 输出：true 解释： 前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。 第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。 第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。 由于所有客户都得到了正确的找零，所以我们输出 true。
>
> 示例 2：
>
> 输入：bills = [5,5,10,10,20] 输出：false 解释： 前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。 对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。 对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。 由于不是每位顾客都得到了正确的找零，所以答案是 false。

### 思路

感觉也没有用到贪心，就是模拟整个交易过程，如果找的开就继续遍历bills，找不开就返回false；如果能成功遍历bills就返回true。

创建变量change用于记录当前手中有的零钱，遍历bills：

- 如果bill[i]是5，不用找零，change[0]++；
- 如果bill[i]是10，找零5元，如果change[0]小于等于0，返回false；大于0，则change[0]--;
- 如果bill[i]是20，找零15元，可以有两种方式：10+5或者5+5+5，先按10+5来找，如果不行再看5+5+5（可能这里用到了贪心？）

### 代码

```C++
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> change(3, 0);
        for (int i = 0; i < bills.size(); i++) {
            if (bills[i] == 5) {
                change[0]++;
            } else if (bills[i] == 10) {
                if (change[0] > 0) {
                    change[0]--;
                    change[1]++;
                } else {
                    return false;
                }
            } else {
                if (change[1] > 0 && change[0] > 0) {
                    change[1]--;
                    change[0]--;
                    change[2]++;
                } else if (change[1] <=0 && change[0] >= 3) {
                    change[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(n).

空间复杂度：空间复杂度为O(1).

### 学习与小结

情况一，情况二，都是固定策略，都不用我们来做分析了，而唯一不确定的其实在情况三。

而情况三逻辑也不复杂甚至感觉纯模拟就可以了，其实情况三这里是有贪心的。

账单是20的情况，为什么要优先消耗一个10和一个5呢？

因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能！

所以局部最优：遇到账单20，优先消耗美元10，完成本次找零。全局最优：完成全部账单的找零。

## LeetCode 406.根据身高重建队列

### 题目

假设有打乱顺序的一群人站成一个队列，数组 `people` 表示队列中一些人的属性（不一定按顺序）。每个 `people[i] = [h(i), k(i)]` 表示第 `i` 个人的身高为 `h(i)` ，前面 **正好** 有 `k(i)`( )个身高大于或等于 `h(i)` 的人。

请你重新构造并返回输入数组 `people` 所表示的队列。返回的队列应该格式化为数组 `queue` ，其中 `queue[j] = [h(j), k(j)]` 是队列中第 `j` 个人的属性（`queue[0]` 是排在队列前面的人）。

> 示例 1：
>
> 输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]] 输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 解释： 编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。 编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。 编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。 编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。 因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
>
> 示例 2：
>
> 输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]] 输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]

### 思路

这道题没做出来，看了力扣提示后，有一点思路，但是还是没有形成解法，并且思路和代码随想录的思路也不同，最终在评论区找到了这个思路：

每次先找最小的人，优先满足他的位置需求，但这个位置并不是他自己k对应的位置，而是在一个“剩余位置”数组中对应的位置：

```C++
[ 0, 1, 2, 3, 4, 5 ] [ 4, 4 ] 4
[ 0, 1, 2, 3, 5 ]    [ 5, 2 ] 2
[ 0, 1, 3, 5 ]       [ 5, 0 ] 0
[ 1, 3, 5 ]          [ 6, 1 ] 3
[ 1, 5 ]             [ 7, 1 ] 5
[ 1 ]                [ 7, 0 ] 1
[ [ 5, 0 ], [ 7, 0 ], [ 5, 2 ], [ 6, 1 ], [ 4, 4 ], [ 7, 1 ] ]
```

如上，最矮的人是4，他前面有4个比他高的，剩余位置数组中下标4就是他在最终排序中的下标，也是4；

接着是5，剩余位置数组中下标2就是他在最终排序中的下标——2；

[ 5, 0 ]，剩余位置数组中下标0就是他在最终排序中的下标——0；

**[ 6, 1 ] ，剩余位置数组中下标1就是他在最终排序中的下标——3；**

这个6，1很巧妙，剩余数组的值2已经被5，2取走了，所以下标2现在对应3，也就是6在最终数组中的下标。

给身高为h的人找空位，要保证该位置前有k个空位，而且这k个空位必须安排身高大于等于h的人，因此按照身高进行升序排序，先给矮的人找空位。对于相同身高的人，要优先考虑k大的，否则k较小的人拿走空位之后，k大的人之前的空位是不够k个的，因为已经有k小的人占走一个了。

但是这个思路实现起来也不是很简单，而且不是特别容易想明白，还是要看贪心算法。

### 学习

遇到两个维度权衡的时候，**一定要先确定一个维度，再确定另一个维度。**如果两个维度一起考虑一定会顾此失彼。

那么本题是先确定h还是先确定k呢？

先确定k的话，排完之后，会发现k的排列并不符合条件，身高也不符合条件，两个维度哪一个都没确定下来。

那么按照身高h来排序呢，身高一定是从大到小排（身高相同的话则k小的站前面），让高个子在前面。

此时我们可以确定一个维度了，就是身高，前面的节点一定都比本节点高。然后只需要按照k为下标重新插入队列就可以了。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2VlZTlkYmE5NDAzNjhiMmYyM2NkYzVjMTU2YjQ2YzlfTE9GMWx0Ymx0MkFxTjhzaHc2bUpobDloVHh4QzA5TUVfVG9rZW46UVBneGIySFRmb3ZsZFN4cGFUd2NZeUgwbkxkXzE3MDY2MDI5Nzk6MTcwNjYwNjU3OV9WNA)

按照身高排序之后，优先按身高高的people的k来插入，后序插入节点也不会影响前面已经插入的节点，最终按照k的规则完成了队列。

所以在按照身高从大到小排序后：

局部最优：优先按身高高的people的k来插入。插入操作过后的people满足队列属性

全局最优：最后都做完插入操作，整个队列满足题目队列属性

### 代码

```C++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> result;
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            result.insert(result.begin() + position, people[i]);
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

1. 排序：调用 `std::sort` 函数，其时间复杂度为 O(NlogN)，其中 N 是 `people` 数组的长度。
2. 插入操作：外部循环遍历每个人一次，执行 N 次插入操作。每次插入的时间复杂度为 O(k)，其中 k 是插入点之后元素的数量。在最坏情况下，每次插入都是在 `result` 数组的开头进行，这会涉及到将整个数组的元素移动一位。因此，这部分的时间复杂度为 O(N^2)。

综上所述，总的时间复杂度为 O(NlogN) + O(N^2)，由于 O(N^2) 在 N 较大时将主导整体时间复杂度，因此可以简化为 O(N^2)。

空间复杂度：空间复杂度为O(N).

### 小结

使用vector是非常费时的，C++中vector（可以理解是一个动态数组，底层是普通数组实现的）如果插入元素大于预先普通数组大小，vector底部会有一个扩容的操作，即申请两倍于原先普通数组的大小，然后把数据拷贝到另一个更大的数组上。

所以使用vector（动态数组）来insert，是费时的，插入再拷贝的话，单纯一个插入的操作就是O(n^2)了，甚至可能拷贝好几次，就不止O(n^2)了。

## LeetCode 452. 用最少数量的箭引爆气球

### 题目

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中`points[i] = [x(start), x(end)]` 表示水平直径在 `x(start)` 和 `x(end)`之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 **完全垂直** 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `x`(start，)`x`(end，) 且满足  `x(start) ≤ x ≤ x`(end，)则该气球会被 **引爆** (。)可以射出的弓箭的数量 **没有限制** 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 `points` ，*返回引爆所有气球所必须射出的* ***最小*** *弓箭数* 。

> 示例 1：
>
> 输入：points = [[10,16],[2,8],[1,6],[7,12]] 输出：2 解释：气球可以用2支箭来爆破: -在x = 6处射出箭，击破气球[2,8]和[1,6]。 -在x = 11处发射箭，击破气球[10,16]和[7,12]。
>
> 示例 2：
>
> 输入：points = [[1,2],[3,4],[5,6],[7,8]] 输出：4 解释：每个气球需要射出一支箭，总共需要4支箭。
>
> 示例 3：
>
> 输入：points = [[1,2],[2,3],[3,4],[4,5]] 输出：2 解释：气球可以用2支箭来爆破: - 在x = 2处发射箭，击破气球[1,2]和[2,3]。 - 在x = 4处射出箭，击破气球[3,4]和[4,5]。

### 思路

把所有区间按从小到大排序，找他们的重叠区间，如果重叠区间不在point[i]内，就需要多一根箭，并且重置重叠区间为points[i]；如果重叠区间和points[i]有重叠部分，就更新重叠区间。遍历一次数组就可以得到结果。

### 代码

```C++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] < b[0];
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        vector<int> overlap(2);
        int result = 1;
        sort(points.begin(), points.end(), cmp);
        overlap = points[0];
        for (int i = 1; i < points.size(); i++) {
            if (overlap[1] < points[i][0]) {
                result++;
                overlap = points[i];
            }
            if (points[i][0] > overlap[0]) {
                overlap[0] = points[i][0];
            } 
            if (points[i][1] < overlap[1]) {
                overlap[1] = points[i][1];
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(nlogn).

空间复杂度：空间复杂度为O(1).

### 学习与小结

```C++
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // 气球i和气球i-1不挨着，注意这里不是>=
                result++; // 需要一支箭
            }
            else {  // 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]); // 更新重叠气球最小右边界
            }
        }
        return result;
    }
};
```

我的思路与代码随想录的做法大致相同，细节处略有不同，只要每次重置最小的右边界即可，不需要更新整个区间。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MDRjNDcwZTkyOGYyNmU2MWUzOTBhYWY1YjgyMjAwNTNfSVQyM0ZaazhEbjdZaVBZN0ZOSG1PVXJtUXhHVHNwN0lfVG9rZW46TFNPT2JMd1NUb3J6dFF4WVFCVGN5VmwwbmpkXzE3MDY2MDI5Nzk6MTcwNjYwNjU3OV9WNA)