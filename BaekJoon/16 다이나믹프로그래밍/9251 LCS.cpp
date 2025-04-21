// 유명한 LCS 문제다.
// 최장 공통 문자열(계속 이어져야 함), 최장 공통 부분수열(끊어져도 됨) 알고리즘 둘 다 lcs 알고리즘이라고 불린다.
// 또한 역추적하여 부분수열을 찾을 수 있어야 한다.

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int arr[1005][1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s1, s2;
    cin >> s1 >> s2;
	int ans = 0;
	for(int i = 1; i <= s1.size(); i++) {
		for(int j = 1; j <= s2.size(); j++) {
			if (s1[i - 1] == s2[j - 1]) {
				arr[i][j] = arr[i - 1][j - 1] + 1;
			}
			else {
				arr[i][j] = max(arr[i - 1][j] , arr[i][j - 1]);
			}
			ans = max(ans, arr[i][j]);
		}
	}
	cout << ans;
}