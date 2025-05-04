// 에라토스테네스의 채를 활용한 문제다.
// 에라토스테네스의 채의 시간복잡도는 O(NloglogN)이다

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int N;
vector<int> arr; // 플레이어 카드
vector<bool> get_num(1'000'005, 0);
vector<int> ans(1'000'005, 0); // 수에 따른 점수

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 0; i < N; i++) {
        int num; cin >> num;
        get_num[num] = true;
        arr.push_back(num);
    }

    for(int i = 0; i < N; i++) {
        for (int j = 2; arr[i] * j <= 1'000'000; j++) {
            if (get_num[arr[i] * j]) {
                ans[arr[i]]++;
                ans[arr[i] * j]--;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        cout << ans[arr[i]] << " ";
    }
}