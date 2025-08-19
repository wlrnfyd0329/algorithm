// 가지고 있는 값을 전부 빼는 것이 아니라 새로 추가 되는 값에 뺏던 값만큼 더해주면 통일되게 관리가 가능하다.

#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

#define MAX_PRODUCT 50005
#define MAX_COMP 6
#define MAX_CATE 6

using namespace std;

struct Sale
{
    set<pair<int, int>> product; // {가격, mID}
    int amount;
    int cnt;
} sale[MAX_CATE][MAX_COMP];

struct Product
{
    int mID, mCate, mCom, mPrice;
    bool isClosed;
} product[MAX_PRODUCT];

unordered_map<int, int> product_table;
int product_idx;

struct RESULT
{
    int cnt;
    int IDs[5];
};

void init()
{
    product_idx = 1;
    product_table.clear();
    for (int i = 1; i < MAX_CATE; i++)
    {
        for (int j = 1; j < MAX_COMP; j++)
        {
            sale[i][j].product.clear();
            sale[i][j].amount = 0;
            sale[i][j].cnt = 0;
        }
    }
    return;
}

// 50,000
int sell(int mID, int mCategory, int mCompany, int mPrice)
{
    int temp_price = sale[mCategory][mCompany].amount;

    product[product_idx] = { mID, mCategory, mCompany,  mPrice + temp_price, false };
    product_table[mID] = product_idx++;
    sale[mCategory][mCompany].product.insert({ mPrice + temp_price, mID });
    return ++sale[mCategory][mCompany].cnt;
}

// 5,000
int closeSale(int mID)
{
    int idx = product_table[mID];
    if (!idx || product[idx].isClosed) return -1;
    product[idx].isClosed = true;
    sale[product[idx].mCate][product[idx].mCom].cnt--;
    return product[idx].mPrice - sale[product[idx].mCate][product[idx].mCom].amount;
}

// 10,000
// 단순하게 생각하면 최대 50,000이고 10,000번 연산하기에 시간이 초과된다고 생각할 수 있지만
// 결국 N이 생겼지만 하나하나 지우기 때문에 50,000이 최대이며 NlogN임을 알 수 있다.
int discount(int mCategory, int mCompany, int mAmount)
{
    Sale* cur_sale = &sale[mCategory][mCompany];
    cur_sale->amount += mAmount;
    for (auto iter = cur_sale->product.begin(); iter != cur_sale->product.end();)
    {
        if (iter->first - cur_sale->amount > 0) break;
        if (!product[product_table[iter->second]].isClosed) {
            product[product_table[iter->second]].isClosed = true;
            cur_sale->cnt--;
        }
        iter = cur_sale->product.erase(iter);
    }
    return cur_sale->cnt;
}

// 1,000
RESULT show(int mHow, int mCode)
{
    RESULT res;
    vector<pair<int, int>> pro;

    for (int i = 1; i < MAX_CATE; i++) {
        if (mHow == 1 && i != mCode) continue;
        for (int j = 1; j < MAX_COMP; j++) {
            if (mHow == 2 && j != mCode) continue;
            int cnt = 0;
            for (auto k : sale[i][j].product) {
                if (cnt >= 5) break;
                if (!product[product_table[k.second]].isClosed) {
                    pro.push_back({ k.first - sale[i][j].amount, k.second });
                    cnt++;
                }
            }
        }
    }

    sort(pro.begin(), pro.end());
    if (pro.size() <= 5) {
        res.cnt = pro.size();
    }
    else {
        res.cnt = 5;
    }
    
    for (int i = 0; i < res.cnt; i++) {
        res.IDs[i] = pro[i].second;
    }

    return res;
}
