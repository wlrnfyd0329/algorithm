#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int a = n - k;
    for (int i = n - 1; i >= 1; i--) {
        n *= i;
    }
    for (int i = a - 1; i >= 1; i--) {
        a *= i;
    }
    for (int i = k - 1; i >= 1; i--) {
        k *= i;
    }
    if (a == 0) {
        a = 1;
    }
    if (k == 0) {
        k = 1;
    }
    cout << n / k / a;
}