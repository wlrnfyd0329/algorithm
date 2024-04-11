#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

queue<int> q, q1;

int main() {
    q.push(1);
    q.push(2);
    q1 = q;
    q.pop();
    cout << q.size() << " " << q1.size();
}   
