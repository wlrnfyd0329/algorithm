// 처음엔 반복적으로 누적합을 수정해야 해서 세그먼트 트리를 떠올렸지만
// 트리를 세그먼트 트리로 접근하려면 ETT 로 변환해서 DFS가 선행되야 한다.
// 하지만 노드의 추가와 삭제가 매우 많기에 그때마다 DFS를 하여 세그먼트 트리를
// 업데이트 하는 것은 비효율적이라는 판단이 들었기에 그냥 트리 순회를 하며
// 인구수를 최대한 업데이트 하는 것으로 생각하였다.
// 해설에도 최악의 경우는 한개의 트리에 계속 값이 추가되는 것인데
// 이는 1~17000까지 더하는 것이고 대략 1.4억이 나오기에 시간초과가 날 것이 자명하기에
// 최악의 경우가 나오지 않도록 기도하라고 써있었다...ㅋㅋ
// 마지막 distribute는 이분탐색을 떠올렸다. 파라메틱스 서치

#include <unordered_map>

using namespace std;

int cnt, n;
int p[20000];
int population[20000];
int child_cnt[20000];
bool isDelete[20000];
unordered_map<int, int> table;

void init(int N, int mId[], int mNum[]) {
	table.clear();
	n = N;
	cnt = N + 1;
	for (int i = 1; i <= N; i++) {
		table[mId[i - 1]] = i;
		p[i] = i;
		child_cnt[i] = 0;
		population[i] = mNum[i - 1];
		isDelete[i] = false;
	}
	return;
}

int add(int mId, int mNum, int mParent) {
	if (child_cnt[table[mParent]] >= 3) return -1;
	int parent = table[mParent];
	table[mId] = cnt;
	p[cnt] = parent;
	child_cnt[cnt] = 0;
	child_cnt[parent]++;
	population[cnt] = mNum;
	while (parent != p[parent]) {
		population[parent] += mNum;
		parent = p[parent];
	}
	population[parent] += mNum;
	isDelete[cnt++] = false;
	return population[table[mParent]];
}

int remove(int mId) {
	int index = table[mId];
	while (index != p[index]) {
		if (isDelete[index]) return -1;
		index = p[index];
	}

	index = table[mId];
	int people = population[table[mId]];
	isDelete[index] = true;
	child_cnt[p[index]]--;

	while (index != p[index]) {
		population[index] -= people;
		index = p[index];
	}
	population[index] -= people;
	return people;
}

int distribute(int K) {
	int sum = 0, max_value = 0;
	for (int i = 1; i <= n; i++) {
		sum += population[i];
		if (max_value < population[i]) {
			max_value = population[i];
		}
	}
	if (sum <= K) return max_value;
	int lf = 0, rg = K;
	while (lf <= rg) {
		int mid = (lf + rg) >> 1;
		sum = 0;
		for (int i = 1; i <= n; i++) {
			if (population[i] <= mid) sum += population[i];
			else sum += mid;
		}
		if (sum <= K) {
			lf = mid + 1;
		}
		else {
			rg = mid - 1;
		}
	}
	return rg;
}