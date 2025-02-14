// 첫번째 날에 A가 열쇠를 가지고 있다! 반드시 첫날에는 A가 있어야 함

#include <iostream>
#include <algorithm>
#include <set>
#include <bitset>

using namespace std;

const int div_num = 1'000'000'007;
int arr[10001][16];

int trans(char c) {
    switch (c)
    {
    case 'A':
        return 8;
    case 'B':
        return 4;
    case 'C':
        return 2;
    case 'D':
        return 1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        fill(arr[0], arr[10000], 0);
        int result = 0;
        string s;
        cin >> s;

        arr[0][trans('A')]++; // 1일차에 꼭 있어야 하는 친구들

        for(int i = 1; i <= s.size(); i++) {
            //cout << "day :" << i << "\n";
            for(int j = 1; j < 16; j++) {
                if (arr[i - 1][j]) { // 전회차에 있던 조합
                    int check[16] = {0, };
                    //cout << "last :" << bitset<4> (j) << " now : ";
                    for (int k = 1; k < 16; k++) {
                        if ((k & j) > 0) { // 그걸로 만들 수 있는 조합
                            int num = trans(s[i-1]) | k;
                            check[num] = 1;
                        }
                    }

                    for(int k = 1; k < 16; k++) {
                        if (check[k]) {
                            //cout << bitset<4> (k) << " ";
                            arr[i][k] += arr[i-1][j];
                            arr[i][k] %= div_num;
                        }   
                    }
                    //cout << "\n";
                }
            }
            //cout << "\n";
        }

        for(int i = 1; i < 16; i++) {
            result += arr[s.size()][i];
            result %= div_num;
        }

        cout << "#" << tc << " " << result << "\n";
    }
}
