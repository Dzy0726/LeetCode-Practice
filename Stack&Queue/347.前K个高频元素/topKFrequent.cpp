/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-08 16:29:55
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-08 16:31:08
 * @FilePath: \LeetCode-Practice\Stack&Queue\347.前K个高频元素\topKFrequent.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// My Solution : Understood Easily but O(nlogn)
class Solution {
public:
    static bool compare(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map <int, int> myMap;
        for (int i = 0; i < nums.size(); i++) {
            myMap[nums[i]]++;
        }
        vector<pair<int, int>> myVector(myMap.begin(), myMap.end());
        sort(myVector.begin(), myVector.end(), compare);
        vector <int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(myVector[i].first);
        }
        return result;
    }
};


// A Better Solution : O(nlogk)
class Solution {
public:
    // 小顶堆
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 要统计元素出现频率
        unordered_map<int, int> map; // map<nums[i],对应出现的次数>
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }

        // 对频率排序
        // 定义一个小顶堆，大小为k
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫面所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) { // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
                pri_que.pop();
            }
        }

        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;

    }
};