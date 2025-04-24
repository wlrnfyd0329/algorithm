// union-find 인 것을 알지 못해서 틀렸다
// 파티에 참석하는 모든 인원의 관계를 파악해야 해서 분리 집합 개념이 적용된다

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int N, M, ans;
int p[55];
vector<vector<int>> parties;

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]); 
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (u == 0) p[v] = u;
    else p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    ans = 0;
    for(int i = 0; i <= N; i++) {
        p[i] = i;
    }
    int cnt; cin >> cnt;
    for(int i = 0; i < cnt; i++) {
        int num; cin >> num;
        uni(num, 0);
    }
    for(int party = 0; party < M; party++) {
        cin >> cnt;
        vector<int> person;
        for(int i = 0; i < cnt; i++) {
            int num; cin >> num;
            person.push_back(num);
            uni(person.front(), num);
        }
        parties.push_back(person);
    }

    for(int party = 0; party < M; party++) {
        bool isKnow = false;
        for(int i = 0; i < parties[party].size(); i++) {
            if (find(parties[party][i]) == 0) {
                isKnow = true;
                break;
            }
        }
        if (!isKnow) ans++;
    }
    cout << ans;
}   