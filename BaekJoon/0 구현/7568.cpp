#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

struct Info {
    int weight;
    int height;
    int rank;
};

vector<Info> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        Info info;
        info.weight = x;
        info.height = y;
        info.rank = 1;
        for(int j = 0; j < i; j++) {
            if (v[j].weight < info.weight && v[j].height < info.height) {
                v[j].rank++;
            }
            else if (v[j].weight > info.weight && v[j].height > info.height) {
                info.rank++;
            }
        }
        v.push_back(info);
    }

    for(auto k : v) {
        cout << k.rank << " ";
    }
}