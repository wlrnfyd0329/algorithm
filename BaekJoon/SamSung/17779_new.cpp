#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arr[25][25];
int boundary[25][25];

int fifth_boundary(int x, int y, int d1, int d2) {
    int cnt = 0;
    for (int i = 0; i <= d1; i++) {
        boundary[x + i][y - i] = 5;
        boundary[x + d2 + i][y + d2 - i] = 5;
    }

    for (int i = 0; i <= d2; i++) {
        boundary[x + i][y + i] = 5;
        boundary[x + d1 + i][y - d1 + i] = 5;
    }

    for (int i = x + 1; i < x + d1 + d2; i++) {
        bool isIn = false;
        for(int j = y - d1; j <= y + d2; j++) {
            if (boundary[i][j] == 5) {
                isIn = !isIn;
                continue;
            }
            if (isIn) {
                boundary[i][j] = 5;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (boundary[i][j] == 5) {
                cnt += arr[i][j];
            }
        }
    }

    return cnt;
}


int first_boundary(int x, int y, int d1, int d2) {
    int cnt = 0;
    for(int i = 1; i < x + d1; i++) {
        for(int j = 1; j <= y; j++) {
            if (boundary[i][j] == 5) break;
            boundary[i][j] = 1;
            cnt += arr[i][j];
        }
    }

    return cnt;
}

int third_boundary(int x, int y, int d1, int d2) {
    int cnt = 0;
    for(int i = x + d1; i <= n; i++) {
        for(int j = 1; j < y - d1 + d2; j++) {
            if (boundary[i][j] == 5) break;
            boundary[i][j] = 3;
            cnt += arr[i][j];
        }
    }

    return cnt;
}

int second_boundary(int x, int y, int d1, int d2) {
    int cnt = 0;
    for(int i = 1; i <= x + d2; i++) {
        for(int j = n; j > y; j--) {
            if (boundary[i][j] == 5) break;
            boundary[i][j] = 2;
            cnt += arr[i][j];
        }
    }

    return cnt;
}

int fourth_boundary(int x, int y, int d1, int d2) {
    int cnt = 0;
    for(int i = x + d2 + 1; i <= n; i++) {
        for(int j = n; j >= y - d1 + d2; j--) {
            if (boundary[i][j] == 5) break;
            boundary[i][j] = 4;
            cnt += arr[i][j];
        }
    }

    return cnt;
}

int cal(int x, int y, int d1, int d2) {
    vector<int> v;
    fill(boundary[0], boundary[24], 0);
    v.push_back(fifth_boundary(x, y, d1, d2));
    v.push_back(first_boundary(x, y, d1, d2));
    v.push_back(second_boundary(x, y, d1, d2));
    v.push_back(third_boundary(x, y, d1, d2));
    v.push_back(fourth_boundary(x, y, d1, d2));
    
    return *max_element(v.begin(), v.end()) - *min_element(v.begin(), v.end());
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    int result = 50000;
    for(int d1 = 1; d1 <= n; d1++) {
        for(int d2 = 1; d2 <= n; d2++) {
            for(int x = 1; x <= n - d1 - d2; x++) {
                for (int y = d1 + 1; y <= n - d2; y++) {
                    result = min(result, cal(x, y, d1, d2));
                }
            }
        }
    }
    cout << result;
}