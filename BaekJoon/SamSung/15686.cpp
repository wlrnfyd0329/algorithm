#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m, result = 2100000000;
int map[55][55];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> cc;
    vector<pair<int, int>> h, c;
    cin >> n >> m;
    for(int i = 1; i <= n ; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                h.push_back({i,j});
            }
            else if (map[i][j] == 2) {
                c.push_back({i, j});
            }
        }
    }
    for(int i = 0; i < m; i++) {
        cc.push_back(0);
    }
    for(int i = 0; i < c.size() - m; i++) {
        cc.push_back(1);
    }
    do {
        vector<int> dist(h.size(), 1000);
        for(int i = 0; i < cc.size(); i++) {
            if(cc[i] == 0) {
                for(int j = 0; j < h.size(); j++) {
                    dist[j] = min(dist[j], abs(h[j].first - c[i].first) + abs(h[j].second - c[i].second));
                }
            }
        }
        int temp = 0;
        for(int i = 0; i < dist.size(); i++) {
            temp += dist[i];
        }
        result = min(result, temp);
    } while(next_permutation(cc.begin(), cc.end()));

    cout << result;
}

/*
처음에는 거리가 bfs로 탐색 거리와 같아서 시도해보려했지만 결국 치킨집을 선택해야된다.
백트레킹으로 치킨집을 선택해서 모든 집과의 거리를 계산하는 방식으로 해결.
굉장히 오래 걸릴 것 같지만 숫자가 작아서 시간초과는 안난듯함.
*/