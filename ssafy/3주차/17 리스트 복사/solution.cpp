
#include <unordered_map>

using namespace std;

int idx = 0;
short arr[10][200000];
unordered_map<string, void*> table; 
unordered_map<pair<string, int>, short> update; // 업데이트를 위한 테이블

void init()
{
    table.clear();
    update.clear();
}

void makeList(char mName[], int mLength, int mListValue[])
{
    string s(mName);
    table[s] = arr[idx];
    for(int i = 0; i < mLength; i++) {
        arr[idx][i] = mListValue[i];
    }
    idx++;
} 

void copyList(char mDest[], char mSrc[], bool mCopy)
{
}

void updateElement(char mName[], int mIndex, int mValue)
{
}

int element(char mName[], int mIndex)
{
    return 0;
}