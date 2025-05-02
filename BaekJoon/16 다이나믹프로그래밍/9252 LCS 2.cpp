#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

string s1, s2;
int board[1005][1005];
vector<char> ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s1 >> s2;
    for(int i = 1; i <= s1.size(); i++) {
        for(int j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                board[i][j] = board[i - 1][j - 1] + 1;
            }
            else {
                board[i][j] = max(board[i - 1][j], board[i][j - 1]);
            }
        }
    }

    int x = s1.size(), y = s2.size();
    while(board[x][y] != 0) {
        if (board[x - 1][y] != board[x][y] && board[x][y - 1] != board[x][y]) {
            x--;
            y--;
            ans.push_back(s1[x]);
        }
        else if (board[x - 1][y] == board[x][y]) {
            x--;
        }
        else {
            y--;
        }
    }

    cout << ans.size() << endl;
    for(int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
}