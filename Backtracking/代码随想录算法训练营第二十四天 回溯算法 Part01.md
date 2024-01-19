# 代码随想录算法训练营第二十四天| 回溯算法 Part01

## 今日题目

77.[组合](https://leetcode.cn/problems/combinations/)

## 回溯法

1. 回溯三部曲

   1. 参数及返回类型：回溯算法中函数返回值一般为void；回溯算法需要的参数不像二叉树递归的时候那么容易一次性确定下来，所以一般是先写逻辑，然后需要什么参数，就填什么参数；
   2. 终止条件：一般来说搜到叶子节点也就找到了满足条件的一条答案，把这个答案存放起来，并结束本层递归；
   3. 回溯的遍历过程：一般是在集合中递归搜索，集合的大小构成了树的宽度，递归的深度就是树的深度
      1. ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NWI1NDYwNzBjZWRjYjQzNzkzZDk5ZWI0ZmZlYjQ1MzRfbEJ4T1FuTThKamFjd1ZiZTRBRG1RRDk2OFU4NGljUXNfVG9rZW46VzFpVGJOMGR5bzA2ZFV4M1BTd2N5QklYblFiXzE3MDU2MzA5MjE6MTcwNTYzNDUyMV9WNA)

2. 伪代码

   1. ```C++
      void backtracking(参数) {
          if (终止条件) {
              存放结果;
              return;
          }
      
          for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
              处理节点;
              backtracking(路径，选择列表); // 递归
              回溯，撤销处理结果
          }
      }
      ```

for循环看做是横向遍历，回溯是纵向遍历。

## LeetCode 77.组合

### 题目

给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。

你可以按 **任何顺序** 返回答案。

> 输入：n = 4, k = 2 输出： [  [2,4],  [3,4],  [2,3],  [1,2],  [1,3],  [1,4], ]

### 思路

对于上述示例，我们可以用两层for循环实现找出答案；如果k = 3，我们可以写三层for循环来实现。但是k是一个变量，我们不能预先知道k为多少，所以无法直接在代码中写出k层for循环来求解。

于是乎，回溯搜索应运而生~

回溯算法就是通过递归来控制有几层for循环，递归来做**层叠嵌套**（可以理解是开k层for循环），每一次的递归中嵌套一个for循环，那么递归就可以用于解决**多层嵌套循环**的问题了。

组合问题可以抽象成如下结构：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTFhNGYwMjQwMGUwYzk2OTY1NDMxMzkzYTMyZDI2MmFfbzNyRmpkdmtmVFR1S0gwOHV2SGtuSmdrMnZ6RmJHTVBfVG9rZW46UkR2M2JDeHBRb1JEWjd4UTZ6emNtS3VNbkZiXzE3MDU2MzA5MjE6MTcwNTYzNDUyMV9WNA)

图中可以发现n相当于树的宽度，k相当于树的深度。那么如何在这个树上遍历，然后收集到我们要的结果集呢？图中每次搜索到了叶子节点，我们就找到了一个结果。相当于只需要把达到叶子节点的结果收集起来，就可以求得 n个数中k个数的组合集合。

回溯三部曲：

1. 参数及返回值：
   1. 返回值可以为空，因为要遍历整个树，取得所有的叶子节点
   2. 每个叶子节点的结果是一个一维数组，最终要返回一个二维数组，这两个数组可以是参数（引用），也可以是全局变量
   3. 参数一定需要n和k，n是树的宽度，k是树的深度（每个结果叶子结点数组的大小）
   4. 因为要求的是组合，组合是无序的，1,2和2,1被认为是同一组合，所以在取完1后，下一步的取数范围就不再包含1，从2开始；同理，取完2后，下一步的取数范围不再包含2，从3开始，以此类推。所以需要一个参数start来控制下一层for循环（下一层递归）从哪里开始取值
2. 终止条件：到达叶子节点就把目前的一个结果加入到最终result。可以利用path.size() == k，即目前的数组大小已经符合题目要求的k，说明到达了叶子，需要添加该结果并且返回。
3. 单层的递归逻辑：如图，每层递归需要从当前数组范围内取出一个数，加入到暂时的结果，然后缩小数组取数的范围进行递归，递归完后记得回溯，也就是要删除这层递归加入的这个数。

### 代码

根据上述分析及伪代码的模版，可以写出代码：

```C++
class Solution {
public:
    vector<int> path;
    vector<vector<int>> result;
    void backTracking(int n, int k, int start) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = start; i <= n; i++) {
            path.push_back(i);
            backTracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backTracking(n, k, 1);
        return result;
    }
};
```

### 时空复杂度

时间复杂度：对于组合问题，我们可以将其视作一个有 k 层的树结构，每层代表一个元素的选择。在最坏的情况下，即当我们需要遍历整棵树时，时间复杂度与树的节点数有关。

在这个问题中，最坏的情况下，我们需要访问从 1 到 n 中选出的所有 k 个数的组合。组合数可以用二项式系数来表示，即 `C(n, k)`。因此，时间复杂度为 `O(C(n, k))`。这个组合数是在每一步中可能选项的数量的乘积，这是因为在每一层递归中，我们有越来越少的选择（因为不能重复选择同一个数字）。

空间复杂度：

空间复杂度由两部分组成：递归栈空间和用于存储结果的空间。

1. **递归****栈空间**:
   1. 因为回溯算法的深度为 k，所以递归栈的最大深度是 k。因此，递归栈空间的复杂度是 `O(k)`。
2. **存储结果的空间**:
   1. 结果集中可能包含 `C(n, k)` 个组合，每个组合有 k 个元素。因此，用于存储结果的空间复杂度是 `O(k * C(n, k))`。

综合以上两点，总的空间复杂度是 `O(k * C(n, k)) + O(k)`，简化后仍然是 `O(k * C(n, k))`，因为这是主导项。

### 学习与小结

写出代码后，我们模拟代码实现过程，当n = 4， k = 4时，只有一个答案就是1,2,3,4，但是根据我们的代码模拟，在添加该答案后，我们还会让i = 2，再去层层调用backtracking函数，但此时数组中剩下2个数（3,4），已经不够k个值，所以肯定会失败，这些就没有必要再去递归调用，这就涉及到了**剪枝**操作。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmE4M2JlY2E1Y2NjNjQ5NDI2YmEzY2EyZjc5Njc4YjZfRUFiZkVxSlFCN2thS0w1cWEwTTFxUUpzaFlJSlZPUTZfVG9rZW46QzFvamJGVURCbzNqVWF4MXVIbmN1QTVyblpjXzE3MDU2MzA5MjE6MTcwNTYzNDUyMV9WNA)

由上图可以看出，取得正确结果的操作数少于要被剪枝的操作数，所以剪枝还是十分必要的。

如果for循环选择的起始位置之后的元素个数已经不足我们需要的元素个数了，那么就没有必要搜索了：

1. 已经选择的元素个数：path.size();
2. 还需要的元素个数为: k - path.size();
3. 在集合n中至多要从该起始位置 : n - (k - path.size()) + 1，开始遍历

为什么有个+1呢，因为包括起始位置，我们要是一个左闭的集合。举个例子，n = 4，k = 3， 目前已经选取的元素为0（path.size为0），n - (k - 0) + 1 即 4 - ( 3 - 0) + 1 = 2。从2开始搜索都是合理的，可以是组合[2, 3, 4]。

优化后的代码如下：

```C++
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) { // 优化的地方
            path.push_back(i); // 处理节点
            backtracking(n, k, i + 1);
            path.pop_back(); // 回溯，撤销处理的节点
        }
    }
public:

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};
```

对于回溯法，我觉得先要画出树形图，知道自己每层递归要做什么，最后要取得什么，不能一上来就没有逻辑乱写一通。参数可以逐步添加，步骤可以逐步完善（比如剪枝），但是基本逻辑不能乱。