#include <iostream>
#include <set>
#include <map>

using namespace std;

struct word {
    int cnt = 0;
    string sw;
    
    word(int cnt, string sw) {
        this->cnt = cnt;
        this->sw = sw;
    }

    bool operator<(const word &w) const {
        if (cnt == w.cnt) {
            if (sw.size() == w.sw.size()) {
                return sw < w.sw;
            }
            else {
                return sw.size() > w.sw.size();
            }
        }
        else {
            return cnt > w.cnt;
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    map<string, int> M;
    set<word> S;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if ((int)s.size() < m) continue;
        M[s]++;
    }
    for (auto k : M) {
        S.insert(word(k.second, k.first));
    }

    for(auto k : S) {
        cout << k.sw << "\n";
    }
}