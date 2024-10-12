#include <iostream>
#include <algorithm>
#include <tuple>
#include <queue>
#include <vector>
using namespace std;

int k, m;
queue<int> piece;
queue<pair<int, int>> q;

int board[5][5];
int sboard[5][5];
int vis[5][5];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

struct cmp
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        if (a.second == b.second)
            return a.first < b.first;
        else
            return a.second > b.second;
    }
};

struct cmp1
{
    bool operator()(tuple<int, int, pair<int, int>> a, tuple<int, int, pair<int, int>> b)
    {
        int aa, ab, ba, bb;
        pair<int, int> ac, bc;
        tie(aa, ab, ac) = a;
        tie(ba, bb, bc) = b;
        if (aa != ba)
            return aa < ba;
        else
        {
            if (ab != bb)
                return ab > bb;
            else
            {
                if (ac.second != bc.second)
                    return ac.second > bc.second;
                else
                    return ac.first > bc.first;
            }
        }
    }
};

void recover()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            sboard[i][j] = board[i][j];
        }
    }
}

void rotation(int x, int y, int num)
{
    for (int i = 0; i < num; i++)
    {
        int tmp = sboard[x - 1][y - 1];
        sboard[x - 1][y - 1] = sboard[x + 1][y - 1];
        sboard[x + 1][y - 1] = sboard[x + 1][y + 1];
        sboard[x + 1][y + 1] = sboard[x - 1][y + 1];
        sboard[x - 1][y + 1] = tmp;

        tmp = sboard[x - 1][y];
        sboard[x - 1][y] = sboard[x][y - 1];
        sboard[x][y - 1] = sboard[x + 1][y];
        sboard[x + 1][y] = sboard[x][y + 1];
        sboard[x][y + 1] = tmp;
    }
}

int bfs(bool isReal)
{
    fill(vis[0], vis[5], 0);
    int result = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    vector<pair<int, int>> v;
    queue<int> score = piece;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (vis[i][j] != 0)
                continue;
            q.push({i, j});
            v.clear();
            v.push_back({i, j});
            vis[i][j] = 1;
            while (!q.empty())
            {
                auto cur = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int nx = cur.first + dx[k];
                    int ny = cur.second + dy[k];
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
                        continue;
                    if (vis[nx][ny] != 0 || sboard[nx][ny] != sboard[cur.first][cur.second])
                        continue;
                    q.push({nx, ny});
                    v.push_back({nx, ny});
                    vis[nx][ny] = 1;
                }
            }
            if (v.size() > 2)
            {
                for (auto k : v)
                {
                    pq.push(k);
                }
                result += v.size();
            }
        }
    }
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        sboard[cur.first][cur.second] = score.front();
        score.pop();
    }
    if (isReal)
        piece = score;
    return result;
}

int search()
{
    priority_queue<tuple<int, int, pair<int, int>>, vector<tuple<int, int, pair<int, int>>>, cmp1> pq1;
    for (int k = 1; k < 4; k++)
    {
        for (int i = 1; i < 4; i++)
        {
            for (int j = 1; j < 4; j++)
            {
                rotation(i, j, k);
                pq1.push({bfs(false), k, {i, j}});
                recover();
            }
        }
    }
    int res, rot;
    pair<int, int> coordi;
    tie(res, rot, coordi) = pq1.top();
    rotation(coordi.first, coordi.second, rot);
    int result = 0;
    do
    {
        res = bfs(true);
        result += res;
    } while (res != 0);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            board[i][j] = sboard[i][j];
        }
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> m;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> board[i][j];
            sboard[i][j] = board[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        piece.push(tmp);
    }
    for (int i = 0; i < k; i++)
    {
        int result = search();
        if (result == 0)
            break;
        cout << result << " ";
    }
    return 0;
}