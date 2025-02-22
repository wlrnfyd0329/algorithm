// 세그먼트 트리 할 줄 모르지만 일단 따라 짜보기

#include <iostream>
#include <vector>
#include <cmath>
typedef long long ll;
using namespace std;

vector<ll> segTree;
vector<ll> numV;

int N, M, K;

ll init(int start, int end, int node) {
    if (start == end)
        return segTree[node] = numV[start];
    int mid = (start + end) >> 1;
    return segTree[node] = init(start, mid, node << 1) + init(mid + 1, end, (node << 1) + 1);
}

ll sum(int start, int end, int left, int right, int node) {
    if (left > end || right < start)
        return 0;
    if (left <= start && right >= end)
        return segTree[node];
    int mid = (start + end) >> 1;
    return sum(start, mid, left, right, node << 1) + sum(mid + 1, end, left, right, (node << 1) + 1);
}

void update(int start, int end, int target, ll diff, int node)
{
    if (target > end || target < start)
        return;
    segTree[node] += diff;
    if (start == end)
        return;
    int mid = (start + end) >> 1;
    update(start, mid, target, diff, node << 1);
    update(mid + 1, end, target, diff, (node << 1) + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    int h = ceil(log2(N));
    int treeSize = 1 << (h+1);
    segTree = vector<ll>(treeSize);
    numV.push_back(0);
    for(int i = 0; i < N; i++) {
        ll num;
        cin >> num;
        numV.push_back(num);
    }
    init(1, N, 1);
    for (int i = 0; i < M + K; ++i)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            ll diff = c - numV[b];
            numV[b] = c;
            update(1, N, b, diff, 1);
        }
        else
        {
            cout << sum(1, N, b, c, 1) << "\n";
        }
    }
}