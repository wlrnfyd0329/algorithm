#include <iostream>
#include <vector>
#include <cmath>
#define endl "\n"

using namespace std;

int n;
vector<int> tree;
vector<int> v;

int init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = v[start];
    }

    int mid = (start + end) >> 1;
    return tree[node] = max(init(node * 2, start, mid), init(node * 2 + 1, mid + 1, end));
}

int query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) {
        if (tree[node] == v[right]) return 1;
        if (start == end) {
            if (tree[node] > v[right]) {
                return 1;
            }
            else {
                return 0;
            }
        }
        if (tree[node] < v[right]) return 0;
    }

    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    v.push_back(0);
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }
    int h = ceil(log2(n));
    tree = vector<int>(1 << (h + 1));

    init(1, 1, n);

    for(int i = 1; i <= n; i++) {
        cout << query(1, 1, n, 1, i) << endl;
    }
}