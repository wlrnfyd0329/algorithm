#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
int arr[100005];
vector<pair<int,int>> tree; // {최솟값, 최댓값}

pair<int, int> init(int node, int start, int end)
{
    if (start == end) {
        return tree[node] = {arr[start], arr[start]};
    }

    int mid = (start + end) >> 1;

    pair<int, int> front = init(node * 2, start, mid);
    pair<int, int> back = init(node * 2 + 1, mid + 1, end);

    return tree[node] = {min(front.first, back.first), max(front.second, back.second)};
}

pair<int, int> find(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return {2'000'000'000, 0};
    if (left <= start && right >= end) return tree[node];

    int mid = (start + end) >> 1;
    pair<int, int> front = find(node * 2, start, mid, left, right);
    pair<int, int> back = find(node * 2 + 1, mid + 1, end, left, right);

    return {min(front.first, back.first), max(front.second, back.second)};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int h = ceil(log2(n));
    tree = vector<pair<int, int>>(1 << (h + 1));

    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    init(1, 1, n);

    for(int i = 0; i < m; i++) {
        int a, b; 
        cin >> a >> b;
        pair<int, int> res = find(1, 1, n, a, b);
        cout << res.first << " " << res.second << "\n";
    }
}