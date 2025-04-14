#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        int answer = 1;
        int temp = 1;
        for (int i = m; i > m - n; i--) {
            answer *= i;
            answer /= temp++;
        }
        cout << answer << "\n";
    }
}