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
	bool operator() (const pair<int, int> &a, const pair<int, int> &b) const {
		if (a.first == b.first) return a.second > b.second;
		return a.first < b.first;
	}
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

int init(int node, int start, int end) {
	if (start == end) {
		tree[node] = (population[start] + population[start + 1]) / bridge[start];
		pq.push({ tree[node], start });
		return tree[node];
	}
	int mid = (start + end) >> 1;
	return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
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
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) >> 1;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

void init(int N, int mPopulation[])
{
	memcpy(population, mPopulation, sizeof(mPopulation));
	n = N;
	fill(bridge, bridge + n, 1);
	int h = ceil(log2(n));
	tree = vector<int>(n + 1);
	init(1, 0, n - 2);
	return;
}

int expand(int M)
{

	return 0;
}

int calculate(int mFrom, int mTo)
{
	return 0;
}

int divide(int mFrom, int mTo, int K)
{
	return 0;
}