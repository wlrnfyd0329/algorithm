#include <iostream>
#include <stack>

using namespace std;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int arr[1005];
    stack<int> s;
    cin >> n;
    int order = 1, index = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    while(true) {
        if (index == n) {
            break;
        }
        if (arr[index] == order) {
            order++;
            index++;
        }
        else {
            if (!s.empty() && s.top() == order) {
                order++;
                s.pop();
            }
            else {
                s.push(arr[index]);
                index++;
            }
        }
    }

    while(!s.empty()) {
        if (s.top() == order) {
            order++;
            s.pop();
        }
        else {
            cout << "Sad";
            return 0;
        }
    }

    cout << "Nice";
}