#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <bitset>

using namespace std;

void combination(int now, int cnt, int status) {
    if (cnt == 3) {
        cout << bitset<5>(status) << "\n";
        return;
    }

    for(int i = now; i < 5; i++) {
        combination(i + 1, cnt + 1, status | (1 << i));
    }
}

struct A
{
    int a = 1;
    int b = 2;
};

set<int> s;
vector<A> v;


int main() {
    // int lf = 1;
    // long long rg = (1 << 31) - 1;
    // int mid = (lf + rg) >> 1;
    // cout << mid;
    // if (s.lower_bound(0) == s.end()) {
    //     cout<< 1;
    // }
    // else {
    //     cout << 0;
    // }
    // v = vector<A> (3);
    // cout << v[0].b;
    // queue<int> q1;
    // q1.push(1);
    // q1.push(2);
    // cout << q1.front() << endl;
    // queue<int> q2 = q1;
    // queue<int> q3(q1);
    // cout << q2.front() << endl;
    // cout << q3.front() << endl;
    // q1.pop();
    // cout << q1.front() << endl;
    // cout << q2.front() << endl;
    // cout << q3.front() << endl;
    bitset<5> bit = 5;
    cout << bit << endl;
    bit.set(3);
    cout << bit;
}   
