#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, h;
int ladder[35][15];
int cladder[35][15];
vector<pair<int,int>> leg;

bool check() {
    for(int i = 1; i <= n; i++) {

        int temp = i;
        for(int j = 1; j <= h; j++) {
            temp += cladder[j][temp];
        }
        if(temp != i) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> h;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ladder[a][b]++;
        ladder[a][b+1]--;
        cladder[a][b]++;
        cladder[a][b + 1]--;
    }

    if(check()) {
        cout << 0;
        return 0;
    }

    for(int i = 1; i <= h; i++) {
        for(int j = 1; j < n; j++) {
            if(ladder[i][j] == 0 && ladder[i][j + 1] == 0) {
                leg.push_back({i, j});
            }
        }
    }

    cout << "\n\n";
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << ladder[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n\n";
    for (auto k : leg)
    {
        cout << k.first << " " << k.second << "\n";
    }

    int temp = leg.size();
    if(!temp) { // 이부분에서 틀림
        cout << -1;
        return 0 ;
    }
    else if(temp > 3) {
        temp = 3;
    }

    vector<int> cleg(leg.size(), 1);
    for(int i = 0; i < temp; i++) {
        cleg[i] = 0;
        do {
            for(int l = 1; l <= h; l++) {
                for(int j = 1; j <= n; j++) {
                    cladder[l][j] = ladder[l][j];
                }
            }
            for(int j = 0; j < cleg.size(); j++) {
                if(cleg[j] == 0) {
                    cladder[leg[j].first][leg[j].second]++;
                    cladder[leg[j].first][leg[j].second + 1]--;
                }
            }

            cout << "\n\n" << check() << "\n";
            for (int i = 1; i <= h; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << cladder[i][j] << " ";
                }
                cout << "\n";
            }

            if(check()) {
                cout << i+1;
                return 0;
            }
        } while(next_permutation(cleg.begin(), cleg.end()));

    }

    cout << -1;

}

/*
조합해서 선택하는 느낌은 백트레킹을 사용하는 문제인 듯하다.
한번 틀렸던 이유는 사다리를 놓을 수 있는 공간의 크기를 0일때를 체크해야하는데 체크하지 않았다.
*/