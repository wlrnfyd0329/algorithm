#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int room[15][15];

void func() {
    for(int i = 1; i <= 14; i++) {
        room[0][i] = i;
    }

    for(int floor = 1; floor <= 14; floor++) {
        for(int i = 1; i <= 14; i++) {
            for(int j = 1; j <= i; j++) {
                room[floor][i] += room[floor - 1][j];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    func();
    for(int tc = 1; tc <= T; tc++) {
        int k, n;
        cin >> k >> n;
        cout << room[k][n] << endl;
    }
}