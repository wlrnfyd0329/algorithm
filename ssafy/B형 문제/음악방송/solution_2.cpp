// 직원들의 출퇴근 시각은 임의로 지정됨을 보장함
// lazy와 비슷하지만, 자손끝까지 내려보내지 않고, query할때, 모두 더하면서 진행한다.
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

#define MAX_EMP 15005
#define MAX_TIME 2000005

unordered_map<int, int> mid_to_idx;
int employee_idx;
struct Employee
{
    int st, en, isDelete;
} employee[MAX_EMP];
int len;
vector<int> tree;

int query(int node, int s, int e, int idx, int acc = 0)
{
    acc += tree[node];
    if (s == e)
        return acc;
    int m = (s + e) >> 1;
    if (idx <= m)
        return query(node << 1, s, m, idx, acc);
    else
        return query(node << 1 | 1, m + 1, e, idx, acc);
}

void update(int node, int s, int e, int l, int r, int v)
{
    if (r < s || e < l)
        return;
    if (l <= s && e <= r)
    {
        tree[node] += v;
        return;
    }
    int m = (s + e) >> 1;
    update(node << 1, s, m, l, r, v);
    update(node << 1 | 1, m + 1, e, l, r, v);
}

void init(int musicTime)
{
    mid_to_idx.clear();
    employee_idx = 1;
    len = musicTime;
    int h = ceil(log2(MAX_TIME));
    tree = vector<int>(1 << (h + 1));
}

// 5,000
void add(int mID, int mStart, int mEnd)
{
    int idx = mid_to_idx[mID];
    if (!idx)
    {
        mid_to_idx[mID] = employee_idx;
        employee[employee_idx] = {mStart, mEnd - len, 0};
        update(1, 1, MAX_TIME, mStart, mEnd - len, 1);
        employee_idx++;
    }
    else
    {
        if (!employee[idx].isDelete)
        {
            update(1, 1, MAX_TIME, employee[idx].st, employee[idx].en, -1);
        }
        employee[idx] = {mStart, mEnd - len, 0};
        update(1, 1, MAX_TIME, mStart, mEnd - len, 1);
    }
}

// 500
void remove(int mID)
{
    int idx = mid_to_idx[mID];
    if (employee[idx].isDelete)
        return;
    employee[idx].isDelete = 1;
    update(1, 1, MAX_TIME, employee[idx].st, employee[idx].en, -1);
}

// 30,000
int getCnt(int mBSTime)
{
    return query(1, 1, MAX_TIME, mBSTime);
}