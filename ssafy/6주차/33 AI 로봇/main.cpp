#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CALL_JOB (100)
#define RETURN_JOB (200)
#define BROKEN (300)
#define REPAIR (400)
#define CHECK (500)

extern void init(int N);
extern int callJob(int cTime, int wID, int mNum, int mOpt);
extern void returnJob(int cTime, int wID);
extern void broken(int cTime, int rID);
extern void repair(int cTime, int rID);
extern int check(int cTime, int rID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int N, Q, cmd;

static int run(int score)
{
    int wIDCnt = 1;
    int cTime, mNum, rID, wID, mOpt;
    int res, ans;

    scanf("%d", &N);
    init(N);

    scanf("%d", &Q);

    while (Q--)
    {
        scanf("%d", &cmd);

        switch (cmd)
        {
        case CALL_JOB:
            scanf("%d %d %d", &cTime, &mNum, &mOpt);
            res = callJob(cTime, wIDCnt, mNum, mOpt);
            scanf("%d", &ans);
            if (ans != res)
                score = 0;
            wIDCnt++;
            break;
        case RETURN_JOB:
            scanf("%d %d", &cTime, &wID);
            returnJob(cTime, wID);
            break;
        case BROKEN:
            scanf("%d %d", &cTime, &rID);
            broken(cTime, rID);
            break;
        case REPAIR:
            scanf("%d %d", &cTime, &rID);
            repair(cTime, rID);
            break;
        case CHECK:
            scanf("%d %d", &cTime, &rID);
            res = check(cTime, rID);
            scanf("%d", &ans);
            if (ans != res)
                score = 0;
            break;
        default:
            score = 0;
            break;
        }
    }

    return score;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, score;

    scanf("%d %d", &T, &score);

    for (int tc = 1; tc <= T; tc++)
        printf("#%d %d\n", tc, run(score));

    return 0;
}