#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int n, m, idx;
int st[100005];
int en[100005];
vector<int> arr[100005];

struct Node {
    Node *left, *right;
    int value, lazy;
    Node() {
        left = right = nullptr;
        value = lazy = 0;
    }
} *root = new Node();

void ett(int node)
{
    st[node] = ++idx;
    for (auto k : arr[node])
    {
        ett(k);
    }
    en[node] = idx;
}

void lazy_update(Node *node, int start, int end)
{
    if (!node) return;
    if (node->lazy != 0)
    {
        node->value += (end - start + 1) * node->lazy;
        if (start != end)
        {
            if(!node->left) node->left = new Node();
            node->left->lazy += node->lazy;
            if(!node->right) node->right = new Node();
            node->right->lazy += node->lazy;
        }
        node->lazy = 0;
    }
}

void update(Node* node, int start, int end, int left, int right, ll value)
{
    lazy_update(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right)
    {
        node->lazy += value;
        lazy_update(node, start, end);
        return;
    }

    int mid = (start + end) >> 1;
    if(!node->left) node->left = new Node();
    update(node->left, start, mid, left, right, value);
    if(!node->right) node->right = new Node();
    update(node->right, mid + 1, end, left, right, value);
    node->value = node->left->value + node->right->value;
}

ll query(Node* node, int start, int end, int index)
{
    lazy_update(node, start, end);
    if (!node || index < start || end < index) return 0;
    if (start == end) return node->value;

    int mid = (start + end) >> 1;
    return query(node->left, start, mid, index) + query(node->right, mid + 1, end, index);
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

    ett(1);

    for (int i = 0; i < m; i++)
    {
        int num, w;
        cin >> num >> w;
        update(root, 1, n, st[num], en[num], w);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << query(root, 1, n, st[i]) << " ";
    }
}