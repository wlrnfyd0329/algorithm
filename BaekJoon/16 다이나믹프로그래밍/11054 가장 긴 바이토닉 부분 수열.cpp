// 이분탐색으로 풀었던 문제를 dp로도 풀 수 있는데, 
// DP는 시간 복잡도가 O(N^2)라서 이분탐색을 알고 사용하는 것이 좋아보임
// 하지만 아래와 같은 문제는 DP문제가 맞다. 두가지 경우를 모두 살펴야 하기 때문이다.
// 내가 작아질 때, 커지고 있는데 작아지고 있는 건지, 작아지고 있었는데, 어떤 것이 최선인지 모르기 때문이다.
// 뒤에 꼬리가 길어질때는 계속 커질때와 계속 작아질때가 있는데, 커졌다가 작아지는 곳이 분기점으로 생각해야 한다.

// 아래와 같은 방법으로도 풀 수 있다.
// 가장 긴 바이토닉 부분 수열을 구하기 위해서는
// 1. 가장 긴 증가하는 부분 수열을 왼쪽에서 오른쪽으로 구한다.
// 2. 가장 긴 증가하는 부분 수열을 오른쪽에서 왼쪽으로 구한다.
// 3. 1번과 2번의 각 자리를 더한 값 중 최대값을 구한다.
// 4. 최대값에서 -1을 뺀다. (값이 중복되기 때문이다.)

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n;
int arr[1005];
int up[1005];
int down[1005];

int solution() {
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (up[i] < up[j] + 1)
					up[i] = up[j] + 1;
            }
            if (arr[j] > arr[i]) {
                int value = max(up[j], down[j]) + 1;
                if (down[i] < value)
                    down[i] = value;
            }
        }
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
        ans = max({ans, up[i], down[i]});
    }
	return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {   
        cin >> arr[i];
        up[i] = 1;   
        down[i] = 1;
    }

    cout << solution();
}