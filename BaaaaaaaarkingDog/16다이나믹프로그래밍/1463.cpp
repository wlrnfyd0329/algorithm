#include <iostream>
#include <algorithm>

using namespace std;

int a[1000005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tmp;
    cin >> tmp;
    for (int i = 2; i <= tmp; i++) {
        a[i] = a[i - 1] + 1;
        if (i % 2 == 0) a[i] = min(a[i], a[i / 2] + 1);
        if (i % 3 == 0) a[i] = min(a[i], a[i / 3] + 1);
    }
    cout << a[tmp];
}