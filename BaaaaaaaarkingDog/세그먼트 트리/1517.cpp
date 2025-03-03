#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;

using namespace std;

int n;
vector<int> v;
vector<ll> tree;
vector<vector<int>> arr;

ll init(int node, int start, int end) {
    if (start == end) {
        arr[node].push_back(v[start]);
        return tree[node] = 0;
    }
    int mid = (start + end) >> 1;
    ll prev_cnt = init(node * 2, start, mid);
    ll next_cnt = init(node * 2 + 1, mid + 1, end);
    ll cnt = prev_cnt + next_cnt;
    int prev_idx = 0;
    int prev_size = arr[node * 2].size();
    int next_idx = 0;
    int next_size = arr[node * 2 + 1].size();
    while(true) {
        if (prev_idx == prev_size && next_idx == next_size) break;

        if (prev_idx == prev_size) {
            arr[node].push_back(arr[node * 2 + 1][next_idx++]);
            continue;
        }

        if (next_idx == next_size) {
            arr[node].push_back(arr[node * 2][prev_idx++]);
            continue;
        }

        if (arr[node * 2][prev_idx] <= arr[node * 2 + 1][next_idx])
        {
            arr[node].push_back(arr[node * 2][prev_idx++]);
        }
        else {
            arr[node].push_back(arr[node * 2 + 1][next_idx++]);
            cnt += prev_size - prev_idx;
        }
    }
    return tree[node] = cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int h = ceil(log2(n));
    tree = vector<ll>(1 << (h + 1));
    arr = vector<vector<int>>(1 << (h + 1));
    v.push_back(0);
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }   

    init(1, 1, n);

    cout << tree[1];
}