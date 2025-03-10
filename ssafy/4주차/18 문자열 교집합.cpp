#include <iostream>
#include <unordered_set>
#include <string>
#define endl "\n"

using namespace std;

int T, N, M, ans;
int word_idx;
unordered_set<string> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> M;
        ans = 0;
        s.clear();
        for(int i = 0; i < N; i++) {
            string str;
            cin >> str;
            s.insert(str);
        }
        for(int i = 0; i < M; i++) {
            string str;
            cin >> str;
            if (s.find(str) != s.end()) ans++;
        }
        cout << "#" << tc << " " << ans << endl;
    }
}