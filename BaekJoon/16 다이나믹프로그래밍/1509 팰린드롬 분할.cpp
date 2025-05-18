#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#define endl "\n"

using namespace std;

string s;
int dp[2505];
bool table[2505][2505];

void func() {
    int N = s.size();
    for(int i = 1; i <= N; i++) {
        int lf = i, rg = i;
        while(lf >= 1 && rg <= N) {
            if (s[lf - 1] == s[rg - 1]) {
                table[lf][rg] = true;
                lf--;
                rg++;
            }
            else {
                break;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        int lf = i, rg = i + 1;
        while(lf >= 1 && rg <= N) {
            if (s[lf - 1] == s[rg - 1]) {
                table[lf][rg] = true;
                lf--;
                rg++;
            }
            else {
                break;
            }
        }
    }

    for(int end = 1; end <= N; end++) {
        dp[end] = 2e9;
        for(int start = 1; start <= end; start++) {
            if (table[start][end]) {
                dp[end] = min(dp[end], dp[start - 1] + 1);
            }
        }
    }

    cout << dp[N];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    func();

}