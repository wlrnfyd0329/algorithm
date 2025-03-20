#include <iostream>

using namespace std;

int n, m;
int city[205][205];
int plan[1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> city[i][j];
        }
        city[i][i] = 1;
    }
    for(int i = 0; i < m; i++) {
        cin >> plan[i];
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                int fp = city[i][k];
                int sp = city[k][j];
                if (fp == 1 && sp == 1) city[i][j] = 1;
            }
        }
    }

    for(int i = 1; i < m; i++) {
        if (!city[plan[i - 1]][plan[i]]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}