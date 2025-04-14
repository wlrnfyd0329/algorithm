#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, dir, dist, result;
int map[55][55];

int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

int ddx[4] = {-1, -1, 1, 1};
int ddy[4] = {-1, 1, -1, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<pair<int, int>> cloud;
    cin >> n >> m;
    cloud.push_back({n - 1, 0});
    cloud.push_back({n - 1, 1});
    cloud.push_back({n - 2, 0});
    cloud.push_back({n - 2, 1});
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for(int i = 0; i < m; i++) {
        cin >> dir >> dist;
        for(int j = 0; j < cloud.size(); j++) {
            cloud[j].first = (cloud[j].first + (n + dx[dir]) * dist) % n;
            cloud[j].second = (cloud[j].second + (n + dy[dir]) * dist) % n;
            map[cloud[j].first][cloud[j].second]++;
        }

        for (int j = 0; j < cloud.size(); j++)
        {
            for(int l = 0; l < 4; l++) {
                int nx = cloud[j].first + ddx[l];
                int ny = cloud[j].second + ddy[l];
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if(!map[nx][ny]) continue;
                map[cloud[j].first][cloud[j].second]++;
            }
        }
        vector<pair<int, int>> temp(cloud);
        cloud.clear();
        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < n; l++)
            {
                if(map[j][l] >= 2 && (find(temp.begin(), temp.end(), make_pair(j, l)) == temp.end())) {
                    map[j][l] -= 2;
                    cloud.push_back({j, l});
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result += map[i][j];
        }
    }

    cout << result;
}

/*
그냥 구현 노가다 문제인듯함
vector v(v1)이런식으로 복사하면 깊은 복사다.
*/
