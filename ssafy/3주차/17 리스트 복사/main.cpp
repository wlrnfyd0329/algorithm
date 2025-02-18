#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_MAKE_LIST 200
#define CMD_COPY_LIST 300
#define CMD_UNDATE_ELEMENT 400
#define CMD_ELEMENT 500

extern void init();
extern void makeList(char mName[], int mLength, int mListValue[]);
extern void copyList(char mDest[], char mSrc[], bool mCopy);
extern void updateElement(char mName[], int mIndex, int mValue);
extern int element(char mName[], int mIndex);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static unsigned int mSeed;
static unsigned int pseudo_rand(void)
{
    mSeed = mSeed * 214013 + 2531011;
    return (mSeed >> 16) & 0x7FFF;
}

static char mName[21];
static char mDest[21];
static char mSrc[21];
static int mListValue[200000];

static void generateName(char *name, int seed)
{
    mSeed = seed;
    int name_len = pseudo_rand() % 20 + 1;
    for (int i = 0; i < name_len; ++i)
    {
        name[i] = pseudo_rand() % 26 + 'a';
    }
    name[name_len] = '\0';
}

static int generateList(int *listValue, int seed)
{
    mSeed = seed;
    int length = pseudo_rand() << 15;
    length = (length + pseudo_rand()) % 200000 + 1;
    for (int i = 0; i < length; ++i)
    {
        listValue[i] = pseudo_rand();
    }
    return length;
}

static bool run()
{
    int numQuery;

    int seed;
    int mIndex, mValue, mCopy, mLength;
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
        case CMD_MAKE_LIST:
            scanf("%d", &seed);
            generateName(mName, seed);
            scanf("%d", &seed);
            mLength = generateList(mListValue, seed);
            makeList(mName, mLength, mListValue);
            break;
        case CMD_COPY_LIST:
            scanf("%d", &seed);
            generateName(mDest, seed);
            scanf("%d", &seed);
            generateName(mSrc, seed);
            scanf("%d", &mCopy);
            copyList(mDest, mSrc, (mCopy != 0));
            break;
        case CMD_UNDATE_ELEMENT:
            scanf("%d", &seed);
            generateName(mName, seed);
            scanf("%d %d", &mIndex, &mValue);
            updateElement(mName, mIndex, mValue);
            break;
        case CMD_ELEMENT:
            scanf("%d", &seed);
            generateName(mName, seed);
            scanf("%d", &mIndex);
            userAns = element(mName, mIndex);
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