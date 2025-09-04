// 구간합을 사용했다면 시간을 많이 단축시킬 수 있다.

#include <vector>
#include <unordered_map>

using namespace std;

#define IMG_CNT 40
#define BUC_SIZE 405
#define BUC_LEN 25

struct Image {
    int size;
    vector<vector<vector<int>>> pixel;

    int depth(int x, int y, int dir) {
        int res = 0;
        for (int i = 0; i < BUC_LEN; i++) {
            for (int j = 0; j < BUC_LEN; j++) {
                int nx = x + i;
                int ny = y + j;
                if (nx < 0 || nx >= size || ny < 0 || ny >= size) continue;
                res += pixel[dir][nx][ny];
            }
        }
        return res;
    }
} image[IMG_CNT]; 
// 4 byte * 4 * 25 * 25 * 10 = 0.1MB
// 4 byte * 4 * 100 * 100 * 10 = 1.6MB
// 4 byte * 4 * 300 * 300 * 10 = 14.4MB
// 4 byte * 4 * 700 * 700 * 10 = 78.4MB

int img_idx = 0;
unordered_map<int, int> id_to_idx;

struct Info {
    int idx, id, x, y, dir; // 16 byte
};
int info_idx = 0;

vector<Info> map[BUC_SIZE][BUC_SIZE]; // 16 byte * 5000 = 80KB, 

void init(int N)
{
    img_idx = 0;
    info_idx = 0;
    id_to_idx.clear();
    for (int i = 0; i < BUC_SIZE; i++) {
        for (int j = 0; j < BUC_SIZE; j++) {
            map[i][j].clear();
        }
    }
}

void addPrint(int mID, int mSize, int mCnt, int mPixel[][3])
{
    id_to_idx[mID] = img_idx;
    image[img_idx].size = mSize;
    image[img_idx].pixel = vector<vector<vector<int>>> (4, vector<vector<int>>(mSize, vector<int>(mSize)));
    for (int i = 0; i < mCnt; i++) {
        image[img_idx].pixel[0][mPixel[i][0]][mPixel[i][1]] = mPixel[i][2];
        image[img_idx].pixel[1][mSize - 1 - mPixel[i][1]][mPixel[i][0]] = mPixel[i][2];
        image[img_idx].pixel[2][mSize - 1 - mPixel[i][0]][mSize - 1 - mPixel[i][1]] = mPixel[i][2];
        image[img_idx].pixel[3][mPixel[i][1]][mSize - 1 - mPixel[i][0]] = mPixel[i][2];
    }
    img_idx++;
}

void pressPrint(int mID, int mRow, int mCol, int mDir)
{
    int idx = id_to_idx[mID];
    int r = mRow / BUC_LEN;
    int c = mCol / BUC_LEN;
    int len = image[idx].size / BUC_LEN;
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= len; j++) {
            map[r + i][c + j].push_back({ info_idx, idx, mRow, mCol, mDir });
        }
    }
    info_idx++;
}

int getDepth(int mRow, int mCol)
{
    unordered_map<int, bool> table;
    int res = 0;
    int r = mRow / BUC_LEN;
    int c = mCol / BUC_LEN;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (auto k : map[r + i][c + j]) {
                if (table[k.idx]) continue;
                res += image[k.id].depth(mRow - k.x, mCol - k.y, k.dir);
                table[k.idx] = true;
            }
        }
    }
    return res;
}