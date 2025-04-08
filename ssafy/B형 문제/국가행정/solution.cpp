// 세그먼트 트리와 우선순위 큐
// 파라매트릭 서치를 활용하는 문제였다.
// 선거구를 정할 때, 인원수를 기준으로 선거구를 자르는 것이 포인트였다.

#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int n;
int population[10'005];
int bridge[10'005];
vector<int> tree;
struct cmp {
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
		if (a.first == b.first) return a.second > b.second;
		return a.first < b.first;
	}
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

int initialize(int node, int start, int end) {
	if (start == end) {
		tree[node] = (population[start] + population[start + 1]) / bridge[start];
		pq.push({ tree[node], start });
		return tree[node];
	}
	int mid = (start + end) >> 1;
	return tree[node] = initialize(node * 2, start, mid) + initialize(node * 2 + 1, mid + 1, end);
}

void update(int node, int start, int end, int idx) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = (population[start] + population[start + 1]) / bridge[start];
		pq.push({ tree[node], start });
		return;
	}
	int mid = (start + end) >> 1;
	update(node * 2, start, mid, idx);
	update(node * 2 + 1, mid + 1, end, idx);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) >> 1;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

void init(int N, int mPopulation[])
{
	n = N;
	memcpy(population, mPopulation, sizeof(int) * n);
	fill(bridge, bridge + n, 1);
	int h = ceil(log2(n));
	pq = priority_queue<pair<int, int>, vector<pair<int, int>>, cmp>();
	tree = vector<int>(1<<(h + 1));
	initialize(1, 0, n - 2);
	return;
}

int expand(int M)
{
	pair<int, int> cur;
	while (M--) {
		cur = pq.top(); pq.pop();
		bridge[cur.second]++;
		update(1, 0, n - 2, cur.second);
	}
	return (population[cur.second] + population[cur.second + 1]) / bridge[cur.second];
}

int calculate(int mFrom, int mTo)
{
	if (mFrom < mTo) return query(1, 0, n - 2, mFrom, mTo - 1);
	else return query(1, 0, n - 2, mTo, mFrom - 1);
}

int divide(int mFrom, int mTo, int K)
{
	int lf = 0, rg = 10'000'000;
	while (lf <= rg) {
		int mid = (lf + rg) >> 1;
		int p = 0;
		for (int i = mFrom; i <= mTo; i++) {
			p++;
			int sum = population[i];
			for (int j = i + 1; j <= mTo; j++) {
				if (sum + population[j] <= mid) {
					sum += population[j];
					i++;
				}
				else break;
			}
		}
		if (p <= K) {
			rg = mid - 1;
		}
		else {
			lf = mid + 1;
		}
	}
	return lf;
}