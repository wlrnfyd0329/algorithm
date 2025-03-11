#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int mJoker, int mNumbers[5]);
extern void putCards(int mDir, int mNumbers[5]);
extern int findNumber(int mNum, int mNth, int ret[4]);
extern void changeJoker(int mValue);

#define CMD_INIT 100
#define CMD_PUT 200
#define CMD_FIND 300
#define CMD_CHANGE 400

#define MAX_CARD_NUM 5
#define MAX_RET_NUM 4

static bool run()
{
	int query_num;
	scanf("%d", &query_num);

	int ret, ans;
	int numbers[MAX_CARD_NUM];
	bool ok = false;

	for (int q = 0; q < query_num; q++)
	{
		int query;
		scanf("%d", &query);

		if (query == CMD_INIT)
		{
			int joker;
			scanf("%d", &joker);
			for (int i = 0; i < MAX_CARD_NUM; i++)
				scanf("%d", &numbers[i]);
			init(joker, numbers);
			ok = true;
		}
		else if (query == CMD_PUT)
		{
			int dir;
			scanf("%d", &dir);
			for (int i = 0; i < MAX_CARD_NUM; i++)
				scanf("%d", &numbers[i]);
			putCards(dir, numbers);
		}
		else if (query == CMD_FIND)
		{
			int num, Nth;
			int ret_numbers[MAX_RET_NUM];
			int ans_numbers[MAX_RET_NUM];
			scanf("%d %d %d", &num, &Nth, &ans);
			ret = findNumber(num, Nth, ret_numbers);
			if (ans != ret)
			{
				ok = false;
			}
			if (ans == 1)
			{
				for (int i = 0; i < MAX_RET_NUM; i++)
				{
					scanf("%d", &ans_numbers[i]);
					if (ans_numbers[i] != ret_numbers[i])
					{
						ok = false;
					}
				}
			}
		}
		else if (query == CMD_CHANGE)
		{
			int value;
			scanf("%d", &value);
			changeJoker(value);
		}
	}
	return ok;
}
int main()
{
	setbuf(stdout, NULL);
	// freopen("sample_input.txt", "r", stdin);
	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}