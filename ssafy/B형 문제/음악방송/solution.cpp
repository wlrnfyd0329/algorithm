// 직원들의 출퇴근 시각은 임의로 지정됨을 보장함
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
vector<int> lazy;

void lazy_update(int node, int start, int end)
{
    if (lazy[node] != 0)
    {
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

int query(int node, int start, int end, int index)
{
    lazy_update(node, start, end);
    if (index < start || end < index)
        return 0;
    if (start == end)
        return tree[node];
    int mid = (start + end) >> 1;
    return query(node * 2, start, mid, index) + query(node * 2 + 1, mid + 1, end, index);
}

void update(int node, int start, int end, int left, int right, int value)
{
    lazy_update(node, start, end);
    if (right < start || end < left)
        return;
    if (left <= start && end <= right)
    {
        lazy[node] += value;
        lazy_update(node, start, end);
        return;
    }
    int mid = (start + end) >> 1;
    update(node * 2, start, mid, left, right, value);
    update(node * 2 + 1, mid + 1, end, left, right, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
    return;
}

void init(int musicTime)
{
    mid_to_idx.clear();
    employee_idx = 1;
    len = musicTime;
    int h = ceil(log2(MAX_TIME));
    tree = vector<int>(1 << (h + 1));
    lazy = vector<int>(1 << (h + 1));
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