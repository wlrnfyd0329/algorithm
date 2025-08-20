// 버킷 알고리즘
// 택시의 초기 위치, 손님의 출발지와 목적지는 임의적으로 생성되어 주어진다.
// 위의 문장이 힌트다. 균일하게 분포된다는 소리다.

#include <set>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_TAXI 2005

struct Result
{
    int mX, mY;
    int mMoveDistance;
    int mRideDistance;
};

vector<int> bucket[10][10];
int len = 0;
set<pair<int, int>> s;
Result taxi[MAX_TAXI];

inline int distance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

void init(int N, int M, int L, int mXs[], int mYs[])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            bucket[i][j].clear();
        }
    }
    len = L;
    s.clear();
    for (int i = 1; i <= M; i++)
    {
        taxi[i].mMoveDistance = 0;
        taxi[i].mRideDistance = 0;
        taxi[i].mX = mXs[i - 1];
        taxi[i].mY = mYs[i - 1];
        bucket[mXs[i - 1] / L][mYs[i - 1] / L].push_back(i);
        s.insert({0, i});
    }
    return;
}

// 30,000
// 버킷 알고리즘을 사용했을 때, 탐색해야 하는 범위를 잘 생각해야 한다. 3 * 3 범위를 탐색해야 함.
// 최대의 거리로 돌아다니는 것을 생각하면 된다.
int pickup(int mSX, int mSY, int mEX, int mEY)
{
    int dx = mSX / len;
    int dy = mSY / len;
    int taxi_id = -1;
    int buc_x = -1;
    int buc_y = -1;
    int idx = -1;
    int min_dist = 10000;
    for (int i = max(0, dx - 1); i <= min(9, dx + 1); i++)
    {
        for (int j = max(0, dy - 1); j <= min(9, dy + 1); j++)
        {
            for (int k = 0; k < bucket[i][j].size(); k++)
            {
                int id = bucket[i][j][k];
                int dist = distance(mSX, mSY, taxi[id].mX, taxi[id].mY);
                if (dist > len)
                    continue;
                if (min_dist > dist)
                {
                    min_dist = dist;
                    taxi_id = id;
                    idx = k;
                    buc_x = i;
                    buc_y = j;
                }
                else if (min_dist == dist)
                {
                    if (taxi_id > id)
                    {
                        taxi_id = id;
                        idx = k;
                        buc_x = i;
                        buc_y = j;
                    }
                }
            }
        }
    }
    if (taxi_id != -1)
    {
        bucket[buc_x][buc_y].erase(bucket[buc_x][buc_y].begin() + idx);
        bucket[mEX / len][mEY / len].push_back(taxi_id);
        s.erase({-taxi[taxi_id].mRideDistance, taxi_id});
        taxi[taxi_id].mRideDistance += distance(mSX, mSY, mEX, mEY);
        taxi[taxi_id].mMoveDistance += min_dist + distance(mSX, mSY, mEX, mEY);
        taxi[taxi_id].mX = mEX;
        taxi[taxi_id].mY = mEY;
        s.insert({-taxi[taxi_id].mRideDistance, taxi_id});
    }
    return taxi_id;
}

// 5,000
Result reset(int mNo)
{
    Result res = taxi[mNo];
    s.erase({-taxi[mNo].mRideDistance, mNo});
    taxi[mNo].mMoveDistance = 0;
    taxi[mNo].mRideDistance = 0;
    s.insert({0, mNo});

    return res;
}

// 10,000
void getBest(int mNos[])
{
    int idx = 0;
    for (auto k : s)
    {
        if (idx >= 5)
            break;
        mNos[idx++] = k.second;
    }
    return;
}