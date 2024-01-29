/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-29 20:23:59
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-29 20:24:02
 * @FilePath: \LeetCode-Practice\Greedy\135.分发糖果\candy.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candies(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }
        int sum = 0;
        for (auto candy : candies) {
            sum += candy;
        }
        return sum;
    }
};