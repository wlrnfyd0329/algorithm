// lis 알고리즘을 사용해야 한다
// 이분탐색을 통해서 찾긴하지만 배열에 직접 수를 업데이트 하는 것보다
// vector에 담아서 최신 것을 보는 것이 문제 풀이에 핵심이다
// 또한 들어오는 숫자마다 lis에 해당되는 인덱스도 저장해야 한다

#include <vector>
#include <iostream>
#define endl "\n"

using namespace std;

vector<vector<int>> mountain; // lis에 들어오는 순서대로 그대로 저장
vector<int> lis_record; // lis에 해당하는 인덱스를 저장

int binary_search(int target) {
    int lf = 0, rg = mountain.size() - 1;
    while (lf <= rg) {
        int mid = (lf + rg) >> 1;
        if (mountain[mid].back() < target) {
            lf = mid + 1;
        }
        else {
            rg = mid - 1;
        }
    }

    return lf;
}

void create() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int h; cin >> h;
        int idx = binary_search(h);
        if (idx == mountain.size()) {
            lis_record.push_back(idx);
            mountain.push_back({h});
        }
        else {
            lis_record.push_back(idx);
            mountain[idx].push_back(h);
        }
    }
}

void insert() {
    int h; cin >> h;
    int idx = binary_search(h);
    if (idx == mountain.size()) {
        lis_record.push_back(idx);
        mountain.push_back({h});
    }
    else {
        lis_record.push_back(idx);
        mountain[idx].push_back(h);
    }
}

void remove() {
    mountain[lis_record.back()].pop_back();
    if (mountain[lis_record.back()].empty()) mountain.pop_back();
    lis_record.pop_back();
}

void move() {
    int m_index; cin >> m_index;
    cout << (lis_record[m_index - 1] + mountain.size()) * 1'000'000LL + mountain.back().front() << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int Q; cin >> Q;

    for (int i = 0; i < Q; i++) {
        int cmd; cin >> cmd;
        switch (cmd)
        {
        case 100:
            create();
            break;
        case 200:
            insert();
            break;
        case 300:
            remove();
            break;
        case 400:
            move();
            break;
        }
    }
}
