// int가 아니라 long long 범위였다. 최악의 범위를 항상 상정하자

#include <iostream>
#include <vector>
#define endl "\n"

typedef long long ll;
using namespace std;

int T, N, max_v = 100;
vector<int> v;
vector<ll> p;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> N;
        v.push_back(N);
        max_v = max(max_v, N);
    }
    
    p = vector<ll> (max_v + 1);
    for(int i = 0; i < 3; i++) p[1 + i] = 1;
    for(int i = 0; i < 2; i++) p[4 + i] = 2;
    int left = 1, right = 5;
    for(int i = 6; i <= max_v; i++) {
        p[i] = p[left++] + p[right++];
    }

    for(int i = 0; i < T; i++) {
        cout << p[v[i]] << endl;
    }
}