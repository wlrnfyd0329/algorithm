#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int n;

struct cmp {
    bool operator()(int a, int b) {
        if (abs(a) != abs(b)) return abs(a) > abs(b);
        else a > 0 && b < 0;
        // if (abs(a) > abs(b)) {
        //     return true;
        // }
        // else if (abs(a) == abs(b)) {
        //     if (a > b) return true;
        //     else return false;
        // }
        // return false;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    priority_queue<int, vector<int>, cmp> pq; // 그냥 선언하면 최대 힙, 이렇게 해야지 최소 힙
    cin >> n;
    for(int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (tmp == 0) {
            if (pq.empty()) cout << 0 << "\n";
            else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
        else {
            pq.push(tmp);
        }
    }
}