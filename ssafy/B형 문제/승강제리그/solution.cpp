#include <set>
#include <vector>
#include <iostream>
using namespace std;

int n, l;
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
vector<set<Player>> frontV;
vector<set<Player>> backV;

void add(Player p, int team) {
	if (frontV[team].size() > backV[team].size()) {
		backV[team].insert(p);
		if ((--frontV[team].end())->Ability <= backV[team].begin()->Ability) {
			frontV[team].insert(*backV[team].begin());
			backV[team].erase(backV[team].begin());
			backV[team].insert(*--frontV[team].end());
			frontV[team].erase(--frontV[team].end());
		}
	}
	else {
		frontV[team].insert(p);
		if ((--frontV[team].end())->Ability <= backV[team].begin()->Ability) {
			frontV[team].insert(*backV[team].begin());
			backV[team].erase(backV[team].begin());
			backV[team].insert(*--frontV[team].end());
			frontV[team].erase(--frontV[team].end());
		}
	}
}

void init(int N, int L, int mAbility[])
{
	n = N;
	l = L;
	frontV.clear();
	backV.clear();
	for (int team = 0; team < L; team++) {
		set<Player> s;
		for (int i = 0; i < N / L; i++) {
			int idx = i + (N / L) * team;
			s.insert({idx, mAbility[idx]});
		}
		set<Player> frontS;
		set<Player> backS;
		int idx = 0;
		for (auto k : s) {
			if (idx < (n / l + 1) / 2) {
				frontS.insert(k);
			}
			else {
				backS.insert(k);
			}
			idx++;
		}
		frontV.push_back(frontS);
		backV.push_back(backS);
	}
}

int move()
{
	int ans = 0;
	Player lower[11];
	Player higher[11];
	for (int team = 0; team < l - 1; team++) {
		auto lower_iter = --backV[team].end();
		lower[team] = *lower_iter;
		backV[team].erase(lower_iter);
		higher[team + 1] = *frontV[team + 1].begin();
		frontV[team + 1].erase(frontV[team + 1].begin());
	}

	for (int team = 0; team < l - 1; team++) {
		ans += lower[team].ID + higher[team + 1].ID;
		add(higher[team + 1], team);
		add(lower[team], team + 1);
	}
	return ans;
}

int trade()
{
	int ans = 0;
	Player middle[11];
	Player higher[11];
	middle[0] = *--frontV[0].end();
	frontV[0].erase(--frontV[0].end());

	for (int team = 1; team < l - 1; team++) {
		middle[team] = *--frontV[team].end();
		higher[team] = *frontV[team].begin();
		frontV[team].erase(--frontV[team].end());
		frontV[team].erase(frontV[team].begin());
	}
	higher[l - 1] = *frontV[l - 1].begin();
	frontV[l - 1].erase(frontV[l - 1].begin());

	for (int team = 0; team < l - 1; team++) {
		ans += middle[team].ID + higher[team + 1].ID;
		add(higher[team + 1], team);
		add(middle[team], team + 1);
	}
	return ans;
}