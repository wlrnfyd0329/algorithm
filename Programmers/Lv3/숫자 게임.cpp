// 투포인터

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int n = B.size();
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    int answer = 0;
    int stA = 0;
    int stB = 0;
    while(stB < n) {
        if (A[stA] < B[stB]) {
            stA++;
            stB++;
            answer++;
        }
        else {
            stB++;
        }
    }
    return answer;
}