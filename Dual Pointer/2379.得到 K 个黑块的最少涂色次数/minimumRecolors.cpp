/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-27 19:19:59
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-27 19:20:07
 * @FilePath: \LeetCode-Practice\Dual Pointer\2379.得到 K 个黑块的最少涂色次数\minimumRecolors.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int result = INT_MAX;
        int blackCount = 0;
        for (int right = 0, left = 0; right < blocks.size(); ++right) {
            if (blocks[right] == 'B') {
                blackCount++;
            }
            while (right - left + 1 > k) {
                if (blocks[left] == 'B') {
                    blackCount--;
                }
                left++;
            }
            if (right - left + 1 == k) {
                result = min(result, k - blackCount);
            }
        }
        return result;
    }
};