// 버블 소트는 오름차순으로 정렬한다고 했을 때, 나보다 작은 애들이 있는 만큼 swap하게 된다.
// 따라서 작은 애들부터 존재하는 인덱스를 따라 세그먼트 트리에 표시하고 자기 자신보다 큰 노드를 모두 query하면
// 자기 자신보다 작은 수의 수를 셀 수 있다.

// 2517 달리기는 들어온 순서가 중요하기 때문에 정렬을 하고 해당하는 index에 맞춰서 채워가며 비교를 하는 것과 다르게
// 1517 버블 소트는 들어온 순서보다는 자기보다 오른쪽에 있는 작은 애들의 수를 세야 되기 때문에 작은 수부터 update하며 진행하는 것이다.
// 하지만 결국 자기 자신의 세그먼트 노드가 큰 애들의 수를 세는 것으로 생각하면 같은 이치다.
// 1517 버블 소트는 세그먼트 트리로도 풀 수 있지만 분할 정복으로도 풀 수 있다.

// 분할 정복을 이용한 병합 정렬을 하고 풀 수 있다. 병합하는 과정에서 swap 횟수를 알 수 있다.
// 오른쪽으로 분할된 리스트의 원소가 왼쪽으로 분할된 리스트의 원소보다 작은 경우 swap이 일어나고 
// 각 리스트의 인덱스 간의 차이를 저장하여 더하면 swap의 횟수를 구할 수 있다.


#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

vector<ll> tree;
vector<pair<int, int>> arr;

void update(int node, int start, int end, int index) {
    if (start == end) {
        tree[node]++;
        return;
    }
    int mid = (start + end) >> 1;
    if (index <= mid) {
        update(node * 2, start, mid, index);
    }
    else {
        update(node * 2 + 1, mid + 1, end, index);
    }
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

void segment_solve() {
    int n;
    cin >> n;
    int h = ceil(log2(n));
    ll cnt = 0;
    tree = vector<ll>(1 << (h + 1));
    for (int i = 1; i <= n; i++) {
        int num; cin >> num;
        arr.push_back({num, i});
    }
    sort(arr.begin(), arr.end());
    for(auto k : arr) {
        update(1, 1, n, k.second);
        cnt += query(1, 1, n, k.second + 1, n);
        cout << k.first << " " << k.second << " " << cnt << endl;
    }

    cout << cnt;
}

vector<int> sorted;
vector<int> v;
ll ans = 0;

void merge(int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while(i <= mid && j <= right) {
        if (v[i] <= v[j]) {
            sorted[k] = v[i];
            i++;
        }
        else {
            sorted[k] = v[j];
            ans += j - k;
            j++;
        }
        k++;
    }

    if (i > mid) {
        for(int a = j; a <= right; a++) {
            sorted[k++] = v[a];
        }
    }
    else {
        for(int a = i; a <= mid; a++) {
            sorted[k++] = v[a];
        }
    }

    for(int a = left; a <= right; a++) {
        v[a] = sorted[a];
    }
}

void merge_sort(int left, int right) {
    if (left < right) {
        int mid = (left + right) >> 1;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}

void merge_sort_solve() {
    int n;
    cin >> n;
    int h = ceil(log2(n));
    sorted = vector<int>(n);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        v.push_back(num);
    }

    merge_sort(0, n - 1);

    cout << ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // merge_sort_solve();
    segment_solve();  
}