#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <bitset>

using namespace std;

void combination(int now, int cnt, int status) {
    if (cnt == 3) {
        cout << bitset<5>(status) << "\n";
        return;
    }

    for(int i = now; i < 5; i++) {
        combination(i + 1, cnt + 1, status | (1 << i));
    }
}

set<int> s;
vector<int> v;

int main() {
    // int lf = 1;
    // long long rg = (1 << 31) - 1;
    // int mid = (lf + rg) >> 1;
    // cout << mid;
    v.push_back(2);
    v.insert(v.begin() + 4, 4);
    for(auto k : v) {
        cout << k << " ";
    }
}   
