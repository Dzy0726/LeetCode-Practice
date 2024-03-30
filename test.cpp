#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N; 
    cin >> N;
    vector<int> aimLength;
    while (N--) {
        int x; 
        cin >> x;
        aimLength.push_back(x);
    }
    int max_value = *max_element(aimLength.begin(), aimLength.end()) + 1;
    vector<int> dp(max_value, INT_MAX);
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 1; i <= max_value; i++) {
        for (int j = 1; j < i; j++) {
            if (i % j == 0) {
                int count = 2; // A+C
                int pastes = (i / j) - 1;
                count += pastes;
                dp[i] = min(dp[i], dp[j] + count);
            }
        }
    }
    for (int i = 0; i < aimLength.size(); i++) {
        cout << dp[aimLength[i]] << endl;
    }

    return 0;
}