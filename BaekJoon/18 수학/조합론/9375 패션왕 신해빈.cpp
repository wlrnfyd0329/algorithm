// 각 패션에 해당하는 부분에 선택하지 않는다는 선택지를 포함해서 곱하면 된다.
// 이후, 아무것도 선택되지 않는 선택지를 빼준다.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
#define endl "\n"

using namespace std;

int T, N, ans;
unordered_map<string, int> table;
vector<int> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int i = 0; i < T; i++) {
        table.clear();
        v.clear();
        ans = 1;
        cin >> N;
        for(int i = 0; i < N; i++) {
            string s1, s2;
            cin >> s1 >> s2;
            if (table.find(s2) == table.end()) {
                table[s2] = v.size();
                v.push_back(1);
            }
            v[table[s2]]++;
        }
        for(int idx = 0; idx < v.size(); idx++) {
            ans *= v[idx];
        }
        cout << ans - 1 << endl;
    }
    
}