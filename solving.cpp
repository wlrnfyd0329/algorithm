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
            string temp = "";
            bool isCorrect = true;
            for(int j = target.size() - 1; j >= 0; j--) {
                if (ans.back() == target[j]) {
                    temp += ans.back();
                    ans.pop_back();
                }
                else {
                    isCorrect = false;
                    break;
                }
            }
            if (!isCorrect) {
                reverse(temp.begin(), temp.end());
                ans += temp;
            }
        }
    }

    cout << (ans.empty() ? "FRULA" : ans);
}   