// 좌표만으로 면적을 구할 수 있는 신발끈 공식을 알아야만 풀 수 있다.
// 10^5 * 10^5 = 10^10 = 100억

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n;
vector<long long> x;
vector<long long> y;

double solve() {
    double ans = 0;
    for(int i = 0; i < n; i++) {
        ans += x[i] * y[i + 1] - x[i + 1] * y[i];
    }

    ans /= 2;
    return ans > 0 ? ans : -ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int tx, ty; cin >> tx >> ty;
        x.push_back(tx);
        y.push_back(ty);
    }
    x.push_back(x.front());
    y.push_back(y.front());

    cout << fixed;      // 이 방법으로
    cout.precision(1);  // 소수점 출력을 정할 수 있다.
    cout << solve();
}