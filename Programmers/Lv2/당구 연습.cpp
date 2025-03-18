#include <string>
#include <vector>
#include <iostream>
#define X first
#define Y second

using namespace std;

int cal(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

vector<int> solution(int m, int n, int startX, int startY, vector<vector<int>> balls)
{
    int position[4][2] = {{-startX, startY}, {startX, -startY}, {2 * m - startX, startY}, {startX, 2 * n - startY}};

    vector<int> answer;
    for (auto ball : balls)
    {
        int dist = 3'000'000;
        if (!(ball[0] == startX && ball[1] < startY)) // 공이 아래쪽이 겹친다
        {
            dist = min(dist, cal(ball[0], ball[1], position[1][0], position[1][1]));
        }
        if (!(ball[0] == startX && ball[1] > startY)) // 공이 위쪽이 겹친다
        {
            dist = min(dist, cal(ball[0], ball[1], position[3][0], position[3][1]));
        }
        if (!(ball[0] > startX && ball[1] == startY)) // 공이 오른쪽이 겹친다
        {
            dist = min(dist, cal(ball[0], ball[1], position[2][0], position[2][1]));
        }
        if (!(ball[0] < startX && ball[1] == startY)) // 공이 왼쪽이 겹친다
        {
            dist = min(dist, cal(ball[0], ball[1], position[0][0], position[0][1]));
        }

        answer.push_back(dist);
    }
    return answer;
}