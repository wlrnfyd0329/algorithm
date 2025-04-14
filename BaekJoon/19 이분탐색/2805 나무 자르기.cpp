#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }

    long long lf = 0, rg = 2'000'000'000;
    while(lf <= rg) {
        long long mid = (lf + rg) >> 1;
        long long meter = 0;
        for(int i = 0; i < n; i++) {
            if (v[i] > mid) {
                meter += v[i] - mid;
            }
        }
        if (meter < m) {
            rg = mid - 1;
        }
        else {
            lf = mid + 1;
        }
    }
    cout << rg;
}