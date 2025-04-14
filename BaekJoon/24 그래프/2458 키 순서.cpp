#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> small[505];
vector<int> big[505];
int small_vis[505];
int big_vis[505];

void smallDFS(int num) {
    if (small_vis[num]) return;
    small_vis[num] = 1;

    for(auto k : small[num]) {
        smallDFS(k);
    }
}

void bigDFS(int num) {
    if (big_vis[num]) return;
    big_vis[num] = 1;

    for(auto k : big[num]) {
        bigDFS(k);
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int know = 0;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
		small[i].clear();
        big[i].clear();
	}
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        small[a].push_back(b);
        big[b].push_back(a);
    }
    
    for (int i = 1; i <= n; i++) {
        fill(small_vis, small_vis + 505, 0);
        fill(big_vis, big_vis + 505, 0);
        smallDFS(i);
        bigDFS(i);
        bool isKnow = true;
        for(int j = 1; j <= n; j++) {
            if (!small_vis[j] && !big_vis[j]) {
                isKnow = false;
                break;
            } 
        }  
        if (isKnow) know++;
    }
    cout << know << "\n";

	return 0;
}