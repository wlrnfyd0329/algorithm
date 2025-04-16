#include <iostream>
#include <string>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    int total = 0;
    int sum = 0;
    int flag = 1;
    string num = "";
    for(int i = 0; i < s.size(); i++) {
        if (s[i] == '+') {
            sum += stoi(num);
            num = "";
        }
        else if (s[i] == '-') {
            sum += stoi(num);
            num = "";
            total += flag * sum;
            sum = 0;
            flag = -1;
        }
        else {
            num += s[i];
        }
    }
    sum += stoi(num);
    total += flag * sum;
    cout << total;
}