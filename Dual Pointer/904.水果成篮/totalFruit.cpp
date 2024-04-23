/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-23 16:17:11
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-23 16:17:17
 * @FilePath: \LeetCode-Practice\Dual Pointer\904.水果成篮\totalFruit.cpp
 * @Description: 好好思考吧只能说
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int result = 0;
        unordered_map<int, int> count;
        for (int left = 0, right = 0; right < fruits.size(); ++right) {
            count[fruits[right]]++;
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                left++;
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};