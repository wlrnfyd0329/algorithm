#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_NUMBER_OF_CROSS 4
#define CMD_PARTICIPANT 5

extern void init();
extern void add(int mX, int mY);
extern void remove(int mX, int mY);
extern int numberOfCross(int mID);
extern int participant(int mX, int mY);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mX, mY, mID;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_ADD:
            scanf("%d %d", &mX, &mY);
            add(mX, mY);
            break;
        case CMD_REMOVE:
            scanf("%d %d", &mX, &mY);
            remove(mX, mY);
            break;
        case CMD_NUMBER_OF_CROSS:
            scanf("%d", &mID);
            userAns = numberOfCross(mID);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_PARTICIPANT:
            scanf("%d %d", &mX, &mY);
            userAns = participant(mX, mY);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }
    return isCorrect;
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