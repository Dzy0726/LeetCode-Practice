/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-05 14:59:57
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-05 15:08:07
 * @FilePath: \LeetCode-Practice\Stack&Queue\225.用队列实现栈\implement-stack-using-queues.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution
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

// Better Solution
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