#include <iostream>
#include <algorithm>

using namespace std;

int n, a[1005][3], h[1005][3];


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    h[0][0] = a[0][0];
    h[0][1] = a[0][1];
    h[0][2] = a[0][2];
    for (int i = 1; i < n; i++ ) {
        h[i][0] = min(h[i-1][1], h[i-1][2]) + a[i][0];
        h[i][1] = min(h[i-1][0], h[i-1][2]) + a[i][1];
        h[i][2] = min(h[i-1][0], h[i-1][1]) + a[i][2];
    }
    int tmp = min(h[n-1][0], h[n-1][1]);
    tmp = min(tmp, h[n - 1][2]);

    cout << tmp;
}