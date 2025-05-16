// CCW 알고리즘 활용 문제

#include <iostream>
#include <algorithm>
#include <vector>
#define X first
#define Y second
#define endl "\n"

typedef long long ll;
using namespace std;

struct Line
{
    pair<ll, ll> p1;
    pair<ll, ll> p2;

} L1, L2;

int ccw(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3) {
    ll s = p1.X * p2.Y + p2.X * p3.Y + p3.X * p1.Y;
    s -= (p1.Y * p2.X + p2.Y * p3.X + p3.Y * p1.X);

    if (s > 0) return 1;
    else if (s == 0) return 0;
    else return -1; 
}

bool isIntersect(Line l1, Line l2) {

    pair<ll, ll> p1 = l1.p1;
    pair<ll, ll> p2 = l1.p2;
    pair<ll, ll> p3 = l2.p1;
    pair<ll, ll> p4 = l2.p2;

    int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4); // l1 기준
    int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2); // l2 기준

    // 두 직선이 일직선 상에 존재
    if (p1p2 == 0 && p3p4 == 0) {
    	// 비교를 일반화하기 위한 점 위치 변경
        if (p1 > p2) swap(p2, p1);
        if (p3 > p4) swap(p3, p4);
        
        return p3 <= p2 && p1 <= p4; // 두 선분이 포개어져 있는지 확인
    }
    
    return p1p2 <= 0 && p3p4 <= 0;
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> L1.p1.X >> L1.p1.Y >> L1.p2.X >> L1.p2.Y;
    cin >> L2.p1.X >> L2.p1.Y >> L2.p2.X >> L2.p2.Y;

    cout << isIntersect(L1, L2);
}