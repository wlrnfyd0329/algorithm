// 이 문제의 핵심은 target의 마지막 문자가 같을 때, 앞으로 가면서 검사하고 빼는 것이다.
// 왜냐면 빼고 나서 앞의 문자열과 합쳐져서 target 문자열이 나올 수 있기 때문이다.
// 또한 해당 문자열을 찾았을 때, substr같이 가지고 있는 문자열을 모두 복사하면 
// 갈이의 최대 100만라서 시간초과가 난다.
// 비교한 문자열만 빼줘야 한다. 그래야 길이의 최대가 36이기에 통과할 수 있다.

#include <iostream>
#include <algorithm>
#include <string>
#define endl "\n"

using namespace std;

string s, target, ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s >> target;
    ans = "";
    for(int i = 0; i < s.size(); i++) {
        ans += s[i];
        if (s[i] == target.back()) {
            bool isCorrect = true;
            // 1. temp를 만들고 뺀 것을 저장하면서 한번에 더해주기
            // string temp = "";
            // for(int j = target.size() - 1; j >= 0; j--) {
            //     if (ans.back() == target[j]) {
            //         temp += ans.back();
            //         ans.pop_back();
            //     }
            //     else {
            //         isCorrect = false;
            //         break;
            //     }
            // }
            // if (!isCorrect) {
            //     reverse(temp.begin(), temp.end());
            //     ans += temp;
            // }

            // 2. 폭탄 문자열을 찾았으면 그만큼 빼주기 -> 반복이 싫어서 substr을 옮기는 방식은 안된다.
            bool isCorrect = true;
            for(int j = 0; j < target.size(); j++) {
                if (ans[ans.size() - 1 - j] != target[target.size() - 1 - j]) {
                    isCorrect = false;
                    break;
                }
            }
            if (isCorrect) {
                for(int j = 0; j < target.size(); j++) {
                    ans.pop_back();
                }
            }
        }
    }

    cout << (ans.empty() ? "FRULA" : ans);
}   