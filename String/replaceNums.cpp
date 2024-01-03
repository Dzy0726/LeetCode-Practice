// My Solution
#include <iostream>
using namespace std;
int main() {
    string s;
    cin >> s;
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result.append("number");
        } else {
            result.push_back(s[i]);
        }
    }
    cout << result << endl;
    return 0;
}

// Standard Solution
#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    int oldSize = s.size();
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            count++;
        }
    }
    s.resize(s.size() + count * 5);
    int newSize = s.size();
    for (int i = oldSize - 1, j = newSize - 1; i < j; i--, j--) {
        if (s[i] < '0' || s[i] > '9') {
            s[j] = s[i];
        } else {
            s[j] = 'r';
            s[j - 1] = 'e';
            s[j - 2] = 'b';
            s[j - 3] = 'm';
            s[j - 4] = 'u';
            s[j - 5] = 'n';
            j -= 5;
        }
    }
    cout << s << endl;
    return 0;
}