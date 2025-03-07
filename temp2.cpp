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

int main() {
    combination(0, 0, 0);
}   
