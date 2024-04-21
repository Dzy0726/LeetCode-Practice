/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-21 23:21:26
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-21 23:21:32
 * @FilePath: \LeetCode-Practice\Dual Pointer\2410. 运动员和训练师的最大匹配数\matchPlayersAndTrainers.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        int i = 0, j = 0;
        while (i < players.size() && j < trainers.size()) {
            if (players[i] <= trainers[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return i;
    }
};