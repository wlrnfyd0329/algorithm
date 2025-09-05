#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define X first
#define Y second
#define MAX_CITY 1005
#define MAX_LIMIT 30005

vector<pair<int, int>> city[MAX_CITY];
priority_queue<pair<int, int>> pq;
int dist[MAX_CITY];

void init(int N, int K, int sCity[], int eCity[], int mLimit[])
{
    for (int i = 0; i < N; i++)
    {
        city[i].clear();
    }

    for (int i = 0; i < K; i++)
    {
        city[sCity[i]].push_back({mLimit[i], eCity[i]});
        city[eCity[i]].push_back({mLimit[i], sCity[i]});
    }
    return;
}

// 1400
void add(int sCity, int eCity, int mLimit)
{
    city[sCity].push_back({mLimit, eCity});
    city[eCity].push_back({mLimit, sCity});
    return;
}

// 100
int calculate(int sCity, int eCity, int M, int mStopover[])
{
    memset(dist, -1, sizeof(dist));
    pq.push({MAX_LIMIT, sCity});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (dist[cur.Y] != -1)
            continue;
        dist[cur.Y] = cur.X;
        for (auto nxt : city[cur.Y])
        {
            pq.push({min(cur.X, nxt.X), nxt.Y});
        }
    }

    int res = dist[eCity];
    for (int i = 0; i < M; i++)
    {
        res = min(res, dist[mStopover[i]]);
    }
    return res;
}