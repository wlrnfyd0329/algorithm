#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

long long divide(long long A, long long B) {
    if (A % B == 0)
        return B;
    else
        return divide(B, A % B);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a, b;
    cin >> a >> b;

    long long common;
    if (a > b) {
        common = divide(a, b);
    }
    else {
        common = divide(b, a);
    }

    cout << common << endl << a * b / common;
}