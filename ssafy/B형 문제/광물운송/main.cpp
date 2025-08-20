#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int L, int N);
extern int addBaseCamp(int mID, int mRow, int mCol, int mQuantity);
extern int findBaseCampForDropping(int K);

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_DROP 3

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int L, N;
            scanf("%d %d", &L, &N);
            init(L, N);
            ok = true;
        }
        else if (query == CMD_ADD)
        {
            int mID, mRow, mCol, mQuantity;
            scanf("%d %d %d %d", &mID, &mRow, &mCol, &mQuantity);

            int ret = addBaseCamp(mID, mRow, mCol, mQuantity);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_DROP)
        {
            int K;
            scanf("%d", &K);
            int ret = findBaseCampForDropping(K);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
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