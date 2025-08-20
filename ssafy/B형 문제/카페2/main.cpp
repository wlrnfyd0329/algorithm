#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT (100)
#define CMD_ORDER (200)
#define CMD_SUPPLY (300)
#define CMD_CANCEL (400)
#define CMD_GET_STATUS (500)
#define CMD_HURRY (600)

struct RESULT
{
    int cnt;
    int IDs[5];
};

extern void init(int N);
extern int order(int mID, int M, int mBeverages[]);
extern int supply(int mBeverage);
extern int cancel(int mID);
extern int getStatus(int mID);
extern RESULT hurry();

#define MAX_NUM_BEVERAGES (10)

static bool run()
{
    int Q, N, M;
    int mID, mBeverage;

    int mBeverages[MAX_NUM_BEVERAGES];

    int ret = -1, ans, cnt;

    RESULT res;

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d", &N);
            init(N);
            okay = true;
            break;
        case CMD_ORDER:
            scanf("%d %d", &mID, &M);
            for (int i = 0; i < M; ++i)
                scanf("%d", &mBeverages[i]);
            ret = order(mID, M, mBeverages);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SUPPLY:
            scanf("%d", &mBeverage);
            ret = supply(mBeverage);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_CANCEL:
            scanf("%d", &mID);
            ret = cancel(mID);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_GET_STATUS:
            scanf("%d", &mID);
            ret = getStatus(mID);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_HURRY:
            res = hurry();
            scanf("%d", &cnt);
            if (res.cnt != cnt)
                okay = false;
            for (int i = 0; i < cnt; ++i)
            {
                scanf("%d", &ans);
                if (res.IDs[i] != ans)
                    okay = false;
            }
            break;
        default:
            okay = false;
            break;
        }
    }

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    // freopen("sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}