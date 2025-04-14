#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, index = 0;
    vector<pair<int, int>> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp; 
        cin >> tmp;
        v.push_back({tmp, i + 1});
    }
    while(!v.empty()) {
        int vindex;
        if (v[index].first > 0) {
            vindex = v[index].first - 1;
        }
        else {
            vindex = v[index].first;
        }
        int origin = v[index].second;
        v.erase(v.begin() + index);
        index += vindex;
        if (v.empty()) {
            cout << origin;
            break;
        }
        while(index < 0 || index >= (int)v.size()) {
            if(index >= (int)v.size()) {
                index -= v.size();
            }
            else if (index < 0) {
                index += v.size();
            }
        }
        cout << origin << " ";
    }
}

// 이 코드는 인덱스를 옮기는 방식을 사용했지만
// deque를 사용해서 요소를 push, pop 하는 방식으로 진행하는 것이 더 깔끔해 보인다