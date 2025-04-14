#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define N 1000001

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;

    bool arr[N]; // int는 25만이 한계인데 bool은 1byte니까 100만까지 가능능

	for(int i=0; i<N; i++) {
		arr[i] = true;
	}

	arr[0] = arr[1] = false;

    for(int i=2; i*i<N; i++) {
		if(arr[i]) {
			for(int j=i*2; j<=N; j+=i) {
				arr[j] = false;
			}
		}
	}
    
    for(int i = 0; i < t; i++) {
        int n, partition = 0;
        cin >> n;
        for (int i = 2; i <= n / 2; i++) {
            if (arr[i] && arr[n - i]) {
                partition++;
            }
        }
        cout << partition << "\n";
    }
}

// 에라토스테네스 체