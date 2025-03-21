#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int ans = 0;
    int cnt = stations.size();
    int power = 2 * w + 1;
    int st = 1, en = stations[0] - w;
    if (en > st) {
        if ((en - st) % power == 0) ans += (en - st) / power;
        else ans += (en - st) / power + 1;
    }
    
    for(int i = 1; i < cnt; i++) {
        st = stations[i - 1] + w + 1;
        en = stations[i] - w;
        if (en > st) {
            if ((en - st) % power == 0) ans += (en - st) / power;
            else ans += (en - st) / power + 1;
        }
    }
    
    st = stations[cnt - 1] + w;
    en = n;
    if (en > st) {
        if ((en - st) % power == 0) ans += (en - st) / power;
        else ans += (en - st) / power + 1;
    }
    
    
    return ans;
}