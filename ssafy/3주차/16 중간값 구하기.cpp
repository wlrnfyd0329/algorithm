// vector를 쓰게된다면 매번 sort 해주기 때문에 시간초과 날 것이다.
// 따라서 최대힙, 최소힙을 사용해서 중간값을 찾아야 한다.
// 중간값보다 작은 값은 최대 힙에 큰 값은 최소 힙에 넣고 중간값을 조절하면 된다.
// 역시 알고리즘은 많이 푸는게 장땡이다. 왜냐면 모르면 틀려야 하기 때문이다.

#include <iostream>
#include <queue>

using namespace std;

const int divdie = 20'171'109;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        priority_queue<int> max_pq;
        priority_queue<int, vector<int>, greater<int>> min_pq;
        int sum = 0;
        int n, mid;
        cin >> n >> mid;
        for(int i = 0; i < n * 2; i++) {
            int x;
            cin >> x;
            if (max_pq.size() < min_pq.size()) { // 큰쪽이 더 많다
                if (x < mid) {
                    max_pq.push(x);
                }
                else { // mid <= x
                    max_pq.push(mid);
                    mid = x;
                    while(mid > min_pq.top()) {
                        int tmp = min_pq.top();
                        min_pq.pop();
                        min_pq.push(mid);
                        mid = tmp;
                    }
                }
            }
            else if (max_pq.size() > min_pq.size()) { // 작은쪽이 더 많다
                if (x < mid) {
                    min_pq.push(mid);
                    mid = x;
                    while(mid < max_pq.top()) {
                        int tmp = max_pq.top();
                        max_pq.pop();
                        max_pq.push(mid);
                        mid = tmp;
                    }
                }
                else { // mid <= x
                    min_pq.push(x);
                }
            }
            else {
                if (x < mid) {
                    max_pq.push(x);
                }
                else { // mid <= x
                    min_pq.push(x);
                }
            }
            if (i % 2 != 0) {
                sum += mid;
                sum %= divdie;
            }
        }

        cout << "#" << tc << " " << sum << endl;
    }
}