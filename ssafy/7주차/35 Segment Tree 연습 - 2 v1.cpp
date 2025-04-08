#include <iostream>
#include <vector>
#include <cmath>
#define endl "\n"

typedef long long ll;
using namespace std;

int T, n, q;
vector<ll> arr;
vector<ll> tree;

ll init(int node, int start, int end) {
    if (start == end) {
        if (start % 2 == 1) tree[node] = arr[start];
        else tree[node] = -arr[start];
        return tree[node];
    }
    int mid = (start + end) >> 1;
    return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

void update(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start == end) {
        if (start % 2 == 1) tree[node] = value;
        else tree[node] = -value;
        return;
    }
    int mid = (start + end) >> 1;
    update(node * 2, start, mid, index, value);
    update(node * 2 + 1, mid + 1, end, index, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        cin >> n >> q;
        int h = ceil(log2(n));
        arr = vector<ll> (n + 1);
        tree = vector<ll> (1 << (h + 1));
        for(int i = 1; i <= n; i++) {
            int num; cin >> num;
            arr[i] = num;
        }
        init(1, 1, n);
        while(q--) {
            int cmd, a, b;
            cin >> cmd >> a >> b;
            if (cmd == 0) {
                update(1, 1, n, a + 1, b);
            }
            else {
                if (a % 2 == 0) {
                    cout << query(1, 1, n, a + 1, b) << " ";
                }
                else {
                    cout << -query(1, 1, n, a + 1, b) << " ";
                }
            }
        }
        cout << endl;
    }
}