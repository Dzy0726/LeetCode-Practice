# 代码随想录算法训练营第十天| 栈与队列 Part01

## 今日题目

232.[用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/)

225.[用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/)

## 基础知识

1. 栈提供push 和 pop 等等接口，所有元素必须符合先进后出规则，所以栈不提供走访功能，也不提供迭代器(iterator)。 不像是set 或者map 提供迭代器iterator来遍历所有元素。
2. 栈是以底层容器完成其所有的工作，对外提供统一的接口，底层容器是可插拔的（也就是说我们可以控制使用哪种容器来实现栈的功能）。所以STL中栈往往不被归类为容器，而被归类为container adapter（容器适配器）。
3. 从下图中可以看出，栈的内部结构，栈的底层实现可以是vector，deque，list 都是可以的， 主要就是数组和链表的底层实现。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NmNkMTE4YTBmYjRiN2M0NWUzYzg0MTA1MTA4MGQ2MmFfZUc4eVBlMFJmTlJZNWFLWEFaT2NQNzdHd0x1eE1qM1VfVG9rZW46VTNsdmJ5clpxbzNhbjl4bTBoMmN1SkNxbnpmXzE3MDQ0Mzg1ODc6MTcwNDQ0MjE4N19WNA)

1. 我们常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。deque是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑了。SGI STL中 队列底层实现缺省情况下一样使用deque实现的。我们也可以指定vector为栈的底层实现，初始化语句如下：

   1. ```C++
      std::stack<int, std::vector<int>>  third;  // 使用vector为底层容器的栈
      ```

## LeetCode 232.用栈实现队列

### 题目

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（`push`、`pop`、`peek`、`empty`）：

实现 `MyQueue` 类：

- `void push(int x)` 将元素 x 推到队列的末尾
- `int pop()` 从队列的开头移除并返回元素
- `int peek()` 返回队列开头的元素
- `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`

**说明：**

- 你 **只能** 使用标准的栈操作 —— 也就是只有 `push to top`, `peek/pop from top`, `size`, 和 `is empty` 操作是合法的。
- 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

> 示例 1：
>
> 输入： ["MyQueue", "push", "push", "peek", "pop", "empty"] [[], [1], [2], [], [], []] 输出**：** [null, null, null, 1, 1, false] 解释： MyQueue myQueue = new MyQueue(); myQueue.push(1); // queue is: [1] myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue) myQueue.peek(); // return 1 myQueue.pop(); // return 1, queue is [2] myQueue.empty(); // return false

### 思路

本题的关键在于出队列和取顶部元素的实现。可以设置两个栈，但是进出方向正好相反，在push数据的时候，只要数据放进输入栈就好，但在pop的时候，操作就复杂一些，输出栈如果为空，就把进栈数据全部导入进来（注意是全部导入），再从出栈弹出数据，如果输出栈不为空，则直接从出栈弹出数据就可以了。可以创建一个私有变量_size，在push时加一，在pop时减一，直接用size的值判断队列是否为空。

### 代码

```C++
class MyQueue {
public:
    MyQueue() {
        _size = 0;
    }
    
    void push(int x) {
        inStack.push(x);
        _size++;
    }
    
    int pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int num = outStack.top();
        outStack.pop();
        _size--;
        return num;
    }
    
    int peek() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        return outStack.top();
    }
    
    bool empty() {
        return _size == 0;
    }

private:
    stack <int> inStack;
    stack <int> outStack;
    int _size;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

### 时空复杂度

- 时间复杂度: push和empty为O(1), pop和peek为O(n)
- 空间复杂度: O(n)

### 学习与小结

pop时，要先看outStack是不是空，如果不是空说明之前已经执行过至少一次pop，直接出栈即可。如果为空，说明是第一次执行pop或者pop次数把所有元素都出栈了，按照从头开始理解即可。可能会有先push几个元素，再pop一下，再push，再pop，这种情况不用担心，因为现在在模拟队列，先进先出，所以后进的元素不会影响即将要被pop的元素！一定要在做题过程中保持思路清晰，多写多画多模拟，便于自己理清逻辑！

## LeetCode 225. 用队列实现栈

### 题目

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（`push`、`top`、`pop` 和 `empty`）。

实现 `MyStack` 类：

- `void push(int x)` 将元素 x 压入栈顶。
- `int pop()` 移除并返回栈顶元素。
- `int top()` 返回栈顶元素。
- `boolean empty()` 如果栈是空的，返回 `true` ；否则，返回 `false` 。

> 示例：
>
> 输入： ["MyStack", "push", "push", "top", "pop", "empty"] [[], [1], [2], [], [], []] 输出： [null, null, null, 2, 2, false] 解释： MyStack myStack = new MyStack(); myStack.push(1); myStack.push(2); myStack.top(); // 返回 2 myStack.pop(); // 返回 2 myStack.empty(); // 返回 False

### 思路

push和empty较为简单，关键依旧是pop和top两个操作。我的想法是用两个队列，一个作为“主力”，一个作为“替补”，在push时，将元素push到“主力”队列，在pop时，将主力队列q1的元素个数pop到只剩一个，而之前pop的这些元素push到替补队列q2中作为保存，然后再将q1最后的元素输出并删除；那么下一次pop怎么办？我们将元素都按原来的顺序保存到了q2中，所以每次删除操作之前只需要判断一下现在元素在哪里存着，然后交换到q1，对q1操作即可。

### 代码

```C++
class MyStack {
public:
    MyStack() {
        _size = 0;
    }
    
    void push(int x) {
        q1.push(x);
        _size++;
    }
    
    int pop() {
        if (q1.empty() && !q2.empty()) {
            swap(q1,q2);
        }
        
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        
        int res = q1.front();
        q1.pop();
        _size--;
        return res;
    }
    
    int top() {
        if (q1.empty() && !q2.empty()) {
            swap(q1,q2);
        }
        
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        
        int res = q1.front();
        return res;
    }
    
    bool empty() {
        return _size == 0;
    }

private:
    queue <int> q1;
    queue <int> q2;
    int _size;
};
```

### 时空复杂度

时间复杂度：循环过程中每个节点遍历了一次，时间复杂度为O(n).

空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

很惊喜卡哥的两个队列解法和我的一样，都是用q2作为“备份”。那么如何优化这道题，只用一个队列来实现？

**一个队列在模拟栈弹出元素的时候只要将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部，此时再去弹出元素就是栈的顺序了。**

十分巧妙，可能受上一题的影响，思维定式，没有想到这样的解法。

```C++
class MyStack {
public:
    queue<int> que;
    /** Initialize your data structure here. */
    MyStack() {

    }
    /** Push element x onto stack. */
    void push(int x) {
        que.push(x);
    }
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int size = que.size();
        size--;
        while (size--) { // 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
            que.push(que.front());
            que.pop();
        }
        int result = que.front(); // 此时弹出的元素顺序就是栈的顺序了
        que.pop();
        return result;
    }

    /** Get the top element. */
    int top() {
        return que.back();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();
    }
};
```

注意：队列是有back操作取队尾的值（不删除），所以队列实现栈的top操作可以直接用back来实现。