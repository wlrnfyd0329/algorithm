#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int TC;
    cin >> TC;
    for(int tc = 1; tc <= TC; tc++) {
        
        int n, m, l;
        cin >> n >> m >> l;
        vector<int> v;
        for(int i = 0; i < n; i++) {
            int num;
            cin >> num;
            v.push_back(num);
        }

        for(int i = 0; i < m; i++) {
            char cmd;
            int a, b;
            cin >> cmd;
            switch (cmd) {
                case 'I':
                    cin >> a >> b;
                    v.insert(v.begin() + a, b);
                    break;
                case 'D':
                    cin >> a;
                    v.erase(v.begin() + a);
                    break;
                case 'C':
                    cin >> a >> b;
                    v[a] = b;
                    break;
            }
        }

        cout << "#" << tc << " " << v[l] << "\n";
    }
}