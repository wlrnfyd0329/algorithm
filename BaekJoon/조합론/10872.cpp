#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    if (n == 0) {
        n = 1;
    }
    else {
        for (int i = n - 1; i >= 1; i--) {
            n *= i;
        }
    }
    cout << n;
}