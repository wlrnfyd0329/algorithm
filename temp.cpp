#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

struct Player {
	int ID;
	int Ability;
    bool isExist = true;
    Player(int id, int ability) : ID(id), Ability(ability) {}
	bool operator<(const Player& other) const {
		if (Ability == other.Ability) {
			return ID < other.ID;
		}
		return Ability > other.Ability;
	}
};
vector<set<Player>> v;

vector<Player> user;
queue<Player> info_store;
vector<Player> info;

int main() {
    info.push_back(Player(1, 1));
    cout << info[0].isExist << " " << &info[0] << "\n";
    info_store.push(info[0]);
    info[0].isExist = false;
    cout << info[0].isExist << " " << &info[0] << "\n";

    cout << info_store.front().isExist << " " << &info_store.front() << "\n";
    user.push_back(info_store.front());
    cout << user[0].isExist << " " << &user[0] << "\n";
    

    set<Player> s;

    s.insert({3, 8});
    s.insert({4, 7});
    s.insert({2, 6});
    s.insert({1, 5});
    s.insert({9, 5});

    cout << &s << "\n";
    for(auto iter = s.begin(); iter != s.end(); iter++) {
        cout << &*iter << "\n";
    }
    cout << "\n";

    Player temp = *s.begin();

    cout << &temp << " " << &*s.begin();
}   
