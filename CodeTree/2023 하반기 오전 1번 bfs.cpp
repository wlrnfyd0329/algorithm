#include <iostream>
#include <vector>
#include <queue>

#define MAX_BOARD 41
#define MAX_KNIGHT 31

using namespace std;

struct Knight {
   int r, c, h, w, k, dmg;
};

vector<vector<int>> map(MAX_BOARD, vector<int>(MAX_BOARD, 0));
vector<vector<int>> knight_map(MAX_BOARD, vector<int>(MAX_BOARD, 0));
vector<Knight> knights(MAX_KNIGHT, { 0, 0, 0, 0, 0, 0 });

int L, N, Q;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool isRange(int x, int y) {
   return x >= 1 && x <= L && y >= 1 && y <= L;
}

// 살아있는 애들만 옮기기
void checkKnights(int num, int dir) {

   // 살아 있는 기사 대상으로 확인하기
   if (knights[num].k <= 0) return ;

   vector<vector<int>> temp_map(MAX_BOARD, vector<int>(MAX_BOARD, 0));
   queue<Knight> q;
   vector<bool> visit(31, false);
   q.push(knights[num]);
   visit[num] = true;
   
   while(!q.empty()) {
      Knight curr = q.front(); q.pop();

      for (int j = curr.r; j < curr.r + curr.h; j++) {
         for (int k = curr.c; k < curr.c + curr.w; k++) {

            int nx = j + dx[dir];
            int ny = k + dy[dir];

            // 못가면 움직이지 않기
            if (!isRange(nx, ny) || map[nx][ny] == 2) return ;

            // 갈 수 있으면 임시 배열에 가고
            temp_map[nx][ny] = knight_map[j][k];

            // 다음 좌표 0이면 머 상관없음
            if (knight_map[nx][ny] == 0) continue;
            // 다음 좌표 같아도 머 상관없음
            if (knight_map[nx][ny] == knight_map[j][k]) continue;

            // 어? 갔는데 다른 애가 있네? 그럼 얘도 옮겨야 함            
            // 죽어있는 애면 상관 없음
            if (knights[knight_map[nx][ny]].k <= 0) continue;
            // 이미 처리된 애면 상관 없음
            if (visit[knight_map[nx][ny]]) continue;

            visit[knight_map[nx][ny]] = true;
            q.push(knights[knight_map[nx][ny]]);
         }
      }
   }

   // 임시 배열 정보와 knight_map을 합쳐야 함
   // 옮긴 애만 반영하면 됨.
   for (int i = 1; i <= L; i++) {
      for (int j = 1; j <= L; j++) {
         int number = knight_map[i][j];

         // 현재 좌표가 0이 아닌데, 방문한 적이 없어?
         // 옮길 필요가 없는 애임;
         if (number != 0 && !visit[number] && knights[number].k > 0) continue;

         // 현재 좌표 값이 0이거나 있는데 옮긴 애면 갱신함;
         knight_map[i][j] = temp_map[i][j];
      }
   }
   
   for (int j = 1; j <= N; j++) {
      if (visit[j]) {
         knights[j].r += dx[dir];
         knights[j].c += dy[dir];
      }
   }
   
   // 대결 데미지 계산
   for (int j = 1; j <= L; j++) {
      for (int k = 1; k <= L; k++) {
         if (knight_map[j][k] == num) continue;
         if (visit[knight_map[j][k]] && map[j][k] == 1) {
            int tmp = knight_map[j][k];
            knights[tmp].k--;
            knights[tmp].dmg++;
         }
      }
   }
}

int main() {

   ios::sync_with_stdio(false);
   cin.tie(0); cout.tie(0);

   cin >> L >> N >> Q;

   // map 초기화
   for (int i = 1; i <= L; i++) {
      for (int j = 1; j <= L; j++) {
         cin >> map[i][j];
      }
   }

   // 기사 초기화
   for (int i = 1; i <= N; i++) {
      cin >> knights[i].r >> knights[i].c >> knights[i].h >> knights[i].w >> knights[i].k;

      for (int j = 0; j < knights[i].h; j++) {
         for (int k = 0; k < knights[i].w; k++) {
            knight_map[knights[i].r + j][knights[i].c + k] = i;
         }
      }
   }

   // 명령어 받기
   for (int i = 0; i < Q; i++) {
      int num, dir;
      cin >> num >> dir;

      // 옮길 수 있으면
      checkKnights(num, dir);

   }

   // 살아있는 애들의 데미지 계산
   int res = 0;
   for (auto& knight : knights) {
      if (knight.k > 0) {
         
         res += knight.dmg;
      }
   }
   
   cout << res << endl;

   return 0;
}
