/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-30 15:58:36
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-30 15:58:43
 * @FilePath: \LeetCode-Practice\Greedy\406.根据身高重建队列\reconstructQueue.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> result;
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            result.insert(result.begin() + position, people[i]);
        }
        return result;
    }
};