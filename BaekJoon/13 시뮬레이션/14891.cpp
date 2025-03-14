#include <iostream>
#include <deque>

using namespace std;

int k, n, dir;
deque<int> DQ[4];

void func(int a, int d) {
    int temp;
    if(d == 1) {
        temp = DQ[a].back();
        DQ[a].pop_back();
        DQ[a].push_front(temp);
    }
    else {
        temp = DQ[a].front();
        DQ[a].pop_front();
        DQ[a].push_back(temp);
    }
}

int check() {
    int temp = 0;
    if (DQ[0][2] != DQ[1][6])
    {
        temp += 1;
    }
    if (DQ[1][2] != DQ[2][6])
    {
        temp += 2;
    }
    if (DQ[2][2] != DQ[3][6])
    {
        temp += 4;
    }
    return temp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 0; i < 4; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < 8; j++) {
            DQ[i].push_back(s[j] - '0');
        }
    }
    cin >> k;
    for(int i = 0; i < k; i++) {
        cin >> n >> dir;
        int temp = check();
        if(n == 1) {
            if(temp == 1 || temp == 5) {
                func(0, dir);
                func(1, -dir);
            }
            else if(temp == 3) {
                func(0, dir);
                func(1, -dir);
                func(2, dir);
            }
            else if(temp == 7) {
                func(0, dir);
                func(1, -dir);
                func(2, dir);
                func(3, -dir);
            }
            else {
                func(0, dir);
            }
        }
        else if(n == 2) {
            if (temp == 1 || temp == 5)
            {
                func(1, dir);
                func(0, -dir);
            }
            else if (temp == 2)
            {
                func(1, dir);
                func(2, -dir);
            }
            else if (temp == 3)
            {
                func(1, dir);
                func(0, -dir);
                func(2, -dir);
            }
            else if (temp == 6)
            {
                func(1, dir);
                func(2, -dir);
                func(3, dir);
            }
            else if (temp == 7)
            {
                func(0, -dir);
                func(1, dir);
                func(2, -dir);
                func(3, dir);
            }
            else {
                func(1, dir);
            }
        }
        else if(n == 3) {
            if (temp == 4 || temp == 5)
            {
                func(2, dir);
                func(3, -dir);
            }
            else if (temp == 2)
            {
                func(2, dir);
                func(1, -dir);
            }
            else if (temp == 3)
            {
                func(2, dir);
                func(1, -dir);
                func(0, dir);
            }
            else if (temp == 6)
            {
                func(2, dir);
                func(3, -dir);
                func(1, -dir);
            }
            else if (temp == 7)
            {
                func(0, dir);
                func(1, -dir);
                func(2, dir);
                func(3, -dir);
            }
            else {
                func(2, dir);
            }
        }
        else {
            if (temp == 4 || temp == 5)
            {
                func(3, dir);
                func(2, -dir);
            }
            else if (temp == 6)
            {
                func(3, dir);
                func(2, -dir);
                func(1, dir);
            }
            else if (temp == 7)
            {
                func(3, dir);
                func(2, -dir);
                func(1, dir);
                func(0, -dir);
            }
            else {
                func(3, dir);
            }
        }
    }
    int result = 0;
    if(DQ[0][0]) result += 1;
    if(DQ[1][0]) result += 2;
    if(DQ[2][0]) result += 4;
    if(DQ[3][0]) result += 8;
    cout << result;
}

/*
그냥 구현 노가다 문제인듯함
*/