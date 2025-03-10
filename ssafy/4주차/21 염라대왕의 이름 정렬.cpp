#include <iostream>
#include <set>
#include <string>
#define endl "\n"

using namespace std;

struct cmp {
    bool operator() (const string &a, const string &b) const {
        if (a.size() == b.size()) return a < b;
        return a.size() < b.size();
    }
};

set<string, cmp> name;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int n;
        name.clear();
        cin >> n;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            name.insert(s);
        }

        cout << "#" << tc << " " << endl;
        for(auto str : name) {
            cout << str << endl;
        }
    }
}