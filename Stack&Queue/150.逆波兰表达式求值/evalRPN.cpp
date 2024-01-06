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