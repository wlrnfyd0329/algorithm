#include <map>
#include <queue>
#include <vector>

using namespace std;

struct News
{
    int id;
    int time;
    bool isExist = true;

    News(int id, int time) : id(id), time(time) {}

    bool operator<(const News &other) const
    {
        if (time == other.time)
            return id < other.id;
        return time < other.time;
    }
};

int user_idx = 0;
priority_queue<News> user[505];
map<int, int> user_table;

int news_idx = 0;
vector<News> news;
map<int, int> news_table;

int channel_idx = 0;
queue<News> channel[505];
map<int, int> channel_table;

void init(int N, int K)
{
    user_idx = 0;
    user_table.clear();

    news_idx = 0;
    news.clear();
    news_table.clear();

    channel_idx;
    channel_table.clear();
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
    return -1;
}

void cancelNews(int mTime, int mNewsID)
{
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
    return -1;
}