#include <iostream>
#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int start, flag;
    cin >> start;
    if (start == 1) {
        flag = 1;
    }
    else if (start == 8) {
        flag = -1;
    }
    else {
        cout << "mixed";
        return 0;
    }
    for(int i = 0; i < 7; i++) {
        int num;
        cin >> num;
        if (flag > 0) {
            if (start + 1 != num) {
                cout << "mixed";
                return 0;
            }
            start = num;
        }
        else {
            if (start - 1 != num) {
                cout << "mixed";
                return 0;
            }
            start = num;
        }
    }
    if (flag > 0) {
        cout << "ascending";
    }
    else {
        cout << "descending";
    }
}