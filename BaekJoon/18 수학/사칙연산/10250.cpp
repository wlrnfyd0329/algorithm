#include <iostream>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int H, W, N;
        cin >> H >> W >> N;
        if (N % H == 0) {
            cout << H;
            if (N / H < 10) {
                cout << 0 << N / H << endl;
            }
            else {
                cout << N / H << endl;
            }
        }
        else {
            cout << N % H;
            if (N / H < 9) {
                cout << 0 << N / H + 1 << endl;
            }
            else {
                cout << N / H + 1 << endl;
            }
        }
    }
}