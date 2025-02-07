#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int TC;
    cin >> TC;
    for(int tc = 1; tc <= TC; tc++) {
        int n, m;
        cin >> n >> m;

        cout << "#" << tc << " ";
        if ((m & ((1 << n) - 1)) == ((1 << n) - 1)) {
            cout << "ON\n";
        }
        else {
            cout << "OFF\n";
        }
    }
}