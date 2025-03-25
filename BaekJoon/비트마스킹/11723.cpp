#include <iostream>
#include <string>
#include <bitset>
#define endl "\n"

using namespace std;

int s = 0;

void add(int n) {
    s |= (1 << n);
}

void remove(int n) {
    s &= ~(1 << n);
}

void check(int n) {
    if ((s & (1 << n)) > 0) cout << 1 << endl;
    else cout << 0 << endl;
}

void toggle(int n) {
    s ^= (1 << n);
}

void all() {
    s = (1 << 21) - 1;
}

void empty() {
    s = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int M; cin >> M;
    for(int i = 0; i < M; i++) {
        string cmd;
        int num;
        cin >> cmd;
        if (cmd == "add") {
            cin >> num;
            add(num);
        }
        if (cmd == "remove") {
            cin >> num;
            remove(num);
        }
        if (cmd == "check") {
            cin >> num;
            check(num);
        }
        if (cmd == "toggle") {
            cin >> num;
            toggle(num);
        }
        if (cmd == "all") all();
        if (cmd == "empty") empty();
    }
}