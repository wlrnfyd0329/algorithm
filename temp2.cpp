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
    if (s.lower_bound(0) == s.end()) {
        cout<< 1;
    }
    else {
        cout << 0;
    }
}   
