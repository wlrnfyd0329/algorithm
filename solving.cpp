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