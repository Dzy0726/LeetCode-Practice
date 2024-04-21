/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-04-22 00:40:05
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-04-22 00:41:49
 * @FilePath: \LeetCode-Practice\Dual Pointer\加一减一\plusorminus.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
/**
 * 题目内容
 * 塔子哥是一个大学生，他喜欢研究各种关于字符串的问题。有一天，他在研究字符串问题时想到了这个问题。
 * 这道题目给定一个长度为n的、由数字字符组成的字符串，你可以进行如下操作： 
 * 选择一个字符，使得其加 1或者减 1
 * 
 * 请注意,你无法对’0’进行减 1 操作，也无法对’9’进行加 1 操作。
 * 
 * 若干次操作后，你需要使得该字符串存在一个长度为 k 的、所有字符都相同的连续子串。请你计算出操作的最小次数。
*/
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    int result = INT_MAX;
    for (int x = 0; x <= 9; ++x) {
        int opTimes = 0;
        int left = 0;
        for (int right = 0; right < n; ++right) {
          opTimes += abs(nums[right] - x);
          while (right - left + 1 > k) {
            opTimes -= abs(nums[left] - x);
            left++;
          }
          if (right - left + 1 == k) {
            if (opTimes < result) {
              result = opTimes;
            }
          }
        }
    }
    cout << result << endl;
    return 0;
}