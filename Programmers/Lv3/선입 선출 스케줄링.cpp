#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int cores_cnt;
vector<pair<int, int>> v;

int bs(int n, vector<int> &c) {
    long long cnt = 0; // 이 부분에서 2.5억으로 나눈 값이 많아지면 오버플로우가 나서 정답이 틀렸다.
    int lf = 0, rg = 250'000'000;
    while(lf <= rg) {
        cnt = 0;
        int mid = (lf + rg) >> 1;
        for(int i = 0; i < cores_cnt; i++) {
            cnt += (mid / c[i]) + 1;
        }
        if (cnt < n) {
            lf = mid + 1;
        }
        else {
            rg = mid - 1;
        }
    }
    return rg;
}

int solution(int n, vector<int> cores) {
    cores_cnt = cores.size();
    
    if (n <= cores_cnt) {
        return n;
    }
    else {
        int time = bs(n, cores);
        for(int i = 0; i < cores_cnt; i++) {
            n -= (time / cores[i]) + 1;
        }
        while(n) {
            time++;
            for (int i = 0; i < cores_cnt; i++) {
                if (time % cores[i] == 0) n--;
                if (n == 0) {
                    return i + 1;
                }
            }

        }
    }
}