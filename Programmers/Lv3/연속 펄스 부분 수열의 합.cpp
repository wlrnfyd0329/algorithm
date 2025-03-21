// 중요한 건 연속합에서 최소의 연속합을 되면 남은 값이 최대가 된다는 것이다.

#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long solution(vector<int> sequence) {
    long long ans = 0;
    int n = sequence.size();
    long long s1 = 0, s2 = 0;
    long long s1_min = 0, s2_min = 0;
    int pulse = 1;
    
    for(int i = 0; i < n; i++) {
        s1 += sequence[i] * pulse;
        s2 += sequence[i] * -pulse;
        
        ans = max(ans, max(s1-s1_min, s2-s2_min));
        
        s1_min = min(s1, s1_min);
        s2_min = min(s2, s2_min);
        
        pulse *= -1;
    }
    
    return ans;
}