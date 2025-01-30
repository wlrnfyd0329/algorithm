#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    vector<int> v;
    cin >> n >> k;
    int index = k - 1;
    for(int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    cout << "<" << v[index];
    while(!v.empty()) {
        v.erase(v.begin() + index);
        if (v.empty()) {
            cout << ">";
            break;
        }
        index += k - 1;
        index %= v.size();
        cout << ", " << v[index];
    }
}