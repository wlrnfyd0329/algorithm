#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M;
vector<int> v;
vector<int> tree;

int init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = v[start];
    }

    int mid = (start + end) >> 1;

    return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

int sum(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) >> 1;
    return sum(node * 2, start, mid, left, right) + sum(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int index, int diff) {
    if(index < start || index > end) return;
    tree[node] += diff;
    if(start == end) return;
    int mid = (start + end) >> 1;
    update(node * 2, start, mid, index, diff);
    update(node * 2 + 1, mid + 1, end, index, diff);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    
    int h = ceil(log2(N));
    tree = vector<int>(1 << (h + 1));
    v.push_back(0);
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }

    init(1, 1, N);

    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        cout << sum(1, 1, N, a, b) << "\n";
    }
}