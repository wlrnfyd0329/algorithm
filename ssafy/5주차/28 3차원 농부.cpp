#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define endl "\n"

using namespace std;

int N, M, c1, c2;
vector<int> cow;
vector<int> horse;

void solve() {
    int dist = 1'000'000'000;
    int cnt = 0;

    for(int i = 0; i < N; i++) {
        int lf = 1, rg = M - 2; // int lf = 1, rg = M - 1; // int lf = 0, rg = M - 2;
        while(lf <= rg) {
            int mid = (lf + rg) >> 1;

            if (horse[mid] <= cow[i]) { //if (horse[mid] < cow[i]) { 
                lf = mid + 1;
            }
            else {
                rg = mid - 1;
            }
        }

        int tdist = abs(cow[i] - horse[rg]);
        if (dist > tdist) {
            cnt = 1;
            dist = tdist;
        }
        else if (dist == tdist) {
            cnt++;
        }   
        
        tdist = abs(cow[i] - horse[lf]);
        if (dist > tdist) {
            cnt = 1;
            dist = tdist;
        }
        else if (dist == tdist) {
            cnt++;
        }   
        // int tdist = 0;
        // if (rg == M - 1) { // if (lf == 0) {
        //     tdist = abs(cow[i] - horse[rg]); // tdist = abs(cow[i] - horse[lf]);
        //     if (dist > tdist) {
        //         cnt = 1;
        //         dist = tdist;
        //     }
        //     else if (dist == tdist) {
        //         cnt++;
        //     }   
        // }
        // else {
        //     tdist = abs(cow[i] - horse[rg]);
        //     if (dist > tdist) {
        //         cnt = 1;
        //         dist = tdist;
        //     }
        //     else if (dist == tdist) {
        //         cnt++;
        //     }   

        //     tdist = abs(cow[i] - horse[lf]);
        //     if (dist > tdist) {
        //         cnt = 1;
        //         dist = tdist;
        //     }
        //     else if (dist == tdist) {
        //         cnt++;
        //     }   
        // } 
    }

    cout << abs(c1 - c2) + dist << " " << cnt << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> c1 >> c2;
        cow = vector<int> (N);
        horse = vector<int> (M);
        for(int i = 0; i < N; i++) {
            int num;
            cin >> num;
            cow[i] = num;
        }
        for(int i = 0; i < M; i++) {
            int num;
            cin >> num;
            horse[i] = num;
        }
        sort(cow.begin(), cow.end());
        sort(horse.begin(), horse.end());

        cout << "#" << tc << " ";
        solve();
    }
}