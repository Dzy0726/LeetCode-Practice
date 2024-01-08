# 代码随想录算法训练营第十三天| 栈与队列 Part03

## 今日题目

239.[滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)

347.[前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements/)

## LeetCode 239.滑动窗口最大值

### 题目

给你一个整数数组 `nums`，有一个大小为 `k` 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 `k` 个数字。滑动窗口每次只向右移动一位。

返回 *滑动窗口中的最大值* 。

> 示例 1：
>
> 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3 输出：[3,3,5,5,6,7] 解释： 滑动窗口的位置                最大值 ---------------               ----- [1  3  -1] -3  5  3  6  7       3 1 [3  -1  -3] 5  3  6  7       3 1  3 [-1  -3  5] 3  6  7       5 1  3  -1 [-3  5  3] 6  7       5 1  3  -1  -3 [5  3  6] 7       6 1  3  -1  -3  5 [3  6  7]      7
>
> 示例 2：
>
> 输入：nums = [1], k = 1 输出：[1]

### 思路

最先想到的就是暴力解法，每次移动窗口都找出最大的元素。然后在其基础上进行了一些剪枝操作，如果当前加入的元素比已有的max大，直接将max替换为当前要加入的元素，然后进行队列的pop和push操作，再将max加入到result中。如果当前加入的元素没max大，就要看当前队列的front是否是max，如果不是，说明max仍在队列中，直接进行pop和push操作，再将max加入到result；如果当前front就是max，就无法剪枝，pop掉max，push新元素，然后寻找当前队列的最大值。

但是最终结果超时，过掉了46/51个用例。

### 代码

46/51超时代码如下：

```C++
class Solution {
public:
    int findMax(queue<int> q) {
        int max = -INT32_MAX;
        while (!q.empty()) {
            max = q.front() > max ? q.front() : max;
            q.pop(); 
        }
        return max;
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector <int> result;
        queue <int> q;
        int max = -INT32_MAX;
        int i = 0;
        for (; i < k; i++) {
            max = nums[i] > max ? nums[i] : max;
            q.push(nums[i]);
        }
        result.push_back(max);
        for (; i < nums.size(); i++) {
            if (nums[i] >= max) {
                max = nums[i];
                q.pop();
                q.push(nums[i]);
                result.push_back(max);
            } else {
                if (q.front() != max) {
                    q.pop();
                    q.push(nums[i]);
                    result.push_back(max);
                } else {
                    q.pop();
                    q.push(nums[i]);
                    max = findMax(q);
                    result.push_back(max);
                }
            }
        }
        return result;     
    }
};
```

### 时空复杂度

时间复杂度：暴力解法最坏情况要遍了一次数组，然后在每个长度为k的窗口再遍历一次，所以时间复杂度为O(n*k).

空间复杂度：最坏情况下队列的长度就是整个数组的长度，所以空间复杂度为O(n).

### 学习与小结

队列中没有必要维护所有窗口元素，只需要维护那些**可能成为最大值**的元素即可。什么是可能成为最大值的元素？比如窗口为：1，3，-1，在遍历时，当3进入队列时，1就没用了，1不可能再成为最大值，因为它必将在3之前离开窗口，所以只保留3，-1就行，那-1小于1，为什么它比1更有可能成为最大值？因为当3离开窗口时，它有可能成为最大值。

这个维护元素单调递减的队列就叫做**单调队列**，即单调递减或单调递增的队列。C++中没有直接支持单调队列，需要我们自己来实现一个单调队列。它的头部永远是队列的最大值或最小值。对于窗口里的元素{2, 3, 5, 1 ,4}，单调队列里只维护{5, 4} 就够了，保持单调队列里单调递减，此时队列出口元素就是窗口里最大元素。

要实现这样的数据结构，需要有以下操作：

1. pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
2. push(value)：如果push的元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止

在C++中，如果没有指定容器，那么stack和queue的底层实现使用deque。所以本题的单调队列我们也使用deque来实现。

```C++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myqueue que;
        vector<int> result;
        int i = 0;
        for (; i < k; i++) {
            que.push(nums[i]);
        }
        result.push_back(que.front());
        for (; i < nums.size(); i++) {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }
        return result;
    }

private:
    class Myqueue {
    public:
        deque<int> q;
        void pop(int val) {
            if (!q.empty() && q.front() == val) {
                q.pop_front();
            }
        }

        void push(int val) {
            while (!q.empty() && q.back() < val) {
                q.pop_back();
            }
            q.push_back(val);
        }

        int front() {
            return q.front();
        }
    };
};
```

- 时间复杂度: O(n)
- 空间复杂度: O(k)

nums 中的每个元素最多也就被 push_back 和 pop_back 各一次，没有任何多余操作，所以整体的复杂度还是 O(n)。空间复杂度因为我们定义一个辅助队列，所以是O(k)。

C++中的**multiset**也可以用作单调队列：

多重集合(multiset) 用以有序地存储元素的容器。允许存在相等的元素。在遍历原数组的时候，只需要把窗口的头元素加入到multiset中，然后把窗口的尾元素删除即可（multiset可以查找，然后删除）。因为multiset是有序的，并且提供了*rbegin()，可以直接获取窗口最大值。

```C++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> st;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i >= k) st.erase(st.find(nums[i - k]));
            st.insert(nums[i]);
            if (i >= k - 1) ans.push_back(*st.rbegin());
        }
        return ans;
    }
};
```

## LeetCode 347.前K个高频元素

### 题目

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

> 示例 1:
>
> 输入: nums = [1,1,1,2,2,3], k = 2 输出: [1,2]
>
> 示例 2:
>
> 输入: nums = [1], k = 1 输出: [1]

### 思路

这道题要完成的是：

1. 统计每个数字出现的频率
2. 对频率排序
3. 取出排序靠前的前k个元素，返回

我们可以用map来统计每个数字出现的频率，只需要遍历一次数组。那么如何进行排序呢？可以将map转化为一个由pair组成的数组，即

```C++
vector<pair<int, int>> myVector(myMap.begin(), myMap.end());
```

这样转化之后，可以对value或者key进行排序，只需要定义一个比较函数，然后用sort函数对其排序：

```C++
bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second; // 根据值进行降序排序
}

sort(myMap.begin(), myMap.end(), compare);
```

> `sort` 通常是非常优化的，通常使用一种改进的快速排序，称为 introsort（内省排序），它结合了快速排序、堆排序和插入排序的优点。
>
> 在 C++ 中，将参数声明为 `const` 的主要目的是指定这些参数在函数内部不应被修改。这是一个良好的编程实践，特别是在设计比较函数时，因为比较函数通常不需要也不应该改变传递给它的参数。

最后取出排好序的前K个元素

### 代码

```C++
class Solution {
public:
    static bool compare(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map <int, int> myMap;
        for (int i = 0; i < nums.size(); i++) {
            myMap[nums[i]]++;
        }
        vector<pair<int, int>> myVector(myMap.begin(), myMap.end());
        sort(myVector.begin(), myVector.end(), compare);
        vector <int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(myVector[i].first);
        }
        return result;
    }
};
```

注意：您代码中出现的问题是因为您试图将一个非静态成员函数（compare）传递给 std::sort。std::sort函数希望有一个可调用的函数，可以用两个参数调用，但非静态成员函数还需要传递一个隐式的 this 指针，而std::sort 并不提供这个指针。所以compare函数要是static。

### 时空复杂度

时间复杂度：O(nlogn)，构建频率map、转为vector都是O(n)，快速排序最坏情况是O(nlogn)，最后找出前K个高频元素为O(K)，但K小于等于N，所以最后时间复杂度为O(nlogn)

空间复杂度：map、vector包括最后的result数组最坏情况长度都是n，所以空间复杂度为O(n).

### 学习与小结

进阶的要求是你所设计算法的时间复杂度 **必须** 优于 `O(n log n)` ，其中 `n` 是数组大小。考虑到只需要前K个高频元素，所以没有必要对全部元素的频率进行排序，从这里入手进行优化。

我们可以使用一种容器适配器就是**优先级队列**。什么是优先级队列呢？

其实就是一个披着队列外衣的堆，因为优先级队列对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式，看起来就是一个队列。而且优先级队列内部元素是自动依照元素的权值排列。那么它是如何有序排列的呢？缺省情况下priority_queue利用max-heap（**大顶堆**）完成对元素的排序，这个大顶堆是以vector为表现形式的complete binary tree（完全二叉树）。

什么是堆呢？

堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。如果父亲结点是大于等于左右孩子就是大顶堆，小于等于左右孩子就是小顶堆。

那么这道题该用大顶堆还是小顶堆？

不能想当然的认为找出频率最大的K个元素，当然用大顶堆。如果用大顶堆，每次移动更新的时候，都把当前频率最高的元素移除堆，那么怎么保留最大的K个元素呢？所以要使用小顶堆，这样每次把频率最小的元素移除堆，最后剩下的就是频率最大的K个元素。

所以整体思路就是：先用map存放元素及其对应的频率，再根据map构建大小为K的小顶堆，最后堆中存放的就是频率最高的前K个元素，然后将他们转为vector返回。

```C++
class Solution {
public:
    // 小顶堆
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 要统计元素出现频率
        unordered_map<int, int> map; // map<nums[i],对应出现的次数>
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }

        // 对频率排序
        // 定义一个小顶堆，大小为k
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫面所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) { // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
                pri_que.pop();
            }
        }

        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;

    }
};
```

1. 定义一个比较类 mycomparison，用于优先队列的元素比较：重载 () 操作符，该函数用于比较两个 pair 对象
2. 定义一个优先队列（小顶堆），元素类型为 pair<int, int>，自定义比较类为 mycomparison
   1.  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)>: 这部分声明了一个优先队列，其中：
   2.  pair<int, int>：指定了存储在队列中的元素类型，即包含两个整数的 pair，通常用来存储元素和它们的频率。
   3.  vector<pair<int, int>>：指定了底层容器类型，即用来实际存储队列中元素的容器，这里是一个 vector。
   4.  decltype(comp)：是一个类型推导指令，它获得 comp lambda 表达式的类型，这里 comp 是之前定义的用于比较两个 pair 的 lambda 表达式。decltype(comp) 因此表示优先队列将使用 comp 的类型作为其比较函数的类型。