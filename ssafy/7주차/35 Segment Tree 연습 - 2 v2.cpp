#include <iostream>
#include <vector>
#define endl "\n"

typedef long long ll;
using namespace std;

int T, N, Q;
vector<ll> arr;
struct Node {
    Node *left, *right;
    ll value;
} *root = new Node();

ll init(Node *node, int start, int end) {
    if (start == end) {
        if (start % 2 == 0) node->value = arr[start];
        else node->value = -arr[start];
        return node->value;
    }
    int mid = (start + end) >> 1;
    if (!node->left) node->left = new Node();
    if (!node->right) node->right = new Node();
    return node->value = init(node->left, start, mid) + init(node->right, mid + 1, end);
}

void update(Node *node, int start, int end, int idx, int value) {
    if(start == end) {
        if(idx % 2 == 0) node->value = value;
        else node->value = -value;
        return;
    }
    int mid = (start + end) >> 1;
    if (idx <= mid) {
        if (!node->left) node->left = new Node();
        update(node->left, start, mid, idx, value);
    }
    else {
        if (!node->right) node->right = new Node();
        update(node->right, mid + 1, end, idx, value);
    }
    ll tmp1 = (node->left) ? node->left->value : 0;
    ll tmp2 = (node->right) ? node->right->value : 0;
    node->value = tmp1 + tmp2;
}

ll query(Node *node, int start, int end, int left, int right) {
    if (!node || right < start || end < left) return 0;
    if (left <= start && end <= right) return node->value;
    int mid = (start + end) >> 1;
    return query(node->left, start, mid, left, right) + query(node->right, mid + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        cin >> N >> Q;
        arr = vector<ll> (N);
        for(int i = 0; i < N; i++) {
            int num; cin >> num;
            arr[i] = num;
        }

        init(root, 0, N - 1);

        while(Q--) {
            int cmd, a, b;
            cin >> cmd >> a >> b;
            if (cmd == 0) {
                update(root, 0, N - 1, a, b);
            }
            else {
                if (a % 2 == 0) cout << query(root, 0, N - 1, a, b - 1) << " ";
                else cout << -query(root, 0, N - 1, a, b - 1) << " ";
            }
        }
        cout << endl;
    }
}