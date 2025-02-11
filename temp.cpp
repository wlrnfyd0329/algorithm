#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<pair<int, int>> v[4];
set<int> s;


int main() {
    cout << v[1].size();
    s.insert(1);
    s.insert(50);
    s.insert(3);
    s.clear();
    for(auto k : s) {
        cout << k <<" ";
    }
}   
