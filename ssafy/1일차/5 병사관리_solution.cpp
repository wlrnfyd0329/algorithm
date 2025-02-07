#include <iostream>
#include <map>

using namespace std;

map<int, int> m[10];

void init()
{
    for(int i = 0; i < 10; i++) {
        m[i].clear();
    }
}

void hire(int mID, int mTeam, int mScore)
{
    m[mTeam][mID] = mScore;
}

void fire(int mID)
{
    for (int i = 0; i < 10; i++) {
        if (m[i].find(mID) != m[i].end()) {
            m[i].erase(mID);
        }
    }
}

void updateSoldier(int mID, int mScore)
{
    for (int i = 0; i < 10; i++) {
        if(m[i].find(mID) != m[i].end()) {
            m[i][mID] = mScore;
        }
    }
}

void updateTeam(int mTeam, int mChangeScore)
{
    for(auto iter = m[mTeam].begin(); iter != m[mTeam].end(); iter++) {
        if (iter->second + mChangeScore > 5) {
            iter->second = 5;
        }
        else if (iter->second + mChangeScore < 1) {
            iter->second = 1;
        }
        else {
            iter->second += mChangeScore;
        }
    }

}

int bestSoldier(int mTeam)
{
    int mID;
    int score = 0;
    for(auto iter = m[mTeam].begin(); iter != m[mTeam].end(); iter++) {
        if (score <= iter->second) {
            mID = iter->first;
        }
    }
    return mID;
}