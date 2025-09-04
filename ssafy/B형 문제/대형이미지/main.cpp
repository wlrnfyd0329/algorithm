#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N);
extern void addPrint(int mID, int mSize, int mCnt, int mPixel[][3]);
extern void pressPrint(int mID, int mRow, int mCol, int mDir);
extern int getDepth(int mRow, int mCol);

#define CMD_INIT	100
#define CMD_ADD		200
#define CMD_PRESS	300
#define CMD_GET		400

static int pixel[10000][3];
static bool run()
{
	int Q, N;
	int id, size, cnt, row, col, dir;
	int ret, ans;

	bool ok = false;

	scanf("%d", &Q);
	for (int q = 0; q < Q; q++)
	{
		int cmd;
		scanf("%d", &cmd);
		if (cmd == CMD_INIT)
		{
			scanf("%d", &N);
			init(N);
			ok = true;
		}
		else if (cmd == CMD_ADD)
		{
			scanf("%d %d %d", &id, &size, &cnt);
			for (int i = 0; i < cnt; i++) {
				scanf("%d %d %d", &pixel[i][0], &pixel[i][1], &pixel[i][2]);
			}
			addPrint(id, size, cnt, pixel);
		}
		else if (cmd == CMD_PRESS)
		{
			scanf("%d %d %d %d", &id, &row, &col, &dir);
			pressPrint(id, row, col, dir);
		}
		else if (cmd == CMD_GET)
		{
			scanf("%d %d", &row, &col);
			ret = getDepth(row, col);
			scanf("%d", &ans);
			if (ans != ret) {
				ok = false;
			}
		}
		else ok = false;
	}
	return ok;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}