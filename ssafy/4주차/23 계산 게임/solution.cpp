#include <deque>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

deque<int> dq;
unordered_map<int, vector<int>> m[6];
int forder = 0;
int border = 0;
int joker = 0;

void init(int mJoker, int mNumbers[5])
{
	dq.clear();
	for (int i = 0; i < 6; i++) {
		m[i].clear();
	}
	forder = 0;
	border = 0;
	joker = mJoker;
	for (int i = 0; i < 5; i++) {
		dq.push_back(mNumbers[i]);
	}
	for (int i = 0; i < 2; i++) {
		int value = 0;
		int joker_cnt = 0;
		for (int j = 0; j < 4; j++) {
			if (dq[i + j] == -1) {
				joker_cnt++;
			}
			else {
				value += dq[i + j];
			}
		}
		m[joker_cnt][value % 20].push_back(border++);
	}
}

void putCards(int mDir, int mNumbers[5])
{
	if (mDir == 1) {
		for (int i = 0; i < 5; i++) {
			dq.push_back(mNumbers[i]);
			int value = 0;
			int joker_cnt = 0;
			for (int j = dq.size() - 4; j < dq.size(); j++) {
				if (dq[j] == -1) {
					joker_cnt++;
				}
				else {
					value += dq[j];
				}
			}
			m[joker_cnt][value % 20].push_back(border++);
		}
	}
	else {
		for (int i = 4; i >= 0; i--) {
			dq.push_front(mNumbers[i]);
			int value = 0;
			int joker_cnt = 0;
			for (int j = 0; j < 4; j++) {
				if (dq[j] == -1) {
					joker_cnt++;
				}
				else {
					value += dq[j];
				}
			}
			m[joker_cnt][value % 20].push_back(--forder);
		}
	}
}

int findNumber(int mNum, int mNth, int ret[4])
{
	vector <int> v;
	for (int i = 0; i < 6; i++) {
		int search = mNum - (joker * i) % 20;
		if (search < 0) search += 20;
		v.insert(v.end(), m[i][search].begin(), m[i][search].end());
	}
	if (v.size() < mNth) return 0;
	else {
		sort(v.begin(), v.end());
		for (int i = 0; i < 4; i++) {
			ret[i] = dq[v[mNth - 1] - forder + i];
		}
		return 1;
	}
}

void changeJoker(int mValue)
{
	joker = mValue;
}