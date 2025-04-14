#include <iostream>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, result = 0;
    map<string, bool> m;
    m["ChongChong"] = true;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        if (m[s1]) {
            m[s2] = true;
        }
        if (m[s2]) {
            m[s1] = true;
        }
    }
    for (auto k : m) {
        if (k.second) result++;
    }
    cout << result;
}