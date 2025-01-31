#include <iostream>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int a[100005];
    deque<int> dq;
    int m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a[i] = tmp;
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (a[i] == 0) {
            dq.push_back(tmp);
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int tmp;
        cin >> tmp;
        dq.push_front(tmp);
        cout << dq.back() << " ";
        dq.pop_back();
    }

}
