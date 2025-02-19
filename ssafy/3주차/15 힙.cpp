#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        priority_queue<int> pq;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            int cmd;
            cin >> cmd;
            if (cmd == 1) {
                int x;
                cin >> x;
                pq.push(x);
            }
            if (cmd == 2) {
                if (pq.empty()) {
                    cout << -1 << " ";
                }
                else {
                    cout << pq.top() << " ";
                    pq.pop();
                }
            }
        }
        cout << endl;
    }

}