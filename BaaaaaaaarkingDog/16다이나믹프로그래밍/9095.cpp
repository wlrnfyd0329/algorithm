#include <iostream>
#include <algorithm>

using namespace std;

int a[15];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    a[1] = 1;
    a[2] = 2;
    a[3] = 4;
    for (int i = 4; i < 11; i++) {
        a[i] = a[i-1] + a[i-2] + a[i-3];
    }

    int num, tmp;
    cin >> num;
    for(int i = 0; i < num; i++) {
        cin >> tmp;
        cout << a[tmp] << "\n";
    }
}