#include <map>

using namespace ::std;

const int N = 100;
const int MAX_NUM_NODE = 400210;
const int LAST_START_NODE = N;
const int FIRST_END_NODE = MAX_NUM_NODE - N - 5;

struct Node
{
    Node *prev;
    Node *next;
} node[MAX_NUM_NODE];   // 교점들의 이중 연결 리스트

void link(Node *front, Node *back)  // 두 정점을 서로 연결해주기
{
    front->next = back;
    back->prev = front;
}

map<int, Node *> nodeMap[N + 1];    // nodeMap[x] := x번 세로줄의 정점들의 y 좌표를 들고 있는 TreeMap
Node *newNode;

void init()
{
    for (int i = 1; i <= N; i++)
    {
        nodeMap[i].clear();
        nodeMap[i][0] = node + i;                                   // i 번 세로줄에 i 번 참가자를 놓는다.
        nodeMap[i][1000000000] = node + FIRST_END_NODE + i - 1;     // i 번 세로줄의 도착점을 추가한다.
        link(node + i, node + FIRST_END_NODE + i - 1);
    }
    newNode = node + N + 1;
}

void add(int mX, int mY)    // (mX, mY)와 (mX + 1, mY)을 잇는 가로줄 추가하기, O(Log N)
{
    Node *nowLeft = newNode++;
    Node *nowRight = newNode++;

    Node *prevLeft = (--nodeMap[mX].upper_bound(mY))->second;       // mX 번 세로 줄에서 mY 직전 정점 찾기
    Node *prevRight = (--nodeMap[mX + 1].upper_bound(mY))->second;  // (mX + 1) 번 세로 줄에서 mY 직전 정점 찾기

    Node *nextLeft = prevLeft->next;        // mX 번 세로 줄에서 mY 직후 정점 찾기
    Node *nextRight = prevRight->next;      // (mX + 1) 번 세로 줄에서 mY 직후 정점 찾기

    // 순서 재조정 하기
    link(prevLeft, nowRight);
    link(nowRight, nextRight);

    link(prevRight, nowLeft);
    link(nowLeft, nextLeft);

    nodeMap[mX][mY] = nowLeft;
    nodeMap[mX + 1][mY] = nowRight;
}

void remove(int mX, int mY)     // (mX, mY)와 (mX + 1, mY)을 잇는 가로줄 제거하기, O(Log N)
{
    Node *nowLeft = nodeMap[mX][mY];        // mX번 세로 줄에서 mY 위치 정점 찾기
    Node *nowRight = nodeMap[mX + 1][mY];   // (mX + 1)번 세로 줄에서 mY 위치 정점 찾기

    Node *prevLeft = nowRight->prev;
    Node *prevRight = nowLeft->prev;

    Node *nextLeft = nowLeft->next;
    Node *nextRight = nowRight->next;

    // 순서 재조정 하기
    link(prevLeft, nextLeft);
    link(prevRight, nextRight);

    nodeMap[mX].erase(mY);
    nodeMap[mX + 1].erase(mY);
}

int numberOfCross(int mID)      // mID번 참가자가 지나게 되는 가로줄의 개수 구하기, O(5000)
{
    int ret = -1;
    Node *now = node + mID; // mID 번 세로줄에서 출발하기
    while (now < node + FIRST_END_NODE) // 마지막 줄에 도착할 때까지 다음으로 이동하기
    {
        ret++;
        now = now->next;
    }
    return ret;
}

int participant(int mX, int mY)     // (mX, mY)에 도착하는 참가자 찾기, O(5000)
{
    Node *now = (--nodeMap[mX].upper_bound(mY))->second;    // mX 번 세로 줄에서 mY 직전 정점 찾기
    while (now > node + LAST_START_NODE)    // 최상단에 도착할 때까지 이전으로 돌아가기
        now = now->prev;
    return now - node;
}