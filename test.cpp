/*** 
 * @Author: Zhenyu Dong
 * @Date: 2024-03-30 16:06:04
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2024-03-30 16:06:13
 * @FilePath: \LeetCode-Practice\test.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int p, n, m;
    cin >> p >> n >> m;

    vector<int> monsters(n);
    for (int i = 0; i < n; i++) {
        cin >> monsters[i];
    }

    for (int i = 0; i < m; i++) {
        int boss_power;
        cin >> boss_power;
        int current_power = p;
        int monster_count = 0;
        int skill_used = 0;

        if (current_power > boss_power) {
            cout << 0 << endl;
            continue;
        }

        for (int monster_power : monsters) {
            while (current_power <= monster_power) {
                current_power = floor(current_power * 1.1);
                skill_used++;
                if (current_power > boss_power) break;
            }
            current_power += monster_power;
            monster_count++;
            if (current_power > boss_power) break;
        }

        while (current_power <= boss_power) {
            current_power = floor(current_power * 1.1);
            skill_used++;
        }

        cout << monster_count + skill_used << endl;
    }
    return 0;
}
// 64 位输出请用 printf("%lld")