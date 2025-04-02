#include <iostream>
#include <string>
#define endl "\n"

using namespace std;

void init() {

}

void insert() {

}

void remove() {

}

void ranking() {

}

void sum() {

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T; 
    for(int i = 0; i < T; i++) {
        string cmd; cin >> cmd;
        if (cmd == "init") {
            init();
        }
        if (cmd == "insert") {
            insert();
        }
        if (cmd == "delete") {
            remove();
        }
        if (cmd == "rank") {
            ranking();
        }
        if (cmd == "sum") {
            sum();
        }
    }
}