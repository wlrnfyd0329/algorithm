#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int n, m, k;
vector<ll> v;
vector<ll> tree;
vector<ll> lazy;

ll init_tree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = v[start];
    }

    int mid = (start + end) >> 1;
    return tree[node] = init_tree(node * 2, start, mid) + init_tree(node * 2 + 1, mid + 1, end);
}

void lazy_update(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int left, int right, ll num) {
    lazy_update(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * num;
        if (start != end) {
            lazy[node * 2] += num;
            lazy[node * 2 + 1] += num;
        }
        return;
    }

    int mid = (start + end) >> 1;
    update(node * 2, start, mid, left, right, num);
    update(node * 2 + 1, mid + 1, end, left, right, num);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
    lazy_update(node, start, end);
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    int h = ceil(log2(n));
    v = vector<ll>(n+1);
    tree = vector<ll>(1<<(h+1));
    lazy = vector<ll>(1<<(h+1));
    
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    init_tree(1, 1, n);

    for(int i = 0; i < m + k; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c;
        if (a == 1) {
            cin >> d;
            update(1, 1, n, b, c, d);
        }
        else {
            cout << query(1, 1, n, b, c) << "\n";
        }
    }

}
