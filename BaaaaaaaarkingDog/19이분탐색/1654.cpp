#include <iostream>

using namespace std;

int K, N;
int line[10005];
int max_len = 0;

bool isPossible(int target) {
    int cnt = 0;
    for(int i = 0; i < K; i++) {
        cnt += line[i] / target;
    }

    if (cnt >= N) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K >> N;
    for(int i = 0; i < K; i++) {
        cin >> line[i];
        max_len = max(max_len, line[i]);
    }
    long long lf = 1, rg = max_len;
    while(lf <= rg) {
        long long mid = (lf + rg) >> 1;
        if (isPossible(mid)) {
            lf = mid + 1;
        }  
        else {
            rg = mid - 1;
        }
    }
    cout << rg;
}