// 투포인터 문제다. 항상 투포인터 문제를 풀때마다 생각이 드는 것이지만
// 반복 한번에 꼭 포인터를 하나씩 움직일 필요가 없다.
// 하나를 증가시켰으면 다른 조건을 만족할때까지 다른 반복문을 안에 넣어도 된다.
#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int N, S, sum, ans = 200'000;
vector<int> num;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    for(int i = 0; i < N; i++) {
        int n; cin >> n;
        num.push_back(n);
    }
    int lf = 0, rg = 0;
    sum = 0;
    while((rg < N) || (sum >= S)) {
        if (sum >= S) {
            ans = min(ans, rg - lf);
            sum -= num[lf++];
        }
        else {
            sum += num[rg++];
        }
    }

    // while(rg < N) {
    //     sum += num[rg++];
    //     while(sum >= S) {
    //         ans = min(ans, rg - lf);
    //         sum -= num[lf++];
    //     }
    // }

    cout << (ans == 200'000 ? 0 : ans);
}