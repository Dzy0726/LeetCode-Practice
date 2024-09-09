/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-09-09 23:51:38
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-09-09 23:52:34
 * @FilePath: \LeetCode-Practice\Dual Pointer\最长上升子数组.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
#include<bits/stdc++.h>

using namespace std;

const int N = 1E5+10;

int n, W[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> W[i];
    }
    int res = 0;

    for (int i = 0; i < n; i++) {
        int j = i;
        while (j + 1 < n && W[j + 1] > W[j]) {
            j++;
        }
        res = max(res, j - i + 1);
        i = j;
    }

    cout << res << endl;
}
