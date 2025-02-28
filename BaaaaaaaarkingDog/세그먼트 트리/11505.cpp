#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int N, M, K;
const int divide_num = 1'000'000'007;
vector<int> v;
vector<ll> tree;

ll init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = v[start];
    }

    int mid = (start + end) >> 1;
    return tree[node] = (init(node * 2, start, mid) * init(node * 2 + 1, mid + 1, end)) % divide_num;
}

ll multiple(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 1;
    if (left <= start && right >= end) return tree[node];
    int mid = (start + end) >> 1;
    return (multiple(node * 2, start, mid, left, right) * multiple(node * 2 + 1, mid + 1, end, left, right)) % divide_num;
}  

void update(int node, int start, int end, int index, ll num) {
    if(index < start || index > end) return;

    if(start == end) {
        tree[node] = num;
        return;
    }
    int mid = (start + end) >> 1;
    update(node * 2, start, mid, index, num);
    update(node * 2 + 1, mid + 1, end, index, num);
    tree[node] = (tree[node * 2] * tree[node * 2 + 1]) % divide_num;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;

    int h = ceil(log2(N));
    tree = vector<ll>(1 << (h + 1));
    v.push_back(0);
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }

    init(1, 1, N);

    for(int i = 0; i < M + K; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            update(1, 1, N, b, c);
        }
        else {
            cout << multiple(1, 1, N, b, c) << "\n";
        }
    }
}