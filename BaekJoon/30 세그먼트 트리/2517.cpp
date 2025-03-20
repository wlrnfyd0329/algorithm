#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define endl "\n"

using namespace std;

int n;
vector<int> tree;
vector<int> power;
vector<pair<int,int>> v;

int query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int index) {
    if (index < start || end < index) return;
    if (start == end) {
        tree[node]++;
        return;
    }

    int mid = (start + end) >> 1;
    update(node * 2, start, mid, index);
    update(node * 2 + 1, mid + 1, end, index);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        power.push_back(num);
        v.push_back({num, i});
    }
    sort(v.begin(), v.end());

    for(int i = 0; i < n; i++) {
        power[v[i].second] = i + 1;
    }

    int h = ceil(log2(n));
    tree = vector<int>(1 << (h + 1));

    for(int i = 0; i < n; i++) {
        update(1, 1, n, power[i]);
        cout << query(1, 1, n, power[i] + 1, n) + 1 << endl;
    }
}