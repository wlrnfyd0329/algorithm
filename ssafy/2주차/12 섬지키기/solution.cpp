// 바다 검사는 4면에서 그냥 같은거 만날때까지 하면 될거 같은데
// 경우의 수를 찾는 게 관건인거 같다. 15만번 호출하기 때문에
// maxArea 는 50번 호출인데 그때 최대 경우의 수는 5000이하면 400번의 연산을 5000번 하면 200만번으로
// 시간을 고려하지 않고 메소드를 구성해도 된다
// 결국 경우의 수를 찾는 것이 포인트가 될 것 같다.

// 바다물에 넘치는 것을 생각해보면 bfs 방법이 있을 수 있다
// 경우의 수를 일일이 계산하고자 하면 최대 400번을 15만번 호출한다면 6000만번 연산하는데 시간복잡도를 고려해야 한다
// 따라서 해싱을 통해서 조회하는 쿼리를 만들어주는 방식으로 진행하면 빠르게 계산할 수 있다
// 왜냐하면 update 쿼리가 없기 때문에 누적합과 같은 get 쿼리가 빠를 것이기 때문이다

// 해싱 방법은 두가지를 생각할 수 있다 => 1. 모든 경우의 수를 배열에 담아서 저장한다 2. 변화량을 계산해서 해싱한다
// 1. 모든 경우의 수를 55555개의 배열을 만들어서 저장한다
// 이때는 314이라고 가정하면 벽을 합쳤을 때, 최대 555 ~ 666 이기 때문에 이것이 가능한 조합을 모두 조회하는 방법을 써야 한다
// 2. 변화량은 -4 ~ 4니까 음수를 제거하기 위해 +5를 해서 1~9까지 생각하고 5개의 사이값인 4개의 변화량을 생각하면
// 최대 9999까지의 경우의 수를 생각할 수 있다
// 변화량으로 할때 주의할 점은 map을 해싱할때는 뒤에서 앞으로 뺏으면 구조물 해싱은 앞에서 뒤로 빼야지 둘이 합쳤을 때, 합이 같아진다

#include <vector>
#include <queue>

using namespace std;

const int MAX_MAP = 20;
const int MAX_HASH = 9999;

int n;
int initMap[MAX_MAP + 5][MAX_MAP + 5];
int modifiedMap[MAX_MAP + 5][MAX_MAP + 5];

struct info
{
    int x;
    int y;
    bool isRow; // 가로인지 아닌지
    bool isReverse; // 뒤집어졌는지 아닌지
}; 

vector<info> table[MAX_HASH + 5];


void init(int N, int mMap[20][20])
{
    n = N;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            modifiedMap[i + 1][j + 1] = initMap[i + 1][j + 1] = mMap[i][j];
        }
    }

    for (int i = 0; i <= MAX_HASH; i++) {
        table[i].clear();
    }

    for(int length = 2; length < 6; length++) {
        for(int i = 1; i <= n; i++) { // 가로 방향 체크(길이에 따라 탐색 범위가 달라지기 때문에 길이를 먼저 정해야 한다)
            for (int j = 1; j <= n - length + 1; j++) {
                int hash = 0;
                for(int k = 1; k < length; k++) { // 가로 정방향
                    hash = hash * 10 + (initMap[i][j + k] - initMap[i][j + k - 1] + 5);
                }
                table[hash].push_back({i, j, true, false});

                int rhash = 0;
                for(int k = length - 1; k >= 1; k--) { // 가로 역방향
                    rhash = rhash * 10 + (initMap[i][j + k - 1] - initMap[i][j + k] + 5);
                }

                if (rhash != hash) table[rhash].push_back({i, j, true, true});

            }
        }

        for(int i = 1; i <= n - length + 1; i++) { // 세로 방향 체크
            for (int j = 1; j <= n; j++) {
                int hash = 0;
                for(int k = 1; k < length; k++) { // 세로 정방향
                    hash = hash * 10 + (initMap[i + k][j] - initMap[i + k - 1][j] + 5);
                }
                table[hash].push_back({i, j, false, false});

                int rhash = 0;
                for(int k = length - 1; k >= 1; k--) { // 세로 역방향
                    rhash = rhash * 10 + (initMap[i + k - 1][j] - initMap[i + k][j] + 5);
                }
                if (rhash != hash) table[rhash].push_back({i, j, false, true});
            }
        }
    }
}

int numberOfCandidate(int M, int mStructure[5])
{
    if (M == 1) return n*n;

    int hash = 0;
    for(int i = 0; i < M-1; i++) {
        hash = hash * 10 + (mStructure[i] - mStructure[i+1] + 5);
    }
    return table[hash].size();
}

bool vis[MAX_MAP + 5][MAX_MAP + 5];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int checkArea(int level) {
    queue<pair<int, int>> q;
    for(int i = 0; i <= n + 1; i++) { // vis 초기화하고 큐에 시작점 넣기
        for(int j = 0; j <= n + 1; j++) {
            if (i == 0 || i == n + 1 || j == 0 || j == n+1) {
                q.push({i, j});
                vis[i][j] = true;
            }
            else {
                vis[i][j] = false;
            }
        }
    }

    int area = n * n;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        for(int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if (nx < 0 || nx > n + 1 || ny < 0 || ny > n + 1) continue;
            if (vis[nx][ny] || modifiedMap[nx][ny] >= level) continue;
            q.push({nx, ny});
            vis[nx][ny] = true;
            
            area--;
        }
    }

    return area;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
    int area = -1;

    if (M == 1) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                modifiedMap[i][j] += mStructure[0];
                area = max(area, checkArea(mSeaLevel));
                modifiedMap[i][j] = initMap[i][j];
            }
        }

        return area;
    }

    int hash = 0;
    for (int i = 0; i < M - 1; i++)
    {
        hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);
    }

    for(auto k : table[hash]) {
        if (k.isRow) { // 가로
            int height = (k.isReverse ? (modifiedMap[k.x][k.y] + mStructure[M - 1]) : (modifiedMap[k.x][k.y] + mStructure[0]));
            for(int i = 0; i < M; i++) {
                modifiedMap[k.x][k.y + i] = height;
            }
            area = max(area, checkArea(mSeaLevel));
            for(int i = 0; i < M; i++) {
                modifiedMap[k.x][k.y + i] = initMap[k.x][k.y + i];
            }
        }
        else { // 세로
            int height = (k.isReverse ? (modifiedMap[k.x][k.y] + mStructure[M - 1]) : (modifiedMap[k.x][k.y] + mStructure[0]));
            for(int i = 0; i < M; i++) {
                modifiedMap[k.x + i][k.y] = height;
            }
            area = max(area, checkArea(mSeaLevel));
            for(int i = 0; i < M; i++) {
                modifiedMap[k.x + i][k.y] = initMap[k.x + i][k.y];
            }
        }
    }

    return area;
}