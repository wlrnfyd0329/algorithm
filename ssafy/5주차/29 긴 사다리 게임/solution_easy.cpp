// 1. 입력 받은 그대로 로그를 가지고 있는다.
// 2. 사다리 맵을 가지고 있자
// 3. 행마다 어떤 열에 있는지 
// 4. 각 열마다, 가로선이 있는 위치를 저장해주자 -> 내가 선택한 방법(쉬운 풀이)
// 5. 사람 마다 지나간 위치를 저장해두자 -> 수업에서 선택한 방법(어려운 풀이)

// 쉬운 풀이 :
// vector로 저장하면 추가는 쉬운데, 삭제는 조금 어렵다
// 로직에서 upper_bound가 사용되고 삭제가 쉬운 TreeSet을 사용한다.

// 어려운 풀이 :
// 4번이 지나가는 예시 : (4, 0) -> (4, 1) -> (5, 3) -> (6, 5) -> (5, 10억)
// 6번이 지나가는 예시 : (6, 0) -> (6, 3) -> (5, 5) -> (6, 10억)
// 근데 add(5, 2)하면
// 4번이 지나가는 예시 : (4, 0) -> (4, 1) -> (5, 2) -> (6, 3) -> (5, 5) -> (6, 10억)
// 6번이 지나가는 예시 : (6, 0) -> (6, 2) -> (5, 3) -> (6, 5) -> (5, 10억)
// 길이 생기면 6은 2를 기점으로 4가 가던 길을 가고 4는 6이 가는 길을 갈 것이다.
// 이제 해당 점을 지나는 사람을 찾고 싶으면 그 아래에서 처음으로 만나는 지나간 사람을 찾으면 된다.
// 그렇다면 LinkedList로 관리하면 된다.

#include <set>

using namespace std;

set<int> ladder[105];

void init()
{
    for (int i = 0; i < 105; i++)
    {
        ladder[i].clear();
    }
}

void add(int mX, int mY)
{
    ladder[mX].insert(mY);
}

void remove(int mX, int mY)
{
    ladder[mX].erase(ladder[mX].find(mY));
}

int numberOfCross(int mID)
{
    int lad = mID;
    int position = 0;
    int cnt = 0;
    // 문제 조건에서 한번에 지나는 다리가 5,000라고 했고 호출 횟수가 500이라 아래처럼 시뮬레이션이 가능하다.
    // 하지만 5,000개의 조건이 없었다면 불가능했다.
    while (1)
    {
        if (lad == 1)
        {
            auto ladder1 = ladder[lad].upper_bound(position);
            if (ladder1 == ladder[lad].end())
                break;
            position = *ladder1;
            lad += 1;
        }
        else
        {
            auto ladder1 = ladder[lad].upper_bound(position);
            auto ladder2 = ladder[lad - 1].upper_bound(position);

            if (ladder1 == ladder[lad].end() && ladder2 == ladder[lad - 1].end())
                break;
            else if (ladder1 != ladder[lad].end() && ladder2 != ladder[lad - 1].end())
            {
                if (*ladder1 < *ladder2)
                {
                    position = *ladder1;
                    lad += 1;
                }
                else
                {
                    position = *ladder2;
                    lad -= 1;
                }
            }
            else if (ladder2 != ladder[lad - 1].end())
            {
                position = *ladder2;
                lad -= 1;
            }
            else
            {
                position = *ladder1;
                lad += 1;
            }
        }
        cnt++;
    }

    return cnt;
}

int participant(int mX, int mY)
{
    int lad = mX;
    int position = mY;
    while (1)
    {
        if (lad == 1)
        {
            auto ladder1 = ladder[lad].lower_bound(position);
            if (ladder1 == ladder[lad].begin())
                break;
            --ladder1;
            position = *ladder1;
            lad += 1;
        }
        else
        {
            auto ladder1 = ladder[lad].lower_bound(position);
            auto ladder2 = ladder[lad - 1].lower_bound(position);

            if (ladder1 == ladder[lad].begin() && ladder2 == ladder[lad - 1].begin())
                break;
            else if (ladder1 != ladder[lad].begin() && ladder2 != ladder[lad - 1].begin())
            {
                --ladder1;
                --ladder2;
                if (*ladder1 > *ladder2)
                {
                    position = *ladder1;
                    lad += 1;
                }
                else
                {
                    position = *ladder2;
                    lad -= 1;
                }
            }
            else if (ladder2 != ladder[lad - 1].begin())
            {
                --ladder2;
                position = *ladder2;
                lad -= 1;
            }
            else
            {
                --ladder1;
                position = *ladder1;
                lad += 1;
            }
        }
    }
    return lad;
}