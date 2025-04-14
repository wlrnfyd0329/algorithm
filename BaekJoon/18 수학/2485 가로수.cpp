#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int Euclidean(int a, int b) {
	int r = a % b;
	if (r == 0)
		return b;
	else
		return Euclidean(b, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    vector<int> v, dis;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    for (int i = 1; i < n; i++) {
        dis.push_back(v[i] - v[i-1]);
    }
    
    sort(dis.begin(), dis.end());

    int num = dis[0];
    for (int i = 1; i < n - 1; i++) {
        num = Euclidean(num, dis[i]);
    }

    int result = 0;
    for (int i = 0; i < n-1; i++) {
        result += dis[i] / num - 1;
    }

    cout << result;

    
}
// 유클리드 호제법을 알아야만 해결 가능함