#include <iostream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, result = 0;
    set<string> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "ENTER") {
            result += v.size();
            v.clear();
            continue;
        }
        v.insert(s);
    }
    cout << result + v.size();
}