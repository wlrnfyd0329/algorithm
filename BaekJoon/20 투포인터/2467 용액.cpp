// 값을 비교하거나 순회하면서 더해야 하는데 선형으로 진행되어 N^2의 풀이 방식이 불가능하다면
// 투포인터 방식을 떠올려야 한다.

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define endl "\n"

using namespace std;

int n;
struct Ans {
    int min_v;
    int liq1;
    int liq2;
} ans = {2'100'000'000, -1, -1};
vector<int> liq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        liq.push_back(num);
    }

    int lf = 0, rg = n - 1;
    while(lf < rg) {
        int value = abs(liq[lf] + liq[rg]);
        if (value < ans.min_v) {
            ans.min_v = value;
            ans.liq1 = liq[lf];
            ans.liq2 = liq[rg];
        }
        if (abs(liq[lf]) > abs(liq[rg])) { // value < 0
            lf++;
        }
        else if (abs(liq[lf]) < abs(liq[rg])) { // value > 0
            rg--;
        } 
        else {
            break;
        }
    }

    cout << ans.liq1 << " " << ans.liq2;
}