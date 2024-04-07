#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, num[25], idx[25], arr[25][25], mn = 2100000000, sum1, sum2;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 2; i < n/2; i++) {
        idx[i] = 1;
    }
    for(int i = n/2; i < n; i++) {
        num[i] = 1;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    do {
        vector<int> v1, v2;
        int result;
        sum1 = 0;
        sum2 = 0;
        for(int i = 0; i < n; i++) {
            if(num[i] == 0) {
                v1.push_back(i + 1);
            }
            else {
                v2.push_back(i + 1);
            }
        }
        do {
            int temp[2];
            int temp_num = 0;
            for(int j = 0; j < n/2; j++) {
                if(idx[j] == 0) {
                    temp[temp_num++] = j;
                }
            }
            sum1 += arr[v1[temp[0]]][v1[temp[1]]] + arr[v1[temp[1]]][v1[temp[0]]];
            sum2 += arr[v2[temp[0]]][v2[temp[1]]] + arr[v2[temp[1]]][v2[temp[0]]];
        } while(next_permutation(idx, idx + n/2));
        if (sum1 > sum2)
            result = sum1 - sum2;
        else
            result = sum2 - sum1;
        if (mn > result)
            mn = result;
    } while(next_permutation(num, num + n - 1));
    cout << mn;
}

/*
next_permutation으로 팀을 짝 짓고 vector에 1팀 2팀을 나눠서 넣고
팀에서 2개씩 조합으로 뽑은 것을 더하는 방식으로 진행한다.
*/