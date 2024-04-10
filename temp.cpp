#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d[0] = 3;
    cout << d[0] << d[1];
}
