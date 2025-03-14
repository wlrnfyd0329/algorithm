#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int arr[8005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    double sum = 0;
    for(auto k : v) {
        sum += k;
        arr[k + 4000]++;
    }
    int sum_res = round(sum / (int)v.size()); // 반올림해야 함
    cout << (sum_res == 0 ? 0 : sum_res) << "\n"; // -0 이 되지 않도록 해야 함
    cout << v[v.size() / 2] << "\n";
    int maxValue = 0;
    for (int i = 0; i < 8001; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    vector<int> v1;
    for (int i = 0; i < 8001; i++) {
        if (arr[i] == maxValue) {
            v1.push_back(i);
        }
    }
    sort(v1.begin(), v1.end());
    if (v1.size() > 1) {
        cout << v1[1] - 4000 << "\n";
    }
    else {
        cout << v1[0] - 4000 << "\n";
    }
    cout << v[n-1] - v[0];
}