#include <iostream>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    deque<int> dq;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int cmd, x;
        cin >> cmd;
        switch (cmd) {
            case 1:
                cin >> x;
                dq.push_front(x);
                break;
            case 2:
                cin >> x;
                dq.push_back(x);
                break;
            case 3:
                if (dq.empty()) {
                    cout << -1 << "\n";
                }
                else {
                    cout << dq.front() << "\n";
                    dq.pop_front();
                }
                break;
            case 4:
                if (dq.empty()) {
                    cout << -1 << "\n";
                }
                else {
                    cout << dq.back() << "\n";
                    dq.pop_back();
                }
                break;
            case 5:
                cout << dq.size() << "\n";
                break;
            case 6:
                if (dq.empty()) {
                    cout << 1 << "\n";
                }
                else {
                    cout << 0 << "\n";
                }
                break;
            case 7:
                if (dq.empty()) {
                    cout << -1 << "\n";
                }
                else {
                    cout << dq.front() << "\n";
                }
                break;
            case 8:
                if (dq.empty()) {
                    cout << -1 << "\n";
                }
                else {
                    cout << dq.back() << "\n";
                }
                break;
        }
    }
}