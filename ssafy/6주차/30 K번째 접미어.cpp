#include <iostream>
#include <algorithm>
#include <string>
#define endl "\n"

using namespace std;

const int MX = 400 * 400 + 5;
int unused;
int trie[MX][26];
int chk[MX];
int ans;
int K;

int chi(char c) {
    return c - 'a';
}

char i2c(int i) {
    return 'a' + i;
}

void insert(const string& s) {
    int cur = 1;
    for (auto c : s) {
        if (trie[cur][chi(c)] == -1) {
            trie[cur][chi(c)] = unused++;
        }
        cur = trie[cur][chi(c)];
    }
    chk[cur] = true;
}

void check(int cur, int i, string s) {
    if (trie[cur][i] == -1) return;
    if (chk[trie[cur][i]]) {
        if (++ans == K) {
            cout << s << endl;
            return;
        }
    }
    cur = trie[cur][i];
    for (int k = 0; k < 26; k++) {
        if (trie[cur][k] != -1) {
            check(cur, k, s + i2c(k));
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> K;
        string S; cin >> S;
        cout << "#" << tc << " ";
        if (K > S.size()) {
            cout << "none" << endl;
            continue;
        }
        unused = 2;
        ans = 0;
        fill(trie[0], trie[MX], -1);
        fill(chk, chk + MX, 0);
        for (int i = 0; i < S.size(); i++) {
            insert(S.substr(i, S.size() - i));
        }
        for (int i = 0; i < 26; i++) {
            string s = "";
            check(1, i, s+i2c(i));
        }
    }
}