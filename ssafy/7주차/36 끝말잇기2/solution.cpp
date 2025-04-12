// 사용하지 않았는데 중복될 가능성이 있는 것을 간과 했다...

#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11

using namespace std;

int n;
bool user[MAX_N + 5]; // false면 살아 있음, true면 죽음
priority_queue<string, vector<string>, greater<string>> s[26];
unordered_map<string, int> word_list;

inline int c2i(char c) {
	return c - 'a';
}

void init(int N, int M, char mWords[][MAX_LEN])
{
	n = N;
	for (int i = 1; i <= N; i++) user[i] = false;
	for (int i = 0; i < 26; i++) s[i] = priority_queue<string, vector<string>, greater<string>>();
	word_list.clear();
	for (int i = 0; i < M; i++) {
		string word(mWords[i]);
		s[c2i(word.front())].push(word);
		word_list[word] = 1;
	}
}

int playRound(int mID, char mCh)
{
	vector<string> v;
	v.push_back(s[c2i(mCh)].top());
	word_list[s[c2i(mCh)].top()] = -1;
	s[c2i(mCh)].pop();
	while (1) {
		if (++mID > n) mID = 1;
		if (user[mID]) continue;
		int target = c2i(v.back().back());
		if (s[target].empty()) {
			user[mID] = true;
			break;
		}
		else {
			v.push_back(s[target].top());
			word_list[s[target].top()] = -1;
			s[target].pop();
		}
	}

	for (auto k : v) {
		int target = c2i(k.back());
		reverse(k.begin(), k.end());
		if (word_list[k] == 0) {
			s[target].push(k);
		}
	}

	return mID;
}