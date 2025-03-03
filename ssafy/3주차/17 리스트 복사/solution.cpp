#include <map>
#include <string>

using namespace std;

int init_cnt;
int init_arr[15][200005];

int address_cnt;
map<string, int> address;

int change_cnt;
pair<int, int> change[150000];

int prevChange[150000]; // 변화들의 직전 변화
int lastChange[5500];   // 해당 배열의 이전 변화

void init()
{
    init_cnt = 0;
    address_cnt = 0;
    address.clear();
    change_cnt = 0;
}

void makeList(char mName[], int mLength, int mListValue[])
{
    for (int i = 0; i < mLength; i++)
    {
        init_arr[init_cnt][i] = mListValue[i];
    }
    address[string(mName)] = address_cnt++;
    change[change_cnt] = {-1, init_cnt++};
    prevChange[change_cnt] = -1;
    lastChange[address[string(mName)]] = change_cnt++;
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
    if (mCopy)
    {
        address[string(mDest)] = address_cnt++;
        change[change_cnt] = {-1, -1}; // -1로 하지 않으면 인덱스를 조회할때, 수정되었다고 착각할 수 있기 때문에 -1로 초기화 해준다.
        prevChange[change_cnt] = lastChange[address[string(mSrc)]];
        lastChange[address[string(mDest)]] = change_cnt++;
    }
    else
    {
        address[string(mDest)] = address[string(mSrc)];
    }
}

void updateElement(char mName[], int mIndex, int mValue)
{
    change[change_cnt] = {mIndex, mValue};
    prevChange[change_cnt] = lastChange[address[string(mName)]];
    lastChange[address[string(mName)]] = change_cnt++;
}

int element(char mName[], int mIndex)
{
    int c = lastChange[address[string(mName)]];
    while (true)
    {
        if (prevChange[c] == -1)
        {
            return init_arr[change[c].second][mIndex];
        }
        if (change[c].first == mIndex)
        {
            return change[c].second;
        }
        c = prevChange[c];
    }
    return 0;
}