// 중요한 포인트는 조회를 하고자 하는 사람을 정렬하고 순서대로 update 하며 자기 자신보다 큰 사람들의 수를 query하면 된다.
// 정수의 범위가 1 ~ 1,000,000,000 인데, N은 3 ~ 500,000 이기 때문에 나온 정수를 N의 범위로 줄여야 한다.
// 들어온 순서대로 update하고 query하는데, 세그먼트 트리의 노드는 정렬한 순서의 index를 따른다.
// 들어온 순서대로 해당 정렬된 위치를 신경써서 진행하는 것이 포인트다.
// 정렬하지 않고 진행하려면 다이나막 세그먼트 트리로 하는 것도 가능할 것 같다.

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
        v.push_back({num, i});
    }
    sort(v.begin(), v.end());

    power = vector<int> (n);
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