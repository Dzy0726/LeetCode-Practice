/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-28 16:28:58
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-28 16:29:06
 * @FilePath: \LeetCode-Practice\Dual Pointer\1423.可获得的最大点数\maxScore.cpp
 * @Description: 正难则反，取k个数是固定的，可以看作滑动窗口长度为n-k, 计算总和减去窗口内的值即可
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int sum = 0;
        for (auto num: cardPoints) {
            sum += num;
        }
        int result = 0;
        for (int right = 0, left = 0; right < cardPoints.size(); ++right) {
            sum -= cardPoints[right];
            while (right - left + 1 > cardPoints.size() - k) {
                sum += cardPoints[left];
                left++;
            }
            if (right - left + 1 == cardPoints.size() - k) {
                result = max(result, sum);
            }
        }
        return result;
    }
};
