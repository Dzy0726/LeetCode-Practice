/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-29 19:26:15
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-29 19:27:17
 * @FilePath: \LeetCode-Practice\Greedy\134.加油站\canCompleteCircuit.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// Greedy Solution
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0;
        int curSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++) {
            sum += gas[i] - cost[i];
            curSum += gas[i] - cost[i];
            if (curSum < 0) {
                start = i + 1;
                curSum = 0;
            }
        }
        if (sum < 0) return -1;
        return start;
    }
};

// A Better Solution
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0;
        int min = INT32_MAX;
        int minIndex = -1;
        for (int i = 0; i < gas.size(); i++) {
            sum += gas[i] - cost[i];
            if (sum < 0 && sum < min) {
                min = sum;
                minIndex = i;
            }
        }
        if (sum < 0) return -1;
        return (minIndex + 1) % gas.length;
    }
};