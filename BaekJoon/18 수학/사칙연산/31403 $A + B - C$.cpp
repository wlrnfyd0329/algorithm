#include <iostream>
#include <string>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a, b, c;
    cin >> a >> b >> c;
    cout << a + b - c << endl;
    cout << stoi(to_string(a) + to_string(b)) - c << endl;
}