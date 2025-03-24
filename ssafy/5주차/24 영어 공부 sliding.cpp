#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"

using namespace std;

int main() {
	ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        int N, P; cin >> N >> P;

        int start = 0, end = 0;
        int last = 0, p = P;
        vector<int> check(1200001, 0);

        for (int i = 0; i < N; i++) {
            int num; cin >> num;

            check[num] = 1;
            last = num;
        }

        int max_v = 0;
        int len = 0;

        while (end <= last + P) {

            if (check[end] == 1) {
                len++;
                end++;
                max_v = max(len, max_v);
            }
            else {
                if (p != 0) {
                    p--;
                    len++;
                    end++;
                    max_v = max(len, max_v);
                }
                else {
                    if (check[start] == 0) p++;
                    len--;
                    start++;
                }
            }
        }

        cout << "#" << tc << " " << max_v << endl;
    }

    return 0;
}