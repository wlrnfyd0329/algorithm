#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> human[100005];
int point[100005];

void dfs(int node) {
    for(auto k : human[node]) {
        point[k] += point[node];
        dfs(k);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int parent;
        cin >> parent;
        if (parent == -1) continue;
        human[parent].push_back(i);
    }

    for(int i = 0; i < m; i++) {
        int num, w;
        cin >> num >> w;
        point[num] += w;
    }

    dfs(1);

    for(int i = 1; i <= n; i++) {
        cout << point[i] << " ";
    }

}