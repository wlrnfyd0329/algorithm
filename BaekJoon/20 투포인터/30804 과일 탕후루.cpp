// 투포인터의 움직임을 유연하게 처리해야 할 것 같다.
// while문을 두개를 사용할 수 있다. 첫번째 while은 그냥 en를 증가만 시켜주고
// type의 개수가 2개를 초과하면 2개 이하가 될때까지 빼준다.
// 큐를 사용해서 입력이 들어올때마다 처리해주는 방법도 사용할 수 있다.

#include <iostream>
#include <vector>
#include <queue>
#define endl "\n"

using namespace std;

int n;
vector<int> v;
int cnt[10];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num; cin >> num;
		v.push_back(num);
	}

	int type = 1, ans = 0;
	int st = 0, en = 1;
	cnt[v[st]] = 1;
	while (en < n) {
		if (type <= 2) {
			if (!cnt[v[en]]++) {
				if(++type > 2) continue;
			}
			en++;
		}
		else {
			ans = max(ans, en - st);
			if (--cnt[v[st++]] == 0) {
				type--;
				en++;
			}
		}
	}

	cout << max(ans, en - st);
}