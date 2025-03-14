#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0 && b == 0 && c == 0) {
            break;
        }
        int vm = max({a, b, c});
        if (a*a + b*b + c*c == 2 * vm* vm) {
            cout << "right" << endl;
        }
        else {
            cout << "wrong" << endl;
        }
    }
}