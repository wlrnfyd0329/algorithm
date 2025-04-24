// 행렬 제곱 연산 구현 문제
// 빠른 거듭 제곱 알고리즘도 사용해야 한다

#include <iostream>
#include <vector>
#define endl "\n"

typedef long long ll;
using namespace std;

struct Matrix {
    int n;
    vector<vector<ll>> mat;

    Matrix(int n) : n(n) {
        mat = vector<vector<ll>> (n, vector<ll> (n, 0));
    }

    Matrix operator*(const Matrix &o) const {
        Matrix ans(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    ans.mat[i][j] += mat[i][k] * o.mat[k][j] % 1000;
                    ans.mat[i][j] %= 1000;
                }
            }
        }
        return ans;
    }
};

Matrix pow(Matrix &m, ll num) {
    if (num == 1) return m;
    Matrix half = pow(m, num / 2);
    return (num % 2) ? half * half * m : half * half;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    ll B;
    cin >> N >> B;
    Matrix m(N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> m.mat[i][j];
        }
    }
    m = pow(m, B);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << m.mat[i][j] % 1000 << " ";
        }
        cout << endl;
    }
}