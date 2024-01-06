/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-06 17:09:44
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-06 17:09:53
 * @FilePath: \LeetCode-Practice\Stack&Queue\150.逆波兰表达式求值\evalRPN.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
                tokens[i] == "/") {
                int right = nums.top(); // 取出第一个数
                nums.pop();
                int left = nums.top(); // 取出第二个数
                nums.pop();
                if (tokens[i] == "+") {
                    nums.push(left + right);
                } else if (tokens[i] == "-") {
                    nums.push(left - right);
                } else if (tokens[i] == "*") {
                    nums.push(left * right);
                } else {
                    nums.push(left / right);
                }
            } else {
                nums.push(std::stoi(tokens[i]));
            }
        }
        return nums.top();
    }
};