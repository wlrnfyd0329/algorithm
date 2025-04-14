#include <iostream>

using namespace std;

int n, m, r;
int dist[105][105];
int item[105];

void floyd() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                int fp = dist[i][k];
                int sp = dist[k][j];
                if (fp == -1 || sp == -1) continue;
                if (dist[i][j] == -1) dist[i][j] = fp+sp;
                else dist[i][j] = min(dist[i][j], fp+sp);
            }
        }
    }

    int total = 0;
    for(int i = 1; i <= n; i++) {
        int item_cnt = 0;
        for(int j = 1; j <= n; j++) {
            if (dist[i][j] == -1 || dist[i][j] > m) continue;
            item_cnt += item[j]; 
        }
        total = max(total, item_cnt);
    }

    cout << total;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> r;
    for(int i = 1; i <= n; i++) {
        cin >> item[i];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (i==j) dist[i][j] = 0;
            else dist[i][j] = -1;
        }
    }
    for(int i = 0; i < r; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        if (dist[a][b] == -1) dist[a][b] = l;
        else dist[a][b] = min(dist[a][b], l);
        if (dist[b][a] == -1) dist[b][a] = l;
        else dist[b][a] = min(dist[b][a], l);
    }

    floyd();
}