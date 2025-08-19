// 가지고 있는 값을 전부 빼는 것이 아니라 새로 추가 되는 값에 뺏던 값만큼 더해주면 통일되게 관리가 가능하다.

#include <unordered_map>
#include <set>
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

    product[product_idx] = {mID, mCategory, mCompany, mPrice, false};
    product_table[mID] = product_idx++;
    sale[mCategory][mCompany].product.insert({mPrice + temp_price, mID});
    return ++sale[mCategory][mCompany].cnt;
}

// 5,000
int closeSale(int mID)
{
    if (!product_table[mID] || product[product_table[mID]].isClosed)
        return -1;
    int temp_price = product[product_table[mID]].mPrice - sale[product[product_table[mID]].mCate][product[product_table[mID]].mCom].amount;
    if (temp_price <= 0)
    {
        product[product_table[mID]].isClosed = true;
        return -1;
    }
    return temp_price;
}

// 10,000
int discount(int mCategory, int mCompany, int mAmount)
{
    return -1;
}

// 1,000
RESULT show(int mHow, int mCode)
{
    RESULT res;

    res.cnt = -1;

    return res;
}
