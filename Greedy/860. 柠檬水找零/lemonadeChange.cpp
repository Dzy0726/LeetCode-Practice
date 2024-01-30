/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-30 15:06:13
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-30 15:06:18
 * @FilePath: \LeetCode-Practice\Greedy\860. 柠檬水找零\lemonadeChange.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> change(3, 0);
        for (int i = 0; i < bills.size(); i++) {
            if (bills[i] == 5) {
                change[0]++;
            } else if (bills[i] == 10) {
                if (change[0] > 0) {
                    change[0]--;
                    change[1]++;
                } else {
                    return false;
                }
            } else {
                if (change[1] > 0 && change[0] > 0) {
                    change[1]--;
                    change[0]--;
                    change[2]++;
                } else if (change[1] <=0 && change[0] >= 3) {
                    change[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};