#include <iostream>
#include <set>

using namespace std;

int t, k;


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    multiset<int> ms;
    cin >> t;
    for (int i = 0; i < t; i++) {
        ms.clear();
        cin >> k;
        for (int j = 0; j < k; j++) {
            char c;
            int n;
            cin >> c >> n;
            if (c == 'I') {
                ms.insert(n);
            }
            else if (c == 'D') {
                if (ms.size() == 0) continue;
                if (n == 1) {
                    ms.erase(--ms.end());
                }
                else {
                    ms.erase(ms.begin());
                }
            }
        }
        if(ms.size() == 0) {
            cout << "EMPTY\n";
        }
        else {
            cout << *--ms.end() << " " << *ms.begin() << "\n";
        }
    }
}