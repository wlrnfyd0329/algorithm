#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n, score, p;
int ans = 1, row = 1;
vector<int> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> score >> p;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v.push_back(num);
    }

    sort(v.begin(), v.end(), greater<>());

    for(auto k : v) {
        if (k > score) {
            ans += row;
            row = 1;
        }
        else if (k == score) {
            row++;
        }
        else break;
    }

    if (ans + row - 1 > p) {
        ans = -1;
    }
    cout << ans;
}