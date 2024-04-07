#include <iostream>

using namespace std;

int n, a[1000005], b, c;
long long result;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    result += n;
    for(int i = 0; i < n; i++) cin >> a[i];
    cin >> b >> c;
    for(int i = 0; i < n; i++) {
        int temp = a[i] - b;
        if (temp > 0) {
            if (temp % c == 0)
                result += temp / c;
            else
                result += temp / c + 1;
        }
    }
    cout << result;
}

/*
반례
1000000
1000000 ... 1000000
1 1

int 값을 초과한다.
int 값은  -2,147,483,648 ~ 2,147,483,647
0이 9개
long long 값은 최대 -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
0이 18개

자료형 명심하자
*/