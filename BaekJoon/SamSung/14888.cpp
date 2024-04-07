#include <iostream>
#include <algorithm>

using namespace std;

int n, num[12], oper[12], sum, mx = -1000000000, mn = 1000000000;
 
int cul(int a, int b, int k) {
    if(k == 0) return a + b;
    else if(k == 1) return a - b;
    else if(k == 2) return a * b;
    else return a / b;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> num[i];
    }
    for(int i = 0; i < 4; i++) {
        int temp;
        cin >> temp;
        for(int j = sum; j < sum + temp; j++) {
            oper[j] = i;
        }
        sum += temp;
    }
    do{
        sum = num[0];
        for(int i = 0; i < n -1; i++) {
            sum = cul(sum, num[i+1], oper[i]);
        }
        if(mx < sum) mx = sum;
        if(mn > sum) mn = sum;
    }while(next_permutation(oper, oper + n - 1));
    cout << mx << "\n" << mn;
}

/*
백트래킹을 사용해야 하는 문제다.
algorithm 헤더의
next_permutation의 사용법을 알면 굉장히 쉽게 풀 수 있다.

현재가 1 2 3이면 next_permutation을 실행한 후 1 3 2가 되고, 
1 3 2에서 next_permutation을 실행하면 2 1 3이 됩니다. 
만약 현재의 수열이 사전 순으로 생각했을 때 제일 마지막이어서 다음 수열이 존재하지 않는다면 false를 반환합니다. 
그렇기 때문에 지금처럼 do-while 문으로 작성하면 코드가 깔끔하게 떨어집니다. 만약 중복된 수가 있다고 해도 사전 순의 결과를 잘 돌려줍니다.
예를 들어 1 1 2에서 시작했다면 1 2 1, 2 1 1로 바뀌게 됩니다.

함수의 이름에서 볼 수 있듯 이 함수를 가지고 순열을 잘 처리할 수 있는데 만약 조합이 필요하다면 어떻게 해야할지 고민해봅시다. 
예를 들어 1 2 3 4에서 수 2개를 순서 없이 뽑는 모든 경우를 출력하는 문제와 같은 상황입니다. 
그럴 때에도 이 함수를 이용하면 되는데 오른쪽의 코드를 확인해보겠습니다. 
바로 0과 1을 이용해 next_permutation을 돌리는 방법으로 해결하면 됩니다. 
4개에서 2개를 뽑는게 아니라 5개에서 3개를 뽑는 문제라면 배열 a를 {0, 0, 0, 1, 1}로 두면 되겠습니다
*/