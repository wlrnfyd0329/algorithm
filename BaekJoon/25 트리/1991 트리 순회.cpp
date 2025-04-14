#include <iostream>
#include <queue>

using namespace std;

int n;
int rn[30], ln[30];

void left_bfs(int num) {
    cout << char(num + 'A');
    if (ln[num] != '.'-'A') left_bfs(ln[num]);
    if (rn[num] != '.'-'A') left_bfs(rn[num]);
}

void mid_bfs(int num) {
    if (ln[num] != '.'-'A') mid_bfs(ln[num]);
    cout << char(num + 'A');
    if (rn[num] != '.'-'A') mid_bfs(rn[num]);
}

void right_bfs(int num) {
    if (ln[num] != '.'-'A') right_bfs(ln[num]);
    if (rn[num] != '.'-'A') right_bfs(rn[num]);
    cout << char(num + 'A');
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        char r, l, m;
        cin >> m >> l >> r;
        ln[m - 'A'] = l - 'A';
        rn[m - 'A'] = r - 'A';
    }
    left_bfs(0);
    cout << "\n";
    mid_bfs(0);
    cout << "\n";
    right_bfs(0);

}