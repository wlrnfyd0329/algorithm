// lis 알고리즘을 사용해야 한다
// 이분탐색을 통해서 찾는데, lower_bound를 활용한다
// 또한, 배열에 직접 수를 업데이트 하는 것보다
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
    // 이 방식으로 lis를 진행하게 되면 mountain.back()은 증가하는 수열을 구하기 위해 뒤죽박죽 섞인 상태가 될 것이다.
    // 10 20 50 5 -> 10 -> 10 20 -> 10 20 50 -> 5 20 50 이렇게 되어있을 텐데, 이는 증가하는 수열은 아니다. 최대 길이만 구할 수 있을 뿐
    // 따라서 각 증가하는 수열을 구하고 싶다면 index로 뒤로 찾아가야 한다.
    // 이 문제는 마지막의 front()를 구하고 있는데, 이것은 말이 되는데, 어차피 마지막 값은 vector에 쌓이는 값이 점점 더 작아지기 때문에 값이 쌓이기 때문에
    // 해당 인덱스의 가장 큰 값은 front()에 있을 것이다.
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
