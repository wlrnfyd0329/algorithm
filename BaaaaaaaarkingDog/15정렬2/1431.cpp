#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int num;
string s[50];

bool cmp(string &a, string &b)
{
    if (a.length() == b.length())
    {
        int tmp1 = 0;
        int tmp2 = 0;
        for (auto k : a)
        {
            int tmp = k - '0';
            if (tmp >= 0 && tmp < 10)
            {
                tmp1 += tmp;
            }
        }
        for (auto k : b)
        {
            int tmp = k - '0';
            if (tmp >= 0 && tmp < 10)
            {
                tmp2 += tmp;
            }
        }
        if (tmp1 == tmp2)
            return a < b;
        return tmp1 < tmp2;
    }
    return a.length() < b.length();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> s[i];
    }


    sort(s, s + num, cmp);
    for (int i = 0; i < num; i++) {
        cout << s[i] << "\n";
    }
}
