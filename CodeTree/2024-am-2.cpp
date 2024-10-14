#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int n, m, Q, st, maxid;
vector<pair<int, int>> v[2005];
int dist[2005];
bool pro_id[30005];

struct cmp
{
    bool operator()(pair<tuple<int, int, int>, int> a, pair<tuple<int, int, int>, int> b)
    { // first는 id, seoncd는 순이익
        if (a.second != b.second)
            return a.second < b.second;
        else
            return get<0>(a.first) > get<0>(b.first);
    }
};

priority_queue<pair<tuple<int, int, int>, int>, vector<pair<tuple<int, int, int>, int>>, cmp> optim;

void construct()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + n, -1);
    dist[st] = 0;
    pq.push({0, st});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (dist[cur.second] != cur.first)
            continue;
        for (auto k : v[cur.second])
        {
            if (dist[k.second] == -1)
                dist[k.second] = k.first + dist[cur.second];
            else
            {
                if (dist[k.second] <= k.first + dist[cur.second])
                    continue;
                dist[k.second] = k.first + dist[cur.second];
            }
            pq.push({dist[k.second], k.second});
        }
    }
}

void create(int id, int rev, int dest)
{
    pro_id[id] = true;
    if (dist[dest] == -1)
    {
        optim.push({{id, rev, dest}, -1});
    }
    else
    {
        optim.push({{id, rev, dest}, rev - dist[dest]});
    }
}

int sell()
{
    while (!optim.empty())
    {
        auto k = optim.top();
        if (!pro_id[get<0>(k.first)])
        {
            optim.pop();
        }
        else
        {
            break;
        }
    }
    if (optim.empty())
        return -1;
    auto id = optim.top();
    if (id.second < 0)
        return -1;
    optim.pop();
    return get<0>(id.first);
}

void change_start(int s)
{
    priority_queue<pair<tuple<int, int, int>, int>, vector<pair<tuple<int, int, int>, int>>, cmp> toptim;
    st = s;
    construct();
    while (!optim.empty())
    {
        auto k = optim.top();
        optim.pop();
        if (pro_id[get<0>(k.first)])
            toptim.push(k);
    }
    while (!toptim.empty())
    {
        auto k = toptim.top();
        if (dist[get<2>(k.first)] == -1)
        {
            optim.push({{get<0>(k.first), get<1>(k.first), get<2>(k.first)}, -1});
        }
        else
        {
            optim.push({{get<0>(k.first), get<1>(k.first), get<2>(k.first)}, get<1>(k.first) - dist[get<2>(k.first)]});
        }
        toptim.pop();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp == 100)
        {
            cin >> n >> m;
            for (int j = 0; j < m; j++)
            {
                int a, b, c;
                cin >> a >> b >> c;
                if (a == b)
                    continue;
                v[a].push_back({c, b});
                v[b].push_back({c, a});
            }
            construct();
        }
        else if (tmp == 200)
        {
            int id, rev, dest;
            cin >> id >> rev >> dest;
            create(id, rev, dest);
        }
        else if (tmp == 300)
        {
            int id;
            cin >> id;
            pro_id[id] = false;
        }
        else if (tmp == 400)
        {
            cout << sell() << "\n";
        }
        else if (tmp == 500)
        {
            int s;
            cin >> s;
            change_start(s);
        }
    }
    return 0;
}