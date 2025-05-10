// DP 문제였다. Bottom-Up 느낌으로 차례대로 행렬을 하나씩 해가면서 최솟값을 찾는 문제다.

#include <iostream>
#define X first
#define Y second
#define endl "\n"

using namespace std;

const int INF = (1 << 31) - 1;
int N, ans = 0;
int matrix[505][2];
int dp[505][505]; // [i][j]일때, i번부터 j번 행렬까지 곱의 최솟값

// 3중 for 문의 동작은 아래와 같다.

// i : 곱셈 연산에 참여한 행렬 수
// j : 곱셈 시작 행렬의 번호
// k : 시작점 j부터 i+j 위치까지 탐색을 위한 변수
// k를 기준으로 나눠진 행렬은 각 나눠진 행렬을 만들때까지의 곱셈의 최솟값이 들어있고
// 거기에 최종적으로 만들어질 j x (i + j) 행렬의 곱셈을 더해야 한다. 이는 N x M x K이다.
// 해당 for 문은 j부터 시작하여 i+j까지의 행렬의 곱셈의 최솟값을 구한다.

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        int r, c;
        cin >> r >> c;
        matrix[i][0] = r;
        matrix[i][1] = c;
    }

    for(int i = 1; i < N; i++) {
        for (int j = 1; i + j <= N; j++) {
            dp[j][i + j] = INF;
            for(int k = j; k <= i + j; k++) {
                dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + matrix[j][0] * matrix[k][1] * matrix[i + j][1]);
            }
        }
    }

    cout << dp[1][N];
}