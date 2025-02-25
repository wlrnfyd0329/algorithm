#include <iostream>

using namespace std;

int score = 0;
int green[6][4];
int blue[6][4];

void print() {
    cout << "\n";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << green[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << blue[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void check(int (&arr)[6][4]) {
    for(int i = 2; i < 6; i++) {
        if (arr[i][0] && arr[i][1] && arr[i][2] && arr[i][3]) {
            for(int j = i; j >= 1; j--) {
                arr[j][0] = arr[j-1][0];
                arr[j][1] = arr[j-1][1];
                arr[j][2] = arr[j-1][2];
                arr[j][3] = arr[j-1][3];
            }
            for (int k = 0; k < 4; k++) {
                arr[0][k] = 0;
            }
            score++;
        }
    }
}

void remove(int (&arr)[6][4]) {
    for(int i = 0; i < 2; i++) {
        if (arr[1][0] || arr[1][1] || arr[1][2] || arr[1][3]) {
            for(int j = 5; j >= 1; j--) {
                arr[j][0] = arr[j-1][0];
                arr[j][1] = arr[j-1][1];
                arr[j][2] = arr[j-1][2];
                arr[j][3] = arr[j-1][3];
            }
        }
    }
    for (int k = 0; k < 4; k++) {
        arr[0][k] = 0;
        arr[1][k] = 0;
    }
}

void input1(int (&arr)[6][4], int n) {
    for(int i = 2; i < 6; i++) {
        if (arr[i][n]) {
            arr[i-1][n] = 1;
            break;
        }
        else {
            if (i == 5) {
                arr[i][n] = 1;
            }
        }
    }
    check(arr);
    remove(arr);
}

void input2(int (&arr)[6][4], int n) {
    for(int i = 2; i < 6; i++) {
        if (arr[i][n] || arr[i][n+1]) {
            arr[i-1][n] = 1;
            arr[i-1][n+1] = 1;
            break;
        }
        else {
            if (i == 5) {
                arr[5][n] = 1;
                arr[5][n+1] = 1;
            }
        }
    }
    check(arr);
    remove(arr);
}

void input3(int (&arr)[6][4], int n) {
    for(int i = 2; i < 6; i++) {
        if (arr[i][n]) {
            arr[i-1][n] = 1;
            arr[i-2][n] = 1;
            break;
        }
        else {
            if (i == 5) {
                arr[i-1][n] = 1;
                arr[i][n] = 1;
            }
        }
    }
    check(arr);
    remove(arr);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        switch (t)
        {
            case 1:
                input1(blue, x);
                input1(green, y);
                break;
            case 2:
                input3(blue, x);
                input2(green, y);
                break;
            case 3:
                input2(blue, x);
                input3(green, y);
                break;
        }
    }
    cout << score << "\n";
    int cnt = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (green[i][j]) cnt++;
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (blue[i][j]) cnt++;
        }
    }
    cout << cnt;
}