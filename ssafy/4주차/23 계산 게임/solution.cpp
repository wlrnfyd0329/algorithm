// 조커의 크기와 숫자가 mod 20이라는 것을 이용해 DP 적 사고가 필요한 문제인 듯하다.
// 해당 인덱스의 수 조합은 조커에 의해 바뀌는데 그것을 미리 계산하여 조커 수에 따른 값에 인덱스를 넣는 방식이다.
// 처음에는 map을 이용하여 조커의 수와 조커를 제외한 수를 미리 계산하여 해당 map에 저장하였고
// find시 해당 map 6개를 불러 개수를 세어가며 답을 도출하려 했음. 하지만 이는 최악의 경우 한번 연산시 6000번 계산하게 되고
// 최악의 경우 만번 호출한다 했을 때, tc 하나당 6000만번 연산을 하고 25개의 tc를 볼때, 시간초과가 나는 것은 당연하다.
// 따라서 find시 상수연산으로 해당 인덱스를 구해야 하는데 DP적 사고로 미리 값을 구해놓는 것이 바람직하다.

#include <deque>
#include <algorithm>

using namespace std;

deque<int> dq;
deque<int> table[20][20];
int forder = 0;
pair<int, int> fvalue;
int border = 0;
pair<int, int> bvalue;
int joker = 0;

void init(int mJoker, int mNumbers[5])
{
	dq.clear();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			table[i][j].clear();
		}
	}
	forder = 0;
	border = 0;
	joker = mJoker % 20;
	int value = 0;
	int joker_cnt = 0;
	for (int i = 0; i < 5; i++)
	{
		dq.push_back(mNumbers[i]);
		if (mNumbers[i] == -1)
		{
			joker_cnt++;
		}
		else
		{
			value += mNumbers[i];
		}
	}

	if (dq.back() == -1)
	{
		fvalue = {joker_cnt - 1, value};
	}
	else
	{
		fvalue = {joker_cnt, value - dq.back()};
	}
	for (int i = 0; i < 20; i++)
	{
		int num = (fvalue.second + (i * fvalue.first)) % 20;
		table[i][num].push_back(border);
	}
	border++;

	if (dq.front() == -1)
	{
		bvalue = {joker_cnt - 1, value};
	}
	else
	{
		bvalue = {joker_cnt, value - dq.front()};
	}
	for (int i = 0; i < 20; i++)
	{
		int num = (bvalue.second + (i * bvalue.first)) % 20;
		table[i][num].push_back(border);
	}
	border++;
}

void putCards(int mDir, int mNumbers[5])
{
	if (mDir == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			dq.push_back(mNumbers[i]);
			if (dq[dq.size() - 5] == -1)
			{
				bvalue.first--;
			}
			else
			{
				bvalue.second -= dq[dq.size() - 5];
			}
			if (dq.back() == -1)
			{
				bvalue.first++;
			}
			else
			{
				bvalue.second += dq.back();
			}
			for (int i = 0; i < 20; i++)
			{
				int num = (bvalue.second + (i * bvalue.first)) % 20;
				table[i][num].push_back(border);
			}
			border++;
		}
	}
	else
	{
		for (int i = 4; i >= 0; i--)
		{
			dq.push_front(mNumbers[i]);
			if (dq[4] == -1)
			{
				fvalue.first--;
			}
			else
			{
				fvalue.second -= dq[4];
			}
			if (dq.front() == -1)
			{
				fvalue.first++;
			}
			else
			{
				fvalue.second += dq.front();
			}
			forder--;
			for (int i = 0; i < 20; i++)
			{
				int num = (fvalue.second + (i * fvalue.first)) % 20;
				table[i][num].push_front(forder);
			}
		}
	}
}

int findNumber(int mNum, int mNth, int ret[4])
{
	if (table[joker][mNum].size() < mNth)
		return 0;

	for (int i = 0; i < 4; i++)
	{
		ret[i] = dq[table[joker][mNum][mNth - 1] - forder + i];
	}
	return 1;
}

void changeJoker(int mValue)
{
	joker = mValue % 20;
}