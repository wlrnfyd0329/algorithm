// 문제를 처음 읽었을 땐, lcs를 이용하여 DP로 풀어야 했는데
// 그냥 그리디 하게 공통 최댓값을 찾아가면 되는 문제였다.
// 아래 부분을 신경써야 한다.
// 1. 공통 최댓값을 찾는데, 찾았으면 그 뒤만 탐색해야 된다.
// 2. 최댓값이 다르면 큰 값은 다시 탐색해야 된다.
// 3. 최댓값이 0이 나오면 더이상 탐색할 것이 없다는 것이다.

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n, m;
vector<int> a, b;
vector<int> ans;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a.push_back(num);
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        b.push_back(num);
    }
    int max_idx_a = 0, max_idx_b = 0,idx_a = 0, idx_b = 0, max_a = 0, max_b = 0;
    while(1) {
        for(int i = max_idx_a; i < n; i++) {
            if (max_a < a[i]) {
                max_a = a[i];
                idx_a = i + 1;
            }
        }
        for(int i = max_idx_b; i < m; i++) {
            if (max_b < b[i]) {
                max_b = b[i];
                idx_b = i + 1;
            }
        }

        if (max_a == 0 || max_b == 0) break;

        if (max_a == max_b) {
            ans.push_back(max_a);
            max_a = 0;
            max_idx_a = idx_a;
            max_b = 0;
            max_idx_b = idx_b;
        }
        else if (max_a > max_b) {
            max_a = 0;
            a[idx_a - 1] = 0;
        }
        else {
            max_b = 0;
            b[idx_b - 1] = 0;
        }
    }

    cout << ans.size() << endl;
    for(auto k : ans) {
        cout << k << " ";
    }
}