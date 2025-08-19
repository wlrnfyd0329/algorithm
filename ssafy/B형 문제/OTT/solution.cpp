// 시청한 영화 개수 1,000
// 사용자 고유번호 1~N
// 영화는 ID(고유함), 장르(1~5), 총점
// 사용자는 시청 목록을 가지고 있음. 이미 시청한 영화 다시 안봄
// 영화 삭제, 삭제하면 그 영화는 시청, 추천X, 사용자 시청 목록 삭제
// 추천은 이미 시청, 삭제 영화는 제외
// 가장 최근 시청한 최대 5개의 영화에서 사용자가 준 평점이 가장 높은 영화 같은 장르
// 가장 높은 평점을 준 영화가 여러 개면 가장 최근
// 시청 목록이 비어 있으면 모든 영화 추천
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

struct Movie
{
    int id;
    int idx;
    int total;
    int genre;

    bool operator<(const Movie &other) const
    {
        if (total == other.total)
            return idx > other.idx;
        return total > other.total;
    }
};
int movie_cnt = 0;
unordered_map<int, int> movie_table;
unordered_map<int, bool> movie_delete_table;
Movie movie[10005];
set<Movie> genre[6];

struct Watch
{
    int mID;
    int score;
};

struct Person
{
    vector<Watch> watch_movie;
    unordered_map<int, bool> watch_movie_table;
} person[1005];

struct RESULT
{
    int cnt;
    int IDs[5];
};

void init(int N)
{
    movie_cnt = 0;
    movie_table.clear();
    movie_delete_table.clear();
    for (int i = 0; i < 6; i++)
    {
        genre[i].clear();
    }
    for (int i = 1; i <= N; i++)
    {
        person[i].watch_movie.clear();
        person[i].watch_movie_table.clear();
    }
    return;
}

// 10,000
int add(int mID, int mGenre, int mTotal)
{
    auto res = movie_table.insert({mID, movie_cnt});
    if (res.second)
    {
        movie[movie_cnt] = {mID, movie_cnt, mTotal, mGenre};
        genre[0].insert(movie[movie_cnt]);
        genre[mGenre].insert(movie[movie_cnt]);
        movie_cnt++;
        return 1;
    }
    else
    {
        return 0;
    }
}

// 1,000
int erase(int mID)
{
    if (movie_table.find(mID) == movie_table.end() || movie_delete_table[mID])
    {
        return 0;
    }
    movie_delete_table[mID] = true;
    return 1;
}

// 30,000
int watch(int uID, int mID, int mRating)
{
    if (movie_table.find(mID) == movie_table.end() || person[uID].watch_movie_table[mID] || movie_delete_table[mID])
    {
        return 0;
    }
    person[uID].watch_movie.push_back({mID, mRating});
    person[uID].watch_movie_table[mID] = true;
    movie[movie_table[mID]].total += mRating;
    genre[0].insert(movie[movie_table[mID]]);
    genre[movie[movie_table[mID]].genre].insert(movie[movie_table[mID]]);
    return 1;
}

// 5,000
RESULT suggest(int uID)
{
    RESULT res;
    int cnt = 0;
    int idx = 1;
    int high_score = -1;
    int personal_genre = 0;
    unordered_map<int, bool> suggest_movie;

    while (cnt < 5)
    {
        int movie_idx = person[uID].watch_movie.size() - idx++;
        if (movie_idx < 0)
            break;
        if (movie_delete_table[person[uID].watch_movie[movie_idx].mID])
            continue;
        if (high_score < person[uID].watch_movie[movie_idx].score)
        {
            high_score = person[uID].watch_movie[movie_idx].score;
            personal_genre = movie[movie_table[person[uID].watch_movie[movie_idx].mID]].genre;
        }
        cnt++;
    }

    res.cnt = 0;
    for (auto k : genre[personal_genre])
    {
        if (!suggest_movie[k.id] && !person[uID].watch_movie_table[k.id] && !movie_delete_table[k.id])
        {
            suggest_movie[k.id] = true;
            res.IDs[res.cnt++] = k.id;
            if (res.cnt >= 5)
                break;
        }
    }

    return res;
}