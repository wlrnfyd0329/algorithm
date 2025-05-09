// 아래와 같이 이분탐색으로 해결할 수 있는 문제지만
// 투포인터를 이용해서 진행할 수도 있다. 최하단에 해당 코드를 첨부한다.

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n;
vector<int> arr;
long long ans_v;
vector<int> ans;

bool isCheck(int target, int a, int b) {
    if (target == a || target == b) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans_v = 5'000'000'000;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        arr.push_back(num);
    }

    sort(arr.begin(), arr.end());

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            long long val = arr[i] + arr[j];
            int idx = lower_bound(arr.begin(), arr.end(), -val) - arr.begin();
            if (idx == 0) {
                while(!isCheck(idx, i, j)) {
                    idx++; 
                }
            }
            else if (idx == arr.size()) {
                idx--;
                while(!isCheck(idx, i, j)) {
                    idx--; 
                }
            }
            else {
                int tidx = idx - 1;
                while(!isCheck(idx, i, j)) {
                    idx++;
                    if (idx == arr.size()) break;
                }
                while(!isCheck(tidx, i, j)) {
                    tidx--;
                    if (tidx < 0) break; 
                }

                if (idx == arr.size() || (tidx >= 0 && (abs(val + arr[idx]) > abs(val + arr[tidx])))) {
                    idx = tidx;
                }
            }

            val += arr[idx];
            
            if (ans_v > abs(val)) {
                ans_v = abs(val);
                ans = {arr[i], arr[j], arr[idx]};
            }
        }
    }


    sort(ans.begin(), ans.end());
    for(int i = 0; i < 3; i++) {
        cout << ans[i] << " ";
    }
}

// 투포인터 풀이
// mn = INF;
// for (int fst = 0; fst < n-2; fst++)
// {
//     // fst = i
//     int sec = fst + 1, thd = n - 1;
//     while (sec < thd)
//     {
//         ll sum = (ll)arr[fst] + arr[sec] + arr[thd];
//         if (abs(sum) < mn) 
//         {
//             mn = abs(sum);
//             answer[0] = arr[fst];
//             answer[1] = arr[sec];
//             answer[2] = arr[thd];
//         }

//         if (sum == 0)
//             break;
//         else if (sum > 0)
//             thd--;
//         else 
//             sec++;
//     }
// }