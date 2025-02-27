#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int n, m, k;
vector<ll> segtree;
vector<ll> v;

ll init(int node, int start, int end) {
    if (start == end) {
        return segtree[node] = v[start];
    }

    int mid = (start + end) / 2;

    return segtree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

ll sum(int node, int left, int right, int start, int end) {
    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return segtree[node];
    int mid = (start + end) / 2;
    return sum(node * 2, left, right, start, mid) + sum(node * 2 + 1, left, right, mid + 1, end);
}

void update(int node, int start, int end, int index, ll diff) {
    if (index < start || index > end) return;
    segtree[node] += diff;

    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, index, diff);
        update(node * 2 + 1, mid + 1, end, index ,diff);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;

    int height = ceil(log2(n));
    int tree_size = 1 << (height + 1);
    segtree = vector<ll>(tree_size);
    v.push_back(0);
    for(int i = 0; i < n; i++) {
        ll tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    init(1, 1, n);

    for(int i = 0; i < m + k; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            ll diff = c - v[b];
            v[b] = c;
            update(1, 1, n, b, diff);
        }
        else {
            cout << sum(1, b, c, 1, n) << endl;
        }
    }

}