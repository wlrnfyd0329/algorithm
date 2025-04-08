#include <iostream>
#include <vector>
#include <cmath>
#define endl "\n"

using namespace std;

struct Node {
    int max_v;
    int min_v;
};

int T, n, q;
vector<int> arr;
vector<Node> tree;

Node init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = { arr[start], arr[start] };
    }
    int mid = (start + end) >> 1;
    Node left = init(node * 2, start, mid);
    Node right = init(node * 2 + 1, mid + 1, end);
    return tree[node] = { max(left.max_v, right.max_v), min(left.min_v, right.min_v) };
}

void update(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start == end) {
        tree[node] = { value, value };
        return;
    }
    int mid = (start + end) >> 1;
    update(node * 2, start, mid, index, value);
    update(node * 2 + 1, mid + 1, end, index, value);
    tree[node] = { max(tree[node * 2].max_v, tree[node * 2 + 1].max_v), min(tree[node * 2].min_v, tree[node * 2 + 1].min_v) };
}

Node query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return { -1, 1'000'000'005 };
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) >> 1;
    Node lf = query(node * 2, start, mid, left, right);
    Node rg = query(node * 2 + 1, mid + 1, end, left, right);
    return { max(lf.max_v, rg.max_v) , min(lf.min_v, rg.min_v) };
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        cin >> n >> q;
        arr = vector<int>(n + 1);
        int h = ceil(log2(n));
        tree = vector<Node>(1 << (h + 1));
        for (int i = 1; i <= n; i++) {
            int num; cin >> num;
            arr[i] = num;
        }
        init(1, 1, n);
        for (int Q = 0; Q < q; Q++) {
            int cmd, a, b; cin >> cmd >> a >> b;
            if (cmd == 0) {
                update(1, 1, n, a + 1, b);
            }
            else {
                Node node = query(1, 1, n, a + 1, b);
                cout << node.max_v - node.min_v << " ";
            }
        }
        cout << endl;
    }
}