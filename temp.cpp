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

	bool operator<(const Player& other) const {
		if (Ability == other.Ability) {
			return ID < other.ID;
		}
		return Ability > other.Ability;
	}
};
vector<set<Player>> v;


int main() {
    short tmp = 1 << 15;
    cout << --tmp << "\n";

    cout << ceil(log2(1000000));
    cout << (1 << 21) << "\n";

    set<Player> s;
    cout << s.size() << "\n";
    s.insert({3, 8});
    s.insert({4, 7});
    s.insert({2, 6});
    s.insert({1, 5});
    s.insert({9, 5});

    for(auto k : s) {
        cout << k.ID << " " << k.Ability << "\n";
    }
    cout << "\n";

    Player temp = *s.begin();
    s.erase(s.begin());

    for(auto k : s) {
        cout << k.ID << " " << k.Ability << "\n";
    }
    cout << "\n";
    cout << temp.ID << " " << temp.Ability;
}   
