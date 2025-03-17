#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, c;
    vector<int> v;
    cin >> n >> c;
    for(int i = 0; i < n; i++) {
        int num; 
        cin >> num;
        v.push_back(num);
    }

    sort(v.begin(), v.end());

    int lf = 0, rg = 1'000'000'000;
    while(lf <= rg) {
        int mid = (lf + rg) >> 1;
        int cnt = 1;
        int st = v[0];
        for(int i = 1; i < n; i++) {
            if (v[i] - st >= mid) {
                cnt++;
                st = v[i];
            }
        }
        if (cnt < c) {
            rg = mid - 1;
        }
        else {
            lf = mid + 1;
        }
    }
    cout << rg;
}