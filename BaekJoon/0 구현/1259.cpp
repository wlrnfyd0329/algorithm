#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        string num;
        bool isRight = true;
        cin >> num;
        if (num == "0") break;
        for(int i = 0; i < num.size() / 2; i++) {
            if (num[i] != num[num.size() - 1 - i]) {
                isRight = false;
                break;
            }
        }
        if (isRight) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
}