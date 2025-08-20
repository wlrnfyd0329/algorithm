// 복잡하게 왔다갔다 풀었지만 그냥 개수를 관리하는 것이 간단하고 좋은 방법일 듯하다.

#include <unordered_map>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define MAX_ORDER 20005
#define MAX_DRINK 200005
#define MAX_TYPE 15

struct Order;
struct Drink;

struct Order
{
    int mID, idx, cnt;
    bool isCancel;
    vector<Drink *> drink;
    set<Order>::iterator iter;

    bool operator<(const Order &other) const
    {
        if (cnt == other.cnt)
            return idx < other.idx;
        return cnt > other.cnt;
    }
};
Order ord[MAX_ORDER];
int ord_idx = 1;
int ord_cnt = 0;
set<Order> ord_set;

struct Drink
{
    Order *order;
    int type;
    bool isServed;
    Drink *prev;
    Drink *next;
};
Drink drink[MAX_DRINK];
int drink_idx = 0;

struct DrinkList
{
    Drink head;
    Drink tail;

    void link(Drink *front, Drink *back)
    {
        front->next = back;
        back->prev = front;
    }

    void init()
    {
        link(&head, &tail);
    }

    void push(Drink *node)
    {
        link(tail.prev, node);
        link(node, &tail);
    }

    void pop(Drink *node)
    {
        link(node->prev, node->next);
    }

    bool empty()
    {
        return head.next == &tail;
    }
} drink_type[MAX_TYPE];

unordered_map<int, int> mid_to_idx;

struct RESULT
{
    int cnt;
    int IDs[5];
};

// 3 <= N <= 10
void init(int N)
{
    ord_idx = 1;
    ord_cnt = 0;
    ord_set.clear();
    drink_idx = 0;
    for (int i = 1; i <= N; i++)
    {
        drink_type[i].init();
    }
    mid_to_idx.clear();
    return;
}

// 20,000
// 남은 주문 개수 반환
// 주문시 사용되는 음료 개수 1~10
int order(int mID, int M, int mBeverages[])
{
    mid_to_idx[mID] = ord_idx;
    ord[ord_idx] = {mID, ord_idx, M, false};
    auto it = ord_set.insert(ord[ord_idx]);
    ord[ord_idx].iter = it.first;
    for (int i = 0; i < M; i++)
    {
        drink[drink_idx] = {&ord[ord_idx], mBeverages[i], false};
        drink_type[mBeverages[i]].push(&drink[drink_idx]);
        ord[ord_idx].drink.push_back(&drink[drink_idx]);
        drink_idx++;
    }
    ord_idx++;
    return ++ord_cnt;
}

// 50,000
// 음료 배치 성공시, 주문 ID 반환 실패시 -1
// 남아 있는 모든 주문에서 음료가 없는 경우, 바로 버려짐
// 주문에 있는 음료 모두 제조시 주문 삭제
int supply(int mBeverage)
{
    if (drink_type[mBeverage].empty())
        return -1;
    auto beverage = drink_type[mBeverage].head.next;
    drink_type[mBeverage].pop(beverage);
    beverage->isServed = true;
    ord_set.erase(beverage->order->iter);
    if (--beverage->order->cnt == 0)
    {
        ord_cnt--;
    }
    else
    {
        auto it = ord_set.insert(*beverage->order);
        beverage->order->iter = it.first;
    }
    return beverage->order->mID;
}

// 1,000
// 주문 취소시 남은 음료 개수 반환
// 남은 음료 재배치
// 이미 취소 됐으면 -1, 이미 모든 음료가 제조된 경우는 0
int cancel(int mID)
{
    vector<int> v;
    int idx = mid_to_idx[mID];
    int cnt = 0;
    if (ord[idx].isCancel)
        return -1;
    if (ord[idx].cnt == 0)
        return 0;
    ord[idx].isCancel = true;
    ord_set.erase(ord[idx].iter);
    ord_cnt--;
    for (int i = 0; i < ord[idx].drink.size(); i++)
    {
        int type = ord[idx].drink[i]->type;
        if (ord[idx].drink[i]->isServed)
        {
            v.push_back(type);
        }
        else
        {
            drink_type[type].pop(ord[idx].drink[i]);
            cnt++;
        }
    }
    for (auto k : v)
    {
        supply(k);
    }
    return cnt;
}

// 5,000
// 남은 음료 개수 반환
// 이미 제조 완료시 0, 취소시 -1
int getStatus(int mID)
{
    int idx = mid_to_idx[mID];
    if (ord[idx].isCancel)
        return -1;
    return ord[idx].cnt;
}

// 10,000
// 음료 개수가 많은 순 -> 가장 먼저 주문 한 순
RESULT hurry()
{
    RESULT res;
    int cnt = 0;
    res.cnt = min(ord_cnt, 5);
    for (auto k : ord_set)
    {
        if (cnt == res.cnt)
            break;
        res.IDs[cnt++] = k.mID;
    }
    return res;
}