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
