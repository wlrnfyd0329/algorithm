// 시간복잡도를 생각하지 않고 경우의 수를 찾는 것을 생각하면 모두 탐색하는 방법이 있다
// 또한 바다물에 넘치는 것을 생각해보면 bfs 방법이 있을 수 있다

#include <iostream>
using namespace std;

int n;
int map[20][20];

void init(int N, int mMap[20][20])
{
    n = N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            map[i][j] = mMap[i][j];
        }
    }
}

int numberOfCandidate(int M, int mStructure[5])
{
    int cnt = 0;
    if (M == 1) return n * n;
    for(int i = 0; i < n; i++) { // 가로 방향 체크
        for (int j = 0; j <= n - M; j++) {
            int sum = map[i][j] + mStructure[0];
            bool isPossible1 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i][j + k] + mStructure[k]) {
                    isPossible1 = false;
                    break;
                }
            }

            if (isPossible1) {
                cnt++;
            }

            sum = map[i][j] + mStructure[M - 1];
            bool isPossible2 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i][j + k] + mStructure[M - 1 - k]) {
                    isPossible2 = false;
                    break;
                }
            }

            if (isPossible2) {
                cnt++;
            }

            if (isPossible1 && isPossible2) {
                cnt--;
            }
        }
    }

    for(int i = 0; i <= n - M; i++) { // 세로 방향 체크
        for (int j = 0; j < n; j++) {
            int sum = map[i][j] + mStructure[0];
            bool isPossible1 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i + k][j] + mStructure[k]) {
                    isPossible1 = false;
                    break;
                }
            }

            if (isPossible1) {
                cnt++;
            }

            sum = map[i][j] + mStructure[M - 1];
            bool isPossible2 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i + k][j] + mStructure[M - 1 - k]) {
                    isPossible2 = false;
                    break;
                }
            }
            
            if (isPossible2) {
                cnt++;
            }

            if (isPossible1 && isPossible2) {
                cnt--;
            }
        }
    }

    return cnt;
}

int checkArea(int m, int mStructure[5], bool isReverse, int level, int x[5], int y[5])
{
    // 바다가 밀려오듯이 break해버리면 중간에 끼어있는 친구들은 살아남는다
    // 따라서 범위 밖에서 bfs하면 전부 탐색할 수 있다
    int area = n * n;

    for(int i = 0; i < m; i++) {
        if (isReverse) {
            map[x[i]][y[i]] += mStructure[m - 1 - i];
        }
        else {
            map[x[i]][y[i]] += mStructure[i];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(map[i][j] >= level) {
                break;
            }
            area--;
        }

        for(int j = n - 1; j >= 0; j--) {
            if(map[i][j] >= level) {
                break;
            }
            area--;
        }
    }

    for (int j = 0; j < n; j++) {
        for(int i = 0; i < n; i++) {
            if(map[i][j] >= level) {
                break;
            }
            area--;
        }

        for(int i = n - 1; i >= 0; i--) {
            if(map[i][j] >= level) {
                break;
            }
            area--;
        }
    }


    for(int i = 0; i < m; i++) {
        if (isReverse) {
            map[x[i]][y[i]] -= mStructure[m - 1 - i];
        }
        else {
            map[x[i]][y[i]] -= mStructure[i];
        }
    }

    return area;
}

int maxArea(int M, int mStructure[5], int mSeaLevel) {
    int max_area = 0;

    for(int i = 0; i < n; i++) { // 가로 방향 체크
        for (int j = 0; j < n - M; j++) {
            int x[5] = {i, };
            int y[5] = {j, };
            int sum = map[i][j] + mStructure[0];
            bool isPossible1 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i][j + k] + mStructure[k]) {
                    isPossible1 = false;
                    break;
                }
                x[k] = i;
                y[k] = j + k;
            }

            sum = map[i][j] + mStructure[M - 1];
            bool isPossible2 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i][j + k] + mStructure[M - 1 - k ]) {
                    isPossible2 = false;
                    break;
                }
            }

            if (isPossible1 && !isPossible2) {
                int area = checkArea(M, mStructure, false, mSeaLevel, x, y);
                if (area > max_area) max_area = area;
            }
            if (!isPossible1 && isPossible2) {
                int area = checkArea(M, mStructure, true, mSeaLevel, x, y);
                if (area > max_area) max_area = area;
            }
        }
    }

    for(int i = 0; i < n - M; i++) { // 세로 방향 체크
        for (int j = 0; j < n; j++) {
            int x[5] = {i, };
            int y[5] = {j, };
            int sum = map[i][j] + mStructure[0];
            bool isPossible1 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i + k][j] + mStructure[k]) {
                    isPossible1 = false;
                    break;
                }
                x[k] = i + k;
                y[k] = j;
            }

            sum = map[i][j] + mStructure[M - 1];
            bool isPossible2 = true;
            for (int k = 1; k < M; k++) {
                if (sum != map[i + k][j] + mStructure[M - 1 - k]) {
                    isPossible2 = false;
                    break;
                }
            }

            if (isPossible1 && !isPossible2) {
                int area = checkArea(M, mStructure, false, mSeaLevel, x, y);
                if (area > max_area) max_area = area;
            }
            if (!isPossible1 && isPossible2) {
                int area = checkArea(M, mStructure, true, mSeaLevel, x, y);
                if (area > max_area) max_area = area;
            }
        }
    }

    return max_area;
}