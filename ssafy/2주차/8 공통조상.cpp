#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int depth[10001];
int parent[10001];
int sub[10001];

vector<int> tree[10001];

void print_parent(int v) { // 순회 한번에 모든 부모 구하기
    cout << "parent : ";
    for(int i = 1; i <= v; i++) {
        cout << parent[i] << " ";
    }
    cout << "\n";
}

void print_depth(int v) { // 순회 한번에 모든 깊이 구하기
    cout << "depth : ";
    for(int i = 1; i <= v; i++) {
        cout << depth[i] << " ";
    }
    cout << "\n";
}

void print_sub(int v) { // 순회 한번에 모든 서브트리 크기 구하기 
    cout << "sub : ";
    for(int i = 1; i <= v; i++) {
        cout << sub[i] << " ";
    }
    cout << "\n";
}

void cycle(int index) { // 순회 하기
    for(auto k : tree[index]) {
        parent[k] = index;
        depth[k] = depth[index] + 1;
        cycle(k);
        sub[index] += sub[k];
    }
    sub[index]++;
}

void print_result(int n1, int n2) {
    int arr[10001] = {};
    while(n1 != 1) {
        arr[parent[n1]] = 1;
        n1 = parent[n1];
    }
    while(true) {
        if(arr[parent[n2]]) {
            cout << parent[n2] << " " << sub[parent[n2]] << "\n";
            break;
        }
        n2 = parent[n2];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int v, e, n1, n2;
        cin >> v >> e >> n1 >> n2; 
        fill(sub, sub + 10001, 0);
        for(int i = 1; i <= v; i++) {
            tree[i].clear();
        }
        for(int i = 0; i < e; i++) {
            int p, s;
            cin >> p >> s;
            tree[p].push_back(s);
        }

        cycle(1);
        // print_depth(v);
        // print_parent(v);
        // print_sub(v);

        cout << "#" << tc << " ";
        print_result(n1, n2);
    }
}