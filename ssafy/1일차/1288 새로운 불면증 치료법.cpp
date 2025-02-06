#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        long long n;
        int x = 1;
        bool isFinish = false;
        bool arr[10];
        fill(arr, arr + 10, 0);
        cin >> n;
        while (!isFinish) {
            int num = x++ * n;
            while(num / 10 != 0) {
                arr[num % 10] = 1;
                num /= 10;
            }
            arr[num] = 1;
            isFinish = true;
            for(int i = 0; i < 10; i++) {
                isFinish = isFinish && arr[i];
            }
        }
        cout << "#" << tc << " " << --x * n << "\n";
    }
}