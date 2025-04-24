// 중위 표기식을 후위 표기식으로 변경하는 문제다.

#include <iostream>
#include <stack>
#include <string>
#define endl "\n"

using namespace std;

stack<char> cs;
string s, ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> s;
    ans = "";
	for(auto c : s) {
        if (c == '+' || c == '-') {
            while(!cs.empty()) {
                if (cs.top() == '(') break;
                ans += cs.top(); cs.pop();
            }
            cs.push(c);
        }
        else if (c == '*' || c == '/') {
            while(!cs.empty()) {
                if (cs.top() == '+' || cs.top() == '-' || cs.top() == '(') break;
                ans += cs.top(); cs.pop();
            }
            cs.push(c);
        } else if (c == '(') {
            cs.push(c);
        } else if (c == ')') {
            while(!cs.empty()) {
                if (cs.top() == '(') {
                    cs.pop();
                    break;
                }
                ans += cs.top(); cs.pop();
            }
        } else {
            ans += c;
        }
    }
    while(!cs.empty()) {
        ans += cs.top(); cs.pop();
    }
    cout << ans;
}