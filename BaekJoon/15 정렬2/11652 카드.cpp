#include <iostream>
#include <algorithm>

using namespace std;

int num, cnt;
int mxcnt = 0;
long long mxval = -(1LL << 62) - 1;
long long l[100005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> l[i];
    }

    sort(l, l + num);
    for(int i = 0; i < num; i++) {
        if (i == 0 || l[i - 1] == l[i]) cnt++;
        else {
            if (mxcnt < cnt)
            {
                mxcnt = cnt;
                mxval = l[i-1];
            }
            cnt = 1;
        }
    }
    if(mxcnt < cnt) mxval = l[num-1];
    cout << mxval;
}