#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

#define MAX_CAMP 20005
#define MAX_BUC 35

unordered_map<int, int> idx_to_id;
int camp_idx = 0;
int len = 0;
int p[MAX_CAMP];
vector<int> v[MAX_BUC][MAX_BUC];

struct Camp
{
    int r, c, q;
} camp[MAX_CAMP];

inline int distance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int find(int x)
{
    if (p[x] < 0)
        return x;
    return p[x] = find(p[x]);
}

bool uni(int u, int v)
{
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (p[u] < p[v])
    {
        int temp = u;
        u = v;
        v = temp;
    }
    if (p[u] == p[v])
        p[v]--;
    p[u] = v;
    return true;
}

void init(int L, int N)
{
    len = L;
    idx_to_id.clear();
    camp_idx = 0;
    memset(p, -1, sizeof(p));
    for (int i = 0; i < MAX_BUC; i++)
    {
        for (int j = 0; j < MAX_BUC; j++)
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
    int dx = mRow / len;
    int dy = mCol / len;
    for (int i = max(0, dx - 1); i <= min(29, dx + 1); i++)
    {
        for (int j = max(0, dy - 1); j <= min(29, dy + 1); j++)
        {
            for (auto k : v[i][j])
            {
            }
        }
    }
    return 0;
}

// 500
int findBaseCampForDropping(int K)
{
    return 0;
}