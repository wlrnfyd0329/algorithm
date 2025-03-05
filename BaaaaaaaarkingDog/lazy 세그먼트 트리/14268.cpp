#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m;
int idx = 0;
int st[100005];
int en[100005];
vector<int> son[100005];
vector<int> tree;
vector<int> lazy;

void dfs(int depth) {
    st[depth] = ++idx;
    for(auto k : son[depth]) {
        dfs(k);
    }
    en[depth] = idx;
}

void update_lazy(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];

        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    return;
}

void update_tree(int node, int start, int end, int left, int right, int diff) {
    update_lazy(node, start, end);

    if (start > right || end < left) return;
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }

    int mid = (start + end) >> 1;
    update_tree(node * 2, start, mid, left, right, diff);
    update_tree(node * 2 + 1, mid + 1, end, left, right, diff);
}



void query(int node, int start, int end, int index) {
    update_lazy(node, start, end);

    if (index < start || index > end) return;   
    if (start == end) {
        cout << tree[node] << "\n";
        return;
    }

    int mid = (start + end) >> 1;
    query(node * 2, start, mid, index);
    query(node * 2 + 1, mid + 1, end, index);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int h = ceil(log2(n));
    tree = vector<int>(1 << (h + 1));
    lazy = vector<int>(1 << (h + 1));
    for(int i = 1; i <= n; i++) {
        int num; 
        cin >> num;
        if (num == -1) continue;
        son[num].push_back(i);
    }

    dfs(1);

    for (int i = 0; i < m; i++) {
        int cmd, person, w;
        cin >> cmd >> person;
        if (cmd == 1) {
            cin >> w;
            update_tree(1, 1, n, st[person], en[person], w);
        }
        else {
            query(1, 1, n, st[person]);
        }
    }
}