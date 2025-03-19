#include <iostream>
#include <cmath>
#include <algorithm>
#define endl "\n"

using namespace std;

int n, person;
double sum = 0;
int arr[300'005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    if (n == 0) cout << 0;
    else {
        person = round(n * 0.15);
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        sort(arr, arr + n);

        for(int i = person; i < n - person; i++) {
            sum += arr[i];
        }

        cout << round(sum / (n - 2 * person));
    }
}