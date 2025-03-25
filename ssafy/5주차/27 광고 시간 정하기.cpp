#include <iostream>
#include <vector>
#define endl "\n"
#define st first
#define en second

using namespace std;

int L, N;
vector<pair<int, int>> pick;
vector<int> total;

int solve(int target) { // target 보다 큰 인덱스를 찾아야 함. 그래서 lf를 반환함.
    int lf = 0, rg = N - 1;
    while(lf <= rg) {
        int mid = (lf + rg) >> 1;
        if (target < pick[mid].en) {
            rg = mid - 1;
        }
        else {
            lf = mid + 1;
        }
    }

    return lf;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin>>T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> L >> N;
        pick = vector<pair<int, int>> (N);
        total = vector<int> (N);
        int ans = 0;
        for(int i = 0; i < N; i++) {
            int s, e;
            cin >> s >> e;
            pick[i] = {s, e};
            if (i == 0) {
                total[i] = e - s;
            }
            else {
                total[i] = total[i - 1] + (e - s);
            }
        }

        for(int i = 0; i < N; i++) {
            int target = pick[i].st + L;
            int idx = solve(target);
            int temp = total[idx - 1];
            if (i != 0) {
                temp -= total[i-1];
            }
            if (idx != N && target > pick[idx].st) {
                temp += target - pick[idx].st;
            }

            ans = max(ans, temp);
        }

        cout << "#" << tc << " " << ans << endl;
    }
}