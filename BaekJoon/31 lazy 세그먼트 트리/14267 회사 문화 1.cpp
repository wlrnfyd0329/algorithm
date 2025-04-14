#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int n, m, idx;
int st[100005];
int en[100005];
vector<int> arr[100005];
vector<ll> tree;
vector<ll> lazy;

void ett(int node)
{
    st[node] = ++idx;
    for (auto k : arr[node])
    {
        ett(k);
    }
    en[node] = idx;
}

void lazy_update(int node, int start, int end)
{
    if (lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int left, int right, ll value)
{
    lazy_update(node, start, end);
    if (right < start || end < left)
        return;
    if (left <= start && end <= right)
    {
        tree[node] += (end - start + 1) * value;
        if (start != end)
        {
            lazy[node * 2] += value;
            lazy[node * 2 + 1] += value;
        }
        return;
    }

    int mid = (start + end) >> 1;
    update(node * 2, start, mid, left, right, value);
    update(node * 2 + 1, mid + 1, end, left, right, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void solo_update(int node, int start, int end, int index, int value)
{
    if (index < start || end < index)
        return;
    if (start == end)
    {
        tree[node] = value;
        return;
    }
    int mid = (start + end) >> 1;
    solo_update(node * 2, start, mid, index, value);
    solo_update(node * 2 + 1, mid + 1, end, index, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int index)
{
    lazy_update(node, start, end);
    if (index < start || end < index)
        return 0;
    if (start == end)
        return tree[node];

    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, index) + query(node * 2 + 1, mid + 1, end, index);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        int num;
        cin >> num;
        if (num == -1)
            continue;
        arr[num].push_back(i);
    }

    int h = ceil(log2(n));
    tree = vector<ll>(1 << (h + 1));
    lazy = vector<ll>(1 << (h + 1));

    ett(1);

    for (int i = 0; i < m; i++)
    {
        int num, w;
        cin >> num >> w;
        update(1, 1, n, st[num], en[num], w);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << query(1, 1, n, st[i]) << " ";
    }
}