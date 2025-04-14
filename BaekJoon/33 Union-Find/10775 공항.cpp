// 결국 root가 0번이 되면 공항이 폐쇄되는 것이다.

#include <iostream>
#include <string.h>
#define endl "\n"

using namespace std;

int p[100'005];

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

bool uni(int x) {
    x = find(x);
    if (x == 0) return false;
    p[x] = x - 1;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int G, P, cnt = 0;
    memset(p, -1, sizeof(p));
    cin >> G >> P;
    for(int i = 0; i < P; i++) {
        int num; cin >> num;
        if (uni(num)) cnt++;
        else break;
    }
    cout << cnt << endl;
}