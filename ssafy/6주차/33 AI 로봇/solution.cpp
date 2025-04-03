#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct AI {
	int id;
	int intell = 0; // 지능
	int time = 0;   // training 시작 시간
	int status = 1; // broken : 0, working : -wId, training : 1
};
vector<AI> robot;
unordered_map<int, queue<int>> work;

struct up {
	bool operator() (const AI &a, const AI &b) const {
		if (a.time == b.time) {
			if (a.intell == b.intell) return a.id > b.id;
			return a.intell < b.intell;
		}
		else if (a.time > b.time) {
			if (a.intell - b.intell == a.time - b.time) return a.id > b.id;
			return a.intell - b.intell < a.time - b.time;
		}
		else {
			if (b.time - a.time == b.intell - a.intell) return a.id > b.id;
			return b.time - a.time < b.intell - a.intell;
		}
	}
};
priority_queue<AI, vector<AI>, up> up_pq;
struct down {
	bool operator() (const AI &a, const AI &b) const {
		if (a.time == b.time) {
			if (a.intell == b.intell) return a.id > b.id;
			return a.intell > b.intell;
		}
		else if (a.time > b.time) {
			if (a.intell - b.intell == a.time - b.time) return a.id > b.id;
			return a.intell - b.intell > a.time - b.time;
		}
		else {
			if (b.time - a.time == b.intell - a.intell) return a.id > b.id;
			return b.time - a.time > b.intell - a.intell;
		}
	}
};
priority_queue<AI, vector<AI>, down> down_pq;

void init(int N)
{
	work.clear();
	up_pq = {};
	down_pq = {};
	robot = vector<AI>(N + 1);
	for (int i = 1; i <= N; i++) {
		robot[i] = { i, 0, 0, 1 };
		up_pq.push(robot[i]);
		down_pq.push(robot[i]);
	}
}

int callJob(int cTime, int wID, int mNum, int mOpt) // O(N), N = 최대 200,000
{
	int sum = 0;
	while (mNum) {
		AI cur;
		if (mOpt == 0) {
			cur = up_pq.top(); up_pq.pop();
		}
		else {
			cur = down_pq.top(); down_pq.pop();
		}
		if (cur.time != robot[cur.id].time || robot[cur.id].status != 1) continue;
		robot[cur.id].intell += cTime - robot[cur.id].time;
		robot[cur.id].status = -wID;
		work[wID].push(cur.id);
		sum += cur.id;
		mNum--;
	}
	return sum;
}

void returnJob(int cTime, int wID) // O(NlogN), N = 최대 200,000 => 200,000 * 20 => 4,000,000
{
	queue<int> q(work[wID]);
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		if (robot[cur].status == -wID) {
			robot[cur].time = cTime;
			robot[cur].status = 1;
			up_pq.push(robot[cur]);
			down_pq.push(robot[cur]);
		}
	}
}

void broken(int cTime, int rID) // O(1)
{
	if (robot[rID].status != 1)
		robot[rID].status = 0;
}

void repair(int cTime, int rID) // O(1)
{
	if (robot[rID].status == 0) {
		robot[rID] = { rID, 0, cTime, 1 };
		up_pq.push(robot[rID]);
		down_pq.push(robot[rID]);
	}
}

int check(int cTime, int rID)  // O(1)
{
	if (robot[rID].status == 1) {
		return robot[rID].intell + cTime - robot[rID].time;
	}
	return robot[rID].status;
}
