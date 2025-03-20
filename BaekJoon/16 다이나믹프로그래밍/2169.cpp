#include <iostream>

using namespace std;

int n, m;
int board[1005][1005];
int ans[1005][1005];

int dx[3] = {0, 0, -1};
int dy[3] = {-1, 1, 0};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> board[i][j];
            ans[i][j] = -2'000'000'000;
        }
    }

    ans[1][1] = board[1][1];

    for (int i = 2; i <= m; i++)
    {
        ans[1][i] = ans[1][i - 1] + board[1][i];
    }

    for (int i = 2; i <= n; i++)
    {
        int dp_left[1005], dp_right[1005];

        dp_left[1] = board[i][1] + ans[i - 1][1];
        for (int j = 2; j <= m; j++)
        {
            dp_left[j] = max(dp_left[j - 1], ans[i - 1][j]) + board[i][j];
        }

        dp_right[m] = board[i][m] + ans[i - 1][m];
        for (int j = m - 1; j >= 1; j--)
        {
            dp_right[j] = max(dp_right[j + 1], ans[i - 1][j]) + board[i][j];
        }

        for (int j = 1; j <= m; j++)
        {
            ans[i][j] = max(dp_left[j], dp_right[j]);
        }
    }

    cout << ans[n][m];
}