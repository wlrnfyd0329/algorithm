#include <iostream>
#include <vector>
#include <string>
#define endl "\n"

using namespace std;

int N, M;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> s;
	int k = 0, ans = 0;
	for(int i = 0; i < M - 2; i++) {
		if (s[i] == 'I' && s[i + 1] == 'O' && s[i + 2] == 'I') {
			i++;
			if (++k == N) {
				k--;
				ans++;
			}
		}
		else {
			k = 0;
		}
	}

	cout << ans;
}