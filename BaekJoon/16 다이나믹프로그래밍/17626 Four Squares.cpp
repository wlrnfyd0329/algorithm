// 점화식은 제곱한 수에 1을 더한 것이 되는데, 
// 주어진 수보다 가장 큰 제곱수만 찾아서 더해주면 정해가 아닐 수 있다.
// 23 = 16 + 4 + 1 + 1 + 1 = 9 + 9 + 4 + 1 이 더 좋을 수 있는 것이다.
// 따라서 자기보다 작은 제곱수를 전부 살피는 것이 포인트이다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n;
int v[50'005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= 223; i++) {
        v[i * i] = 1;
    }
    for(int i = 1; i <= n; i++) {
        if (v[i] != 0) continue;
        for(int j = 1; j * j <= i; j++) {
            if (v[i] == 0) {
                v[i] = v[j * j] + v[i - j * j];
            }
            else {
                v[i] = min(v[i], v[j * j] + v[i - j * j]);
            }
        }
    }
    cout << v[n];
}