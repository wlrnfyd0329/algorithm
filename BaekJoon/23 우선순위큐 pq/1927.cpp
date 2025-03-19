#include <iostream>
#include <queue>
#define endl "\n"

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        if (num == 0) {
            if (pq.empty()) cout << 0 << endl;
            else {
                cout << pq.top() << endl;
                pq.pop();
            }
        }
        else {
            pq.push(num);
        }
    }
}