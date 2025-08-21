// 사각형의 위치는 임의로 지정됨을 보장하기에 버킷 알고리즘 사용
// 버킷의 사이즈는 단순히 N / L로 board의 길이의 사각형 최대 길이로 잡으면 무조건 하나는 포함될 것이라 생각
// 좌표판의 넓이와 사각형의 최대 넓이를 계산해서 한변의 길이를 구한 후 버킷을 나눠도 무방하다.

#include <unordered_map>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_BUC 55
#define MAX_SQUARE 15005

unordered_map<int, int> mid_to_idx;
int squ_idx = 1;
int buc_size;
int len;
int p[MAX_SQUARE];
struct SQUARE {
    int r, c, h, w;
} square[MAX_SQUARE];
vector<int> board[MAX_BUC][MAX_BUC];

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (p[u] < p[v]) swap(u, v);
    p[v] += p[u];
    p[u] = v;
    return true;
}

bool is_overlap(SQUARE& a, SQUARE& b) { // 겹치는지 확인
    if (a.r >= b.r + b.h || b.r >= a.r + a.h) return false;
    if (a.c >= b.c + b.w || b.c >= a.c + a.w) return false;
    return true;
}

void init(int L, int N) {
    buc_size = N / L;
    len = L;
    mid_to_idx.clear();
    squ_idx = 1;
    for (int i = 0; i <= buc_size; i++) {
        for (int j = 0; j <= buc_size; j++) {
            board[i][j].clear();
        }
    }
}

// 15,000
int draw(int mID, int mRow, int mCol, int mHeight, int mWidth) {
    mid_to_idx[mID] = squ_idx;
    square[squ_idx] = { mRow, mCol, mHeight, mWidth };
    p[squ_idx] = -1;
    for (int i = mRow / len; i <= (mRow + mHeight - 1) / len; i++) {
        for (int j = mCol / len; j <= (mCol + mWidth - 1) / len; j++) {
            for (auto k : board[i][j]) {
                if (is_overlap(square[k], square[squ_idx])) {
                    uni(k, squ_idx);
                }
            }
            board[i][j].push_back(squ_idx);
        }
    }

    return -p[find(squ_idx++)];
}

// 5,000
int getRectCount(int mID) {
    if (!mid_to_idx[mID]) return 0;
    return -p[find(mid_to_idx[mID])];
}

// 2,000
int countGroup() {
    int cnt = 0;
    for (int i = 1; i < squ_idx; i++) {
        if (p[i] < 0) cnt++;
    }
    return cnt;
}