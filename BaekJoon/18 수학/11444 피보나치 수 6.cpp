// 피보나치 일반항을 2배를 곱해보며 새로운 점화식을 만들어도 된다.
// {{1, 1}, {1, 0}} x {F(n+1), F(n)} 행렬이 사실 피보나치 행렬이다.
// n번째 피보나치 수를 구하고 싶다면 위의 행렬을 n번 제곱하면 되는데
// 이는 빠른 제곱수 구하는 분할정복 느낌으로 해결할 수 있다.

#include <iostream>
#include <vector>

typedef long long ll;
using namespace std;

const int DIV = 1'000'000'007;
ll n;

struct Matrix {
	ll mat[2][2];
  
	Matrix operator*(const Matrix &r) const {
	  Matrix res = {{
			{0, 0},
			{0, 0}
		}};
	  for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
		  for(int k = 0; k < 2; k++) {
			res.mat[i][j] += mat[i][k] * r.mat[k][j] % DIV;
		  }
		  res.mat[i][j] %= DIV;
		}
	  }
	  return res;
	}
};

Matrix exponentiation(Matrix m, ll power) {
	if(power == 1) {
		return m;
	}
	Matrix half = exponentiation(m, power / 2);
	return power % 2 ? half * half * m : half * half;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> n;
	Matrix m = {{
		{1, 1},
		{1, 0}
	}};
	m = exponentiation(m, n);
	cout << m.mat[1][0];
}