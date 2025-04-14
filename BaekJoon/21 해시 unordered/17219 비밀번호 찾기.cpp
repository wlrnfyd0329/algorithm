#include <iostream>
#include <unordered_map>
#include <string>
#define endl "\n"

using namespace std;

int N, M;
unordered_map<string, string> table;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        string s1, s2; cin >> s1 >> s2;
        table[s1] = s2;
    }

    for(int i = 0; i < M; i++) {
        string s; cin >> s;
        cout << table[s] << endl;
    }
}