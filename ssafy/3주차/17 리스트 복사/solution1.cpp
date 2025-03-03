#include <map>
#include <string>
#include <iostream>

using namespace std;

int arr_cnt;
int init_arr[15][200005];

int address_cnt;
map<string, int> address;

int change_cnt;
pair<pair<int, int>, int> change[150000];
// <생성 리스트, 복사된 리스트>, -1 : 원본 리스트 생성
// <생성 리스트, 복사된 리스트>, -2 : 복사 리스트 생성
// <변경될 리스트, 인덱스>, 값 : 값 변경

void init()
{
    arr_cnt = 0;
    address_cnt = 0;
    change_cnt = 0;
    address.clear();
}

void makeList(char mName[], int mLength, int mListValue[])
{
    address[string(mName)] = address_cnt;
    for (int i = 0; i < mLength; i++)
    {
        init_arr[arr_cnt][i] = mListValue[i];
    }
    change[change_cnt++] = {{address_cnt++, arr_cnt++}, -1};
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
    if (mCopy)
    {
        address[string(mDest)] = address_cnt;
        change[change_cnt++] = {{address_cnt++, address[string(mSrc)]}, -2};
    }
    else
    {
        address[string(mDest)] = address[string(mSrc)];
    }
}

void updateElement(char mName[], int mIndex, int mValue)
{
    change[change_cnt++] = {{address[string(mName)], mIndex}, mValue};
}

int element(char mName[], int mIndex)
{
    int arr_num = address[string(mName)];
    for (int i = change_cnt - 1; i >= 0; i--)
    {
        if (change[i].first.first == arr_num)
        {
            if (change[i].second == -2)
            {
                arr_num = change[i].first.second;
            }
            else if (change[i].second == -1)
            {
                arr_num = change[i].first.second;
                break;
            }
            else
            {
                if (change[i].first.second == mIndex)
                {
                    return change[i].second;
                }
            }
        }
    }
    return init_arr[arr_num][mIndex];
}