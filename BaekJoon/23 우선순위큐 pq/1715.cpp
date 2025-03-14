#include <iostream>
#include <queue>
#include <functional>

using namespace std;

int n, result;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    priority_queue<int, vector<int>, greater<int>> pq;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        pq.push(tmp);
    }
    while(pq.size() != 1) {
        int first, second;
        first = pq.top();
        pq.pop();
        second = pq.top();
        pq.pop();
        pq.push(first + second);
        result += first + second;
    }
    cout << result;
}