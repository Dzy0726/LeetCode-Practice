/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-05 14:22:22
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-05 14:22:50
 * @FilePath: \LeetCode-Practice\Stack&Queue\232.用栈实现队列\implement-queue-using-stacks.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
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