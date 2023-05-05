/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-05-05 19:05:28
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-05-05 19:05:35
 * @FilePath: /202.快乐数/happyNum.cpp
 * @Description: 
 * @
 * @Copyright (c) 2023 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    int getNum(int n) {
        int sum = 0;
        while(n > 0) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> myset;
        int sum;
        while(1) {
           sum = getNum(n);
           if(sum == 1) {
               return true;
           } 
           if(myset.find(sum) == myset.end()) {
               myset.insert(sum);
           } else {
               return false;
           }
           n = sum;
        }
    }
};