// 동시에 관리해야 되는 것을 포인터를 통해서 주소값을 다루는 것이 포인트였다.

#include <map>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct News
{
	int ID;
	int Time;
	int Channel;
	bool isExist = true;

	News() {}
	News(int id, int time, int channel) : ID(id), Time(time), Channel(channel) {}

	bool operator<(const News &other) const
	{
		if (Time == other.Time) return ID > other.ID;
		return Time > other.Time;
	}
}newsPool[30005]; // 생성된 뉴스 정보 담아줌

struct cmp {
	// time이 낮을수록, newId가 낮을수록 우선순위 큼
	bool operator()(const News *a, const News *b) {
		if (a->Time != b->Time) return !(a->Time < b->Time);
		return !(a->ID < b->ID);
	}
};

int n, k;

int user_idx = 0;
vector<News*> user[505]; // 유저가 받은 뉴스 저장
map<int, int> user_table;

int news_idx = 0;
map<int, int> news_table;

int channel_idx = 0;
vector<pair<int, int>> channel_user_info[505]; // {유저 index, 들어온 시간}
priority_queue<News*, vector<News*>, cmp> channel; // 채널에 온 뉴스 시간 순 저장
map<int, int> channel_table;

void init(int N, int K)
{
	n = N;
	k = K;

	user_idx = 0;
	for (int i = 0; i < 505; i++) {
		user[i].clear();
		channel_user_info[i].clear();
	}
	user_table.clear();

	news_idx = 0;
	news_table.clear();

	channel_idx = 0;
	while (!channel.empty()) {
		channel.pop();
	}
	channel_table.clear();
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	if (user_table.find(mUID) == user_table.end()) {
		user_table[mUID] = user_idx++;
	}

	for (int i = 0; i < mNum; i++) {
		if (channel_table.find(mChannelIDs[i]) == channel_table.end()) {
			channel_table[mChannelIDs[i]] = channel_idx++;
		}
		channel_user_info[channel_table[mChannelIDs[i]]].push_back({ user_table[mUID], mTime });
	}
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	news_table[mNewsID] = news_idx;
	News new_news(mNewsID, mTime + mDelay, channel_table[mChannelID]);
	newsPool[news_idx] = new_news;
	channel.emplace(&newsPool[news_idx]);
	news_idx++;
	return channel_user_info[channel_table[mChannelID]].size();
}

void cancelNews(int mTime, int mNewsID)
{
	newsPool[news_table[mNewsID]].isExist = false;
}

void sendNew(int mTime) {
	while (!channel.empty()) {
		if (channel.top()->Time > mTime) break;
		if (!channel.top()->isExist) {
			channel.pop();
			continue;
		}
		for (auto user_info : channel_user_info[channel.top()->Channel]) {
			if (user_info.second < channel.top()->Time) {
				user[user_info.first].push_back(channel.top());
			}
		}
		channel.pop();
	}
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	sendNew(mTime);
	int user_idx = user_table[mUID];
	int cnt = 0;
	int input_cnt = 0;
	for (int i = user[user_idx].size() - 1; i >= 0; i--) {
		if (user[user_idx][i]->isExist) {
			cnt++;
			if (input_cnt < 3) {
				mRetIDs[input_cnt++] = user[user_idx][i]->ID;
			}
		}
	}
	user[user_idx].clear();

	return cnt;
}