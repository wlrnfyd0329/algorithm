#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int n, k, c;
long long result;
pair<int, int> j[300005];
multiset<int> ms;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> j[i].second >> j[i].first;
    }
    sort(j, j+n);
    for (int i = 0; i < k; i++) {
        cin >> c;
        ms.insert(c);
    }

    for (int i = n-1; i >= 0; i--) {
        auto it = ms.lower_bound(j[i].second); // 해당하는 값이 없어도 그 값의 최대한 가까운 값을 돌려줌
        if (it == ms.end()) continue;
        result += j[i].first;
        ms.erase(it);
    }
    
    cout << result;
}