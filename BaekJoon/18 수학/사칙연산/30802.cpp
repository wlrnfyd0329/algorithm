#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int shirt[6];
    int t, p;
    cin >> n;
    for(int i = 0; i < 6; i++) {
        cin >> shirt[i];
    }
    cin >> t >> p;

    int ans = 0;
    for(int i = 0; i < 6; i++) {
        if (shirt[i] % t == 0) {
            ans += shirt[i] / t;
        }
        else {
            ans += (shirt[i] / t) + 1;
        }
    }
    cout << ans << endl;
    cout << n / p << " " << n % p;
}