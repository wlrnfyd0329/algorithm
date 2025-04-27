// vector<vector<int>> 에 lis 값을 계속 push_back하는 방식으로 lis를 진행하게 되면 lis는 증가하는 수열을 구하기 위해 뒤죽박죽 섞인 상태가 될 것이다.
// 10 20 50 5 -> 10 -> 10 20 -> 10 20 50 -> 5 20 50 이렇게 되어있을 텐데, 이는 증가하는 수열은 아니다. 최대 길이만 구할 수 있을 뿐
// 따라서 각 증가하는 수열을 구하고 싶다면 index로 뒤로 찾아가야 한다. 뒤에서 부터 찾고 다시 거꾸로 출력해야 한다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n;
vector<int> arr;
vector<int> idx;
vector<int> lis;

int lower_bound(int target) {
    int lf = 0, rg = lis.size() - 1;
    while(lf <= rg) {
        int mid = (lf + rg) >> 1;
        if (lis[mid] < target) {
            lf = mid + 1;
        }
        else {
            rg = mid - 1;
        }
    }
    return lf;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        int index = lower_bound(num);
        arr.push_back(num);
        idx.push_back(index);
        if (index == lis.size()) {
            lis.push_back(num);
        }
        else {
            lis[index] = num;
        }
    }

    int index = lis.size();
    vector<int> ans;
    cout << index-- << endl;
    for(int i = idx.size() - 1; i >= 0; i--) {
        if (idx[i] == index) {
            ans.push_back(arr[i]);
            if (--index < 0) break;
        }
    }
    for(int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }
}