/*** 
 * @Author: Dzy0726
 * @Date: 2024-02-05 15:51:13
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-02-05 15:51:24
 * @FilePath: \LeetCode-Practice\Dynamic Programming\509.斐波那契数\fib.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fib(n - 1) + fib(n - 2);
    }
};