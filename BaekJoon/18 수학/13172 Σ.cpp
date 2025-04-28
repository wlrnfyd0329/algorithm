#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"

using namespace std;

const int DIV = 1'000'000'007;
int m;
int n, s;

long long cal_b (int num) {
    if (num == 0) return 1;
    if (num == 1) return n;
    long long half = cal_b(num / 2) % DIV;
    return num % 2 ?(((half * half) % DIV) * n) % DIV : (half * half) % DIV;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m;
    long long ans = 0;
    while(m--) {
        cin >> n >> s;
        if (s % n == 0) ans += s / n;
        else ans += (cal_b(DIV - 2) * s) % DIV;
        ans %= DIV;
    }
    cout << ans;
}