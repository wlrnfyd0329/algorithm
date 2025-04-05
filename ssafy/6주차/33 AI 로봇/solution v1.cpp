// 함수의 총 호출 횟수가 정해진 경우에는 각 함수가 모든 호출 횟수를 사용할 경우도 고려해야 한다.

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct AI {
	int id;
	int intell = 0; // 지능
	// 나는 시간을 기록하면서 불릴 때, 시간의 차이로 지능을 업데이트를 해주는데
	// 그냥 작업이 시작될 때, 작업이 시작된 시간을 기록하고 return할 때, 그 시간 차 만큼 iq에 빼주면 된다.
	// 내가 작업을 다녀온 동안 손해 본 시간을 생각해보는 것이다.
	// 수리하고 돌아왔을 때, 지능은 신경 써줘야 한다. -현재 시간을 넣어주면 된다.
	int time = 0;   // training 시작 시간
	int status = 1; // broken : 0, working : -wId, training : 1
};
vector<AI> robot;
// map을 사용할 필요가 없다. index 자체가 값이 불규칙하거나, 값이 매우 큰 것이 아니기 때문이다.
// 즉 1. 문자열 인덱스, 2. 정상적이지 않은 범위의 정수 인덱스(희소한 경우)에 사용한다.
// 지금은 그냥 arraylist, vector를 만들어서 추가하면 된다.
unordered_map<int, queue<int>> work;

// 1. pq를 두개 만드는데, 아래와 같이 정렬 순서를 바꿔준다.
// 2. pq를 두 개 만드는데, 넣을 때 높은 지능을 가진 친구를 넣을 때, 음수를 취해서 넣어주면 된다.
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
		// 1. 아래의 방법처럼 지능과 상태를 확인해서 lazy하게 처리해주기
		// 2. 삭제한 애들은 lazy queue를 사용한다. 즉 heap을 4개를 사용한다. 
		// (그러면 원래 pq에서 뽑을 때, lazy heap에 있는 값과 비교하면 된다.)
		// 원래 queue : 10, 7, 5, 5, 3 / lazy queue : 5, 3 이라고 하면 10, 7은 사용하고 5가 나오면 사용안하고 lazy queue에서도 뽑는다.
		// 3. 한쪽에서 뽑으면 다른쪽에서도 그걸 뽑자(pq가 아니라 set이면 가능하다 || heap을 직접 구현해서 사용한다)
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
