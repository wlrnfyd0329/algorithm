#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"

using namespace std;

int n, m;
int arr[100'005];

bool bs(int num) {
    int lf = 0, rg = n - 1;
    while(lf <= rg) {
        int mid = (lf + rg) >> 1;
        if (arr[mid] == num) {
            return true;
        }
        else if (arr[mid] > num) {
            rg = mid - 1;
        }
        else {
            lf = mid + 1;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    cin >> m;
    for(int i = 0; i < m; i++) {
        int num; 
        cin >> num;
        cout << bs(num) << endl;
        //cout << binary_search(arr, arr + n, num) << endl;
    }

}