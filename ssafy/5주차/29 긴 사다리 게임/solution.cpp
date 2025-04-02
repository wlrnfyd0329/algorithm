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