#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int musicTime);
extern void add(int mID, int mStart, int mEnd);
extern void remove(int mID);
extern int getCnt(int mBSTime);

#define CMD_INIT 0
#define CMD_ADD 1
#define CMD_REMOVE 2
#define CMD_GETCNT 3

static bool run()
{
    int Q, id, stime, etime;
    int ret, ans;

    bool ok = false;

    scanf("%d", &Q);
    for (int q = 0; q < Q; q++)
    {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == CMD_INIT)
        {
            scanf("%d", &stime);
            init(stime);
            ok = true;
        }
        else if (cmd == CMD_ADD)
        {
            scanf("%d %d %d", &id, &stime, &etime);
            add(id, stime, etime);
        }
        else if (cmd == CMD_REMOVE)
        {
            scanf("%d", &id);
            remove(id);
        }
        else if (cmd == CMD_GETCNT)
        {
            scanf("%d", &stime);
            ret = getCnt(stime);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else
            ok = false;
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