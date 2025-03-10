// 라빈카프 알고리즘
// 원래 해시값이 같아도 중복될 수 있기 때문에 값을 비교해야 하는데
// 그냥 같다고 판단하기 그래도 해시 값 3개를 비교해서 진행
// 아주 낮은 확률로 틀림

#include <iostream>
#include <string>
#define endl "\n"

using namespace std;

const int EXPONENT1 = 31;
const int EXPONENT2 = 37;
const int EXPONENT3 = 41;

int getCount(const string &a, const string &b) {
    int ans = 0;
    
    int stringHash1 = 0;
    int patternHash1 = 0;

    int stringHash2 = 0;
    int patternHash2 = 0;

    int stringHash3 = 0;
    int patternHash3 = 0;

    int power1 = 1;
    int power2 = 1;
    int power3 = 1;

    for(int i = 0; i <= a.size() - b.size(); i++) {
        if (i == 0) {
            for(int j = b.size() - 1; j >= 0; j--) {
                stringHash1 += a[j] * power1;
                patternHash1 += b[j] * power1;

                stringHash2 += a[j] * power2;
                patternHash2 += b[j] * power2;

                stringHash3 += a[j] * power3;
                patternHash3 += b[j] * power3;

                if (j > 0) {
                    power1 *= EXPONENT1;
                    power2 *= EXPONENT2;
                    power3 *= EXPONENT3;
                }
            }
        }
        else {
            stringHash1 = EXPONENT1 * (stringHash1 - a[i - 1] * power1) + a[i + b.size() - 1];
            stringHash2 = EXPONENT2 * (stringHash2 - a[i - 1] * power2) + a[i + b.size() - 1];
            stringHash3 = EXPONENT3 * (stringHash3 - a[i - 1] * power3) + a[i + b.size() - 1];
        }

        if (stringHash1 == patternHash1 && stringHash2 == patternHash2 && stringHash3 && patternHash3) {
            ans++;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; 
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        string B, word;
        cin >> B >> word;
        
        cout << "#" << tc << " " << getCount(B, word) << endl;
    }
}