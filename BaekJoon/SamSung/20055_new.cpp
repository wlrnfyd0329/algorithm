#include <iostream>
#include <deque>

using namespace std;

int n, k;
deque<pair<int, bool>> belt;

void rotation() {
    belt.push_front(belt.back());
    belt.pop_back();
    belt[n-1].second = false;
}

void robot_move() {
    for(int i = n - 2; i >= 1; i--) {
        if (belt[i].second && belt[i+1].first != 0 && !belt[i+1].second) {
            belt[i+1].first--;
            if(belt[i+1].first == 0) k--;
            belt[i+1].second = true;
            belt[i].second = false;
        }
        belt[n-1].second = false;
    }

}

void robot_up() {
    if (belt[0].first != 0) {
        belt[0].first--;
        if(belt[0].first == 0) k--;
        belt[0].second = true;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int turn = 0;
    cin >> n >> k;

    for(int i = 0; i < 2 * n; i++) {
        int durability;
        cin >> durability;
        belt.push_back({durability, false});
    }

    while(k > 0) {
        turn++;
        rotation();
        robot_move();
        robot_up();
    }

    cout << turn;
}