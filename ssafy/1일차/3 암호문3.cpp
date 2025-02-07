#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int TC = 10;
    for(int tc = 1; tc <= TC; tc++) {
        vector<int> v;
        int n, m;
        cin >> n;
        for(int i = 0; i < n; i++) {
            int num;
            cin >> num;
            v.push_back(num);
        }
        cin >> m;
        for(int j = 0; j < m; j++) {
            char command;
            int x, y, s;
            cin >> command;
            switch (command)
            {
            case 'I':
                cin >> x >> y;
                for(int i = 0; i < y; i++) {
                    cin >> s;
                    v.insert(v.begin() + x++, s);
                }
                break;
            case 'D':
                cin >> x >> y;
                v.erase(v.begin() + x, v.begin() + x + y);
                // for(int i = 0; i < y; i++) {
                //     v.erase(v.begin() + x);
                // }
                break;
            case 'A':
                cin >> y;
                for(int i = 0; i < y; i++) {
                    cin >> s;
                    v.push_back(s);
                }
                break;
            }
        }

        cout << "#" << tc << " ";
        for(int i = 0; i < 10; i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }
}