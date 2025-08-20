#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT (100)
#define CMD_PICKUP (200)
#define CMD_RESET (300)
#define CMD_GET_BEST (400)

#define MAX_M (2000)

struct Result
{
    int mX, mY;
    int mMoveDistance;
    int mRideDistance;
};

extern void init(int N, int M, int L, int mXs[], int mYs[]);
extern int pickup(int mSX, int mSY, int mEX, int mEY);
extern Result reset(int mNo);
extern void getBest(int mNos[]);

static long long mSeed;
static int pseudo_rand()
{
    mSeed = (mSeed * 1103515245LL + 12345) % 2147483647;
    return (int)(mSeed >> 16);
}

static int mXs[MAX_M];
static int mYs[MAX_M];

static bool run()
{
    int Q, S;
    int N, M, L, mNo;
    int mSX, mSY, mEX, mEY;
    int ret = -1, ans;

    Result res;
    int x, y, mdist, rdist;

    int mNos[5];

    scanf("%d %d", &Q, &S);

    mSeed = (long long)S;

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d %d", &N, &M);
            L = N / 10;
            for (int i = 0; i < M; ++i)
            {
                mXs[i] = pseudo_rand() % N;
                mYs[i] = pseudo_rand() % N;
            }
            init(N, M, L, mXs, mYs);
            okay = true;
            break;
        case CMD_PICKUP:
            do
            {
                mSX = pseudo_rand() % N;
                mSY = pseudo_rand() % N;
                mEX = pseudo_rand() % N;
                mEY = pseudo_rand() % N;
            } while (mSX == mEX && mSY == mEY);
            ret = pickup(mSX, mSY, mEX, mEY);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_RESET:
            scanf("%d", &mNo);
            res = reset(mNo);
            scanf("%d %d %d %d", &x, &y, &mdist, &rdist);
            if (res.mX != x || res.mY != y || res.mMoveDistance != mdist || res.mRideDistance != rdist)
                okay = false;
            break;
        case CMD_GET_BEST:
            getBest(mNos);
            for (int i = 0; i < 5; ++i)
            {
                scanf("%d", &ans);
                if (mNos[i] != ans)
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