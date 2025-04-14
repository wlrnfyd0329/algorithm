#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, k, cnt, ncnt, result;
int r, c, m, d, s;
int arr[10000][5];
int narr[10000][5];
int use[10000];
vector<int> fireball;
vector<pair<int, int>> fireball_map;
int map[55][55];

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> k;
    for(int i = 0; i < M; i++) {
        cin >> r >> c >> m >> s >> d;
        arr[i][0] = r - 1;
        arr[i][1] = c - 1;
        arr[i][2] = m;
        arr[i][3] = s;
        arr[i][4] = d;
        cnt++;
    }
    
    while(k--) {
        fireball_map.clear();
        fill(map[0], map[54], 0);
        fill(use, use+10000, 0);
        ncnt = 0;
        for(int i = 0; i < cnt; i++) {
            arr[i][0] = (arr[i][0] + (N + dx[arr[i][4]]) * arr[i][3]) % N;
            arr[i][1] = (arr[i][1] + (N + dy[arr[i][4]]) * arr[i][3]) % N;
            map[arr[i][0]][arr[i][1]]++;
        }

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(map[i][j] >= 2) {
                    fireball_map.push_back({i, j});
                }
            }
        }

        for(int i = 0; i < fireball_map.size(); i++) {
            fireball.clear();
            for(int j = 0; j < cnt; j++) {
                if(fireball_map[i].first == arr[j][0] && fireball_map[i].second == arr[j][1]) {
                    fireball.push_back(j);
                    use[j] = 1;
                }
            }
            int tm = 0;
            int ts = 0;
            int td = 0;
            for(int j = 0; j < fireball.size(); j++) {
                tm += arr[fireball[j]][2];
                ts += arr[fireball[j]][3];
                td += arr[fireball[j]][4] % 2;
            }
            if((tm / 5) != 0) {
                for(int j = ncnt; j < ncnt + 4; j++) {
                    narr[j][0] = fireball_map[i].first;
                    narr[j][1] = fireball_map[i].second;
                    narr[j][2] = tm / 5;
                    narr[j][3] = ts / fireball.size();
                    if(td == 0 || td == fireball.size()) {
                        narr[j][4] = 2 * (j - ncnt);
                    }
                    else {
                        narr[j][4] = 2 * (j - ncnt) + 1;
                    }
                }
                ncnt += 4;
            }
        }
        for(int i = 0; i < cnt; i++) {
            if(!use[i]) {
                narr[ncnt][0] = arr[i][0];
                narr[ncnt][1] = arr[i][1];
                narr[ncnt][2] = arr[i][2];
                narr[ncnt][3] = arr[i][3];
                narr[ncnt][4] = arr[i][4];
                ncnt++;
            }
        }
        cnt = ncnt;
        for(int i = 0; i < cnt; i++) {
            arr[i][0] = narr[i][0];
            arr[i][1] = narr[i][1];
            arr[i][2] = narr[i][2];
            arr[i][3] = narr[i][3];
            arr[i][4] = narr[i][4];
        }
    }
    
    for(int i = 0; i < cnt; i++) {
        result += arr[i][2];
    }
    cout << result;
}

/*
OutofBounds 오류가 처음에 났다.
fireball 개수가 5500개로 했는데 틀렸고 10000개를 했더니 맞았다.
fireball이 최대 만개까지 만들어질 수 있나보다.

구조체를 사용하자
struct fireball{
    int x;
    int y;
    int mass;
    int s;
    int d;
};
그리고
벡터를 사용해서 파이어볼을 저장했으면 더욱! 간편하고 배열의 수도 생각할 필요가 없었을 것이다.
vector<fireball> map[51][51];
vector<fireball> fireballs;
*/