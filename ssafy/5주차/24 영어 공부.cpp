#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int N, P;
vector<int> v;

int solve() {
    int ans = 0;
    for(int i = 0; i < N; i++) {
        int lf = i, rg = N - 1;
        while(lf <= rg) {
            int mid = (lf + rg) >> 1;
            int blank = (v[mid] - v[i] + 1) - (mid - i + 1); // 빈칸개수 (그 사이의 필요한 총 개수) - (사이에 있는 공부한 날의 수)
            if (blank > P) // 불가능
            {
                rg = mid - 1;
            }
            else { // 가능
                ans = max(ans, (v[mid] - v[i] + 1) + (P - blank));
                lf = mid + 1;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        v.clear();
        cin >> N >> P;
        for(int i = 0; i < N; i++) {
            int num;
            cin >> num;
            v.push_back(num);
        }
        cout << "#" << tc << " " << solve() << endl;
    }
}