#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int n, k, cnt;
deque<int> DQ;
deque<bool> robot;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i = 0; i < 2 * n; i++) {
        int temp;
        cin >> temp;
        DQ.push_back(temp);
    }
    for(int i = 0; i < n; i++) {
        robot.push_back(false);
    }
    while(true) {
        cnt++;
        int temp;
        temp = DQ.back(); DQ.pop_back();
        DQ.push_front(temp);
        robot.pop_back();
        robot.push_front(false);
        robot[n - 1] = false;

        for(int i = n - 2; i >= 0; i--) {
            if (!robot[i + 1] && robot[i] && DQ[i + 1]) {
                robot[i + 1] = robot[i];
                DQ[i + 1]--;
                robot[i] = false;
                robot[n - 1] = false;
            }
        }

        if(DQ[0]) {
            robot[0] = true;
            DQ[0]--;
        }
        
        int cnt0 = 0;
        for(int i = 0; i < 2 * n; i++) {
            if(DQ[i] == 0) cnt0++;
        }
        if(cnt0 >= k) break;
    }
    cout << cnt;
}

/*
그냥 구현 노가다 문제인듯함
*/
