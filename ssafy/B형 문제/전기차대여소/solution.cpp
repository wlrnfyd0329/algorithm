// 호출 횟수가 적은 add 함수에서 거리를 미리 계산해주는 것이 핵심인 문제였다.
// 다른건 다익스트라

#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#define MAX_N 350
#define X first
#define Y second

using namespace std;

int n;
int range;
int board[MAX_N][MAX_N];
int store_board[MAX_N][MAX_N];
vector<pair<int, int>> store[205];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void init(int N, int mRange, int mMap[MAX_N][MAX_N])
{
    n = N;
    range = mRange;
    fill(store_board[0], store_board[MAX_N], -1);
    for (int i = 0; i < n; i++)
    {
        memcpy(board[i], mMap[i], sizeof(int) * n);
    }
    for (int i = 0; i < 205; i++)
    {
        store[i].clear();
    }
}

void add(int mID, int mRow, int mCol) // O(N^2) : 4 * 100 * 100 => 40,000 => 40,000 * 200 => 8,000,000
{
    // 각 간선과 노드 미리 계산
    queue<pair<int, int>> q;
    int vis[MAX_N][MAX_N];
    for (int i = 0; i < n; i++)
    {
        memset(vis[i], 0, sizeof(int) * n);
    }
    store_board[mRow][mCol] = mID;
    q.push({mRow, mCol});
    vis[mRow][mCol] = 1;
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        if (vis[cur.X][cur.Y] == range + 1)
            break;
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;
            if (vis[nx][ny] || board[nx][ny] == 1)
                continue;
            if (store_board[nx][ny] >= 0)
            {
                store[mID].push_back({vis[cur.X][cur.Y], store_board[nx][ny]});
                store[store_board[nx][ny]].push_back({vis[cur.X][cur.Y], mID});
            }
            vis[nx][ny] = vis[cur.X][cur.Y] + 1;
            q.push({nx, ny});
        }
    }
}

int distance(int mFrom, int mTo) // O(Nlogn) = 200 * 8 = 1600 => 1600 * 800 = 1,280,000
{
    // 다익스트라
    int dist[205];
    fill(dist, dist + 205, 0x3f3f3f3f);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[mFrom] = 0;
    pq.push({dist[mFrom], mFrom});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        if (dist[cur.Y] != cur.X)
            continue;
        for (auto nxt : store[cur.Y])
        {
            if (dist[nxt.Y] <= nxt.X + dist[cur.Y])
                continue;
            dist[nxt.Y] = nxt.X + dist[cur.Y];
            pq.push({dist[nxt.Y], nxt.Y});
        }
    }

    if (dist[mTo] == 0x3f3f3f3f)
        return -1;
    else
        return dist[mTo];
}