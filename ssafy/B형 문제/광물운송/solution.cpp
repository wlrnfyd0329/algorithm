#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_CAMP 20005
#define MAX_BUC 35
#define INF 0x3f3f3f3f

unordered_map<int, int> idx_to_id;
int camp_idx = 0;
int len = 0;
vector<int> v[MAX_BUC][MAX_BUC];

struct Camp
{
    int r, c, q;
} camp[MAX_CAMP];

struct Group {
    int p, q;
} p[MAX_CAMP];

inline int distance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int find(int x)
{
    if (p[x].p < 0)
        return x;
    return p[x].p = find(p[x].p);
}

bool uni(int u, int v)
{
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (camp[u].q < camp[v].q)
    {
        swap(u, v);
    }
    else if (camp[u].q == camp[v].q) {
        if (camp[u].r < camp[v].r) {
            swap(u, v);
        }
        else if (camp[u].r == camp[v].r) {
            if (camp[u].c < camp[v].c) {
                swap(u, v);
            }
        }
    }
    p[v].q += p[u].q;
    p[u].p = v;
    return true;
}

void init(int L, int N)
{
    len = L;
    idx_to_id.clear();
    camp_idx = 0;
    for (int i = 0; i <= 30; i++)
    {
        for (int j = 0; j <= 30; j++)
        {
            v[i][j].clear();
        }
    }
}

// 20,000
int addBaseCamp(int mID, int mRow, int mCol, int mQuantity)
{
    idx_to_id[camp_idx] = mID;
    camp[camp_idx] = {mRow, mCol, mQuantity};
    p[camp_idx] = { -1, mQuantity };
    int dx = mRow / len;
    int dy = mCol / len;
    for (int i = max(0, dx - 1); i <= min(29, dx + 1); i++)
    {
        for (int j = max(0, dy - 1); j <= min(29, dy + 1); j++)
        {
            for (auto k : v[i][j])
            {
                int dist = distance(camp[k].r, camp[k].c, mRow, mCol);
                if (dist > len) continue;
                uni(k, camp_idx);
            }
        }
    }
    v[dx][dy].push_back(camp_idx);
    return p[find(camp_idx++)].q;
}

// 500
int findBaseCampForDropping(int K)
{
    int idx;
    int x = INF;
    int y = INF;
    int quantity = INF;
    for (int i = 0; i < camp_idx; i++) {
        if (p[i].p < 0 && p[i].q >= K) {
            if (quantity > camp[i].q) {
                idx = i;
                x = camp[i].r;
                y = camp[i].c;
                quantity = camp[i].q;
            }
            else if (quantity == camp[i].q) {
                if (x > camp[i].r) {
                    idx = i;
                    x = camp[i].r;
                    y = camp[i].c;
                    quantity = camp[i].q;
                }
                else if (x == camp[i].r) {
                    if (y > camp[i].c) {
                        idx = i;
                        x = camp[i].r;
                        y = camp[i].c;
                        quantity = camp[i].q;
                    }
                }
            }
        }
    }

    if (quantity == INF) return -1;
    return idx_to_id[idx];
}