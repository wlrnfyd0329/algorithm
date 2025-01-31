#include <iostream>
#include <stack>

using namespace std;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        stack<int> S;
        string s;
        cin >> s;
        for(auto k : s) {
            if (S.empty()) {
                S.push(k);
            }
            else {
                if (k == ')') {
                    if (S.top() == '(') {
                        S.pop();
                    }
                    else {
                        S.push(k);
                    }
                }
                else {
                    S.push(k);
                }
            }
        }

        if (S.empty()) {
            cout << "YES" << "\n";
        }
        else {
            cout << "NO" << "\n";
        }
    }
}
