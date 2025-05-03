#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int N, M;
vector<int> arr;
bool table[2005][2005];

void func() {
    for(int i = 1; i <= N; i++) {
        int lf = i, rg = i;
        while(lf > 0 && rg <= N) {
            if (arr[lf] == arr[rg]) {
                table[lf][rg] = true;
                lf--;
                rg++;
            }
            else {
                break;
            }
        }
    }

    for(int i = 1; i < N; i++) {
        int lf = i, rg = i + 1;
        while(lf > 0 && rg <= N) {
            if (arr[lf] == arr[rg]) {
                table[lf][rg] = true;
                lf--;
                rg++;
            }
            else {
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    arr = vector<int> (N + 1);
    for(int i = 1; i <= N; i++) {
        int num; cin >> num;
        arr[i] = num;
    }
    func();
    cin >> M;
    for(int i = 0; i < M; i++) {
        int s, e;
        cin >> s >> e;
        cout << table[s][e] << endl;
    }

}