#include <iostream>

using namespace std;

int score = 0;
int green[5][4]; // 0은 높이다
int blue[4][5];

void print() {
    cout << "\n";
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << green[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            cout << blue[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void greenCheck() {
    for(int i = 4; i >= 1; i--) { // green 체크
        if (green[i][0] && green[i][1] && green[i][2] && green[i][3]) {
            for(int j = i; j >= 2; j--) {
                green[j][0] = green[j - 1][0];
                green[j][1] = green[j - 1][1];
                green[j][2] = green[j - 1][2];
                green[j][3] = green[j - 1][3];
            }
            green[1][0] = 0;
            green[1][1] = 0;
            green[1][2] = 0;
            green[1][3] = 0;

            green[0][0] = 0;
            green[0][1] = 0;
            green[0][2] = 0;
            green[0][3] = 0;
            for(int j = 1; j <= 4; j++) {
                if (green[j][0]) green[0][0] = max(green[0][0], 5 - j);
                if (green[j][1]) green[0][1] = max(green[0][1], 5 - j);
                if (green[j][2]) green[0][2] = max(green[0][2], 5 - j);
                if (green[j][3]) green[0][3] = max(green[0][3], 5 - j);
            }
            score++;
            i++;
        }
    }
}

void blueCheck() {
    for(int j = 4; j >= 1; j--) { // blue 체크
        if (blue[0][j] && blue[1][j] && blue[2][j] && blue[3][j]) {
            for(int i = j; i >= 2; i--) {
                blue[0][i] = blue[0][i - 1];
                blue[1][i] = blue[1][i - 1];
                blue[2][i] = blue[2][i - 1];
                blue[3][i] = blue[3][i - 1];
            }
            blue[0][1] = 0;
            blue[1][1] = 0;
            blue[2][1] = 0;
            blue[3][1] = 0;

            blue[0][0] = 0;
            blue[0][1] = 0;
            blue[0][2] = 0;
            blue[0][3] = 0;
            for(int j = 1; j <= 4; j++) {
                if (blue[0][j]) blue[0][0] = max(blue[0][0], 5 - j);
                if (blue[1][j]) blue[1][0] = max(blue[1][0], 5 - j);
                if (blue[2][j]) blue[2][0] = max(blue[2][0], 5 - j);
                if (blue[3][j]) blue[3][0] = max(blue[3][0], 5 - j);
            }
            score++;
            j++;
        }
    }
}

void type1(int x, int y) {
    if (green[0][y] == 4) {
        for(int i = 4; i >= 2; i--) {
            green[i][0] = green[i - 1][0];
            green[i][1] = green[i - 1][1];
            green[i][2] = green[i - 1][2];
            green[i][3] = green[i - 1][3];
        }
        green[1][0] = 0;
        green[1][1] = 0;
        green[1][2] = 0;
        green[1][3] = 0;

        green[1][y] = 1;
        green[0][y] = 4;
        
        green[0][0] = 0;
        green[0][1] = 0;
        green[0][2] = 0;
        green[0][3] = 0;
        for(int j = 1; j <= 4; j++) {
            if (green[j][0]) green[0][0] = max(green[0][0], 5 - j);
            if (green[j][1]) green[0][1] = max(green[0][1], 5 - j);
            if (green[j][2]) green[0][2] = max(green[0][2], 5 - j);
            if (green[j][3]) green[0][3] = max(green[0][3], 5 - j);
        }
    }
    else {
        green[4 - green[0][y]++][y] = 1;
    }
    greenCheck();

    if (blue[x][0] == 4) {
        for(int i = 4; i >= 2; i--) {
            blue[0][i] = blue[0][i - 1];
            blue[1][i] = blue[1][i - 1];
            blue[2][i] = blue[2][i - 1];
            blue[3][i] = blue[3][i - 1];
        }
        blue[0][1] = 0;
        blue[1][1] = 0;
        blue[2][1] = 0;
        blue[3][1] = 0;

        blue[x][1] = 1;
        blue[x][0] = 4;

        blue[0][0] = 0;
        blue[0][1] = 0;
        blue[0][2] = 0;
        blue[0][3] = 0;
        for (int j = 1; j <= 4; j++)
        {
            if (blue[0][j])
                blue[0][0] = max(blue[0][0], 5 - j);
            if (blue[1][j])
                blue[1][0] = max(blue[1][0], 5 - j);
            if (blue[2][j])
                blue[2][0] = max(blue[2][0], 5 - j);
            if (blue[3][j])
                blue[3][0] = max(blue[3][0], 5 - j);
        }
    }
    else {
        blue[x][4 - blue[x][0]++] = 1;
    } 

    blueCheck();
}

void type2(int x, int y) {
    if (green[0][y] == 4 || green[0][y+1] == 4)
    {
        for (int i = 4; i >= 2; i--)
        {
            green[i][0] = green[i - 1][0];
            green[i][1] = green[i - 1][1];
            green[i][2] = green[i - 1][2];
            green[i][3] = green[i - 1][3];
        }
        green[1][0] = 0;
        green[1][1] = 0;
        green[1][2] = 0;
        green[1][3] = 0;

        green[1][y] = 1;
        green[1][y+1] = 1;

        green[0][y] = 4;
        green[0][y + 1] = 4;

        green[0][0] = 0;
        green[0][1] = 0;
        green[0][2] = 0;
        green[0][3] = 0;
        for(int j = 1; j <= 4; j++) {
            if (green[j][0]) green[0][0] = max(green[0][0], 5 - j);
            if (green[j][1]) green[0][1] = max(green[0][1], 5 - j);
            if (green[j][2]) green[0][2] = max(green[0][2], 5 - j);
            if (green[j][3]) green[0][3] = max(green[0][3], 5 - j);
        }
    }
    else
    {
        int height = max(green[0][y], green[0][y+1]);
        green[4 - height][y] = 1;
        green[4 - height][y+1] = 1;
        green[0][y] = height + 1;
        green[0][y+1] = height + 1;
    }
    greenCheck();

    if (blue[x][0] == 4)
    {
        for (int k = 0; k < 2; k++) {
            for (int i = 4; i >= 2; i--) {
                blue[0][i] = blue[0][i - 1];
                blue[1][i] = blue[1][i - 1];
                blue[2][i] = blue[2][i - 1];
                blue[3][i] = blue[3][i - 1];
            }
        }
        blue[0][1] = 0;
        blue[1][1] = 0;
        blue[2][1] = 0;
        blue[3][1] = 0;
        blue[0][2] = 0;
        blue[1][2] = 0;
        blue[2][2] = 0;
        blue[3][2] = 0;

        blue[x][1] = 1;
        blue[x][2] = 1;

        blue[x][0] = 4;

        blue[0][0] = 0;
        blue[0][1] = 0;
        blue[0][2] = 0;
        blue[0][3] = 0;
        for(int j = 1; j <= 4; j++) {
            if (blue[0][j]) blue[0][0] = max(blue[0][0], 5 - j);
            if (blue[1][j]) blue[1][0] = max(blue[1][0], 5 - j);
            if (blue[2][j]) blue[2][0] = max(blue[2][0], 5 - j);
            if (blue[3][j]) blue[3][0] = max(blue[3][0], 5 - j);
        }
    }
    else if (blue[x][0] == 3)
    {
        blue[x][1] = 1;
        blue[x][0] = 4;
        blueCheck();

        if (blue[x][0] == 4) {
            for (int i = 4; i >= 2; i--) {
                blue[0][i] = blue[0][i - 1];
                blue[1][i] = blue[1][i - 1];
                blue[2][i] = blue[2][i - 1];
                blue[3][i] = blue[3][i - 1];
            }
            blue[0][1] = 0;
            blue[1][1] = 0;
            blue[2][1] = 0;
            blue[3][1] = 0;

            blue[x][1] = 1;
            blue[x][0] = 4;

            blue[0][0] = 0;
            blue[0][1] = 0;
            blue[0][2] = 0;
            blue[0][3] = 0;
            for (int j = 1; j <= 4; j++)
            {
                if (blue[0][j])
                    blue[0][0] = max(blue[0][0], 5 - j);
                if (blue[1][j])
                    blue[1][0] = max(blue[1][0], 5 - j);
                if (blue[2][j])
                    blue[2][0] = max(blue[2][0], 5 - j);
                if (blue[3][j])
                    blue[3][0] = max(blue[3][0], 5 - j);
            }
        }
        else {
            blue[x][1] = 1;
            blue[x][0] = 4;
        }
    }
    else {
        blue[x][4 - blue[x][0]++] = 1;
        blue[x][4 - blue[x][0]++] = 1;
    }
    blueCheck();
}

void type3(int x, int y) {
    if (green[0][y] == 4)
    {
        for (int k = 0; k < 2; k++) {
            for (int i = 4; i >= 2; i--) {
                green[i][0] = green[i - 1][0];
                green[i][1] = green[i - 1][1];
                green[i][2] = green[i - 1][2];
                green[i][3] = green[i - 1][3];
            }
        }
        green[1][0] = 0;
        green[1][1] = 0;
        green[1][2] = 0;
        green[1][3] = 0;
        green[2][0] = 0;
        green[2][1] = 0;
        green[2][2] = 0;
        green[2][3] = 0;

        green[1][y] = 1;
        green[2][y] = 1;

        green[0][y] = 4;

        green[0][0] = 0;
        green[0][1] = 0;
        green[0][2] = 0;
        green[0][3] = 0;
        for(int j = 1; j <= 4; j++) {
            if (green[j][0]) green[0][0] = max(green[0][0], 5 - j);
            if (green[j][1]) green[0][1] = max(green[0][1], 5 - j);
            if (green[j][2]) green[0][2] = max(green[0][2], 5 - j);
            if (green[j][3]) green[0][3] = max(green[0][3], 5 - j);
        }
    }
    else if (green[0][y] == 3)
    {
        green[1][y] = 1;
        green[0][y] = 4;
        greenCheck();

        if (green[0][y] == 4)
        {
            for (int i = 4; i >= 2; i--)
            {
                green[i][0] = green[i - 1][0];
                green[i][1] = green[i - 1][1];
                green[i][2] = green[i - 1][2];
                green[i][3] = green[i - 1][3];
            }
            green[1][0] = 0;
            green[1][1] = 0;
            green[1][2] = 0;
            green[1][3] = 0;

            green[1][y] = 1;
            green[0][y] = 4;

            green[0][0] = 0;
            green[0][1] = 0;
            green[0][2] = 0;
            green[0][3] = 0;
            for (int j = 1; j <= 4; j++)
            {
                if (green[j][0])
                    green[0][0] = max(green[0][0], 5 - j);
                if (green[j][1])
                    green[0][1] = max(green[0][1], 5 - j);
                if (green[j][2])
                    green[0][2] = max(green[0][2], 5 - j);
                if (green[j][3])
                    green[0][3] = max(green[0][3], 5 - j);
            }
        }
        else
        {
            green[1][y] = 1;
            green[0][y] = 4;
        }
    }
    else {
        green[4 - green[0][y]++][y] = 1;
        green[4 - green[0][y]++][y] = 1;
    }
    greenCheck();

    if (blue[x][0] == 4 || blue[x + 1][0] == 4)
    {
        for (int i = 4; i >= 2; i--)
        {
            blue[0][i] = blue[0][i - 1];
            blue[1][i] = blue[1][i - 1];
            blue[2][i] = blue[2][i - 1];
            blue[3][i] = blue[3][i - 1];
        }
        blue[0][1] = 0;
        blue[1][1] = 0;
        blue[2][1] = 0;
        blue[3][1] = 0;

        blue[x][1] = 1;
        blue[x + 1][1] = 1;
        
        blue[x][0] = 4;
        blue[x + 1][0] = 4;

        blue[0][0] = 0;
        blue[0][1] = 0;
        blue[0][2] = 0;
        blue[0][3] = 0;
        for(int j = 1; j <= 4; j++) {
            if (blue[0][j]) blue[0][0] = max(blue[0][0], 5 - j);
            if (blue[1][j]) blue[1][0] = max(blue[1][0], 5 - j);
            if (blue[2][j]) blue[2][0] = max(blue[2][0], 5 - j);
            if (blue[3][j]) blue[3][0] = max(blue[3][0], 5 - j);
        }
    }
    else
    {
        int height = max(blue[x][0], blue[x + 1][0]);
        blue[x][4 - height] = 1;
        blue[x + 1][4 - height] = 1;
        blue[x][0] = height + 1;
        blue[x + 1][0] = height + 1;
    }
    blueCheck();
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
                type1(x, y);
                break;
            case 2:
                type2(x, y);
                break;
            case 3:
                type3(x, y);
                break;
        }
        cout << "#" << green[0][3] << "\n";
        cout << x << " " << y << "\n";
        print();
    }
    cout << score << "\n";
    int cnt = 0;
    for(int i = 1; i <= 4; i++) {
        for(int j = 0; j < 4; j++) {
            if (green[i][j]) cnt++;
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 1; j <= 4; j++) {
            if (blue[i][j]) cnt++;
        }
    }
    cout << cnt;
}