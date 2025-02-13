// LCA2 모르면 틀려야 함....

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, result;
int depth[100001];
int parent[100001][18];
vector<int> tree[100001];

void init()
{
    result = 0;
    fill(depth, depth + 100000, 0);
    for (int i = 1; i <= n; i++)
    {
        tree[i].clear();
    }
}

void lca2_dp() // 각 노드의 2^k번째 부모를 저장함 dp
{
    for (int k = 1; k < 18; k++)
    {
        for (int idx = 1; idx <= n; idx++)
        { // 1부터 하는건 초기화의 목적도 있음
            parent[idx][k] = parent[parent[idx][k - 1]][k - 1];
        }
    }
}

int lca(int x, int y)
{ // x와 y 사이의 거리를 잰다.
    int cnt = 0;
    if (depth[x] > depth[y])
    { // y를 더 깊게 생각하기 위해서 x가 더 깊다면 바꿔준다.
        swap(x, y);
    }
    if (parent[y][0] == x)
    { // 문제에 맞게 y가 더 깊기에 y의 조상이 x라면 거리가 1
        return 1;
    }
    for (int k = 17; k >= 0; k--)
    {
        // lca 알고리즘의 중요한 부분이다
        // 가장 먼 조상부터 탐색을 시작하는데 x보다 얕아지지 않도록 해야 한다
        // 즉 x보다 깊은 조상 중에 제일 얕은 값을 찾는다

        // depth를 맞추는 1번째 방법
        if (depth[y] - depth[x] >= (1 << k))
        {
            // 깊이 차이를 미리 계산하고 k가 2의 제곱수니까 그전까지는 무조건 벗어남
            // 따라서 계산해서 가장 가까운 제곱수를 찾기 위해서 역순으로 진행함

            y = parent[y][k]; // 찾았으면 y를 바꿔줌
            // 이것을 반복하면 depth가 같아짐
            // 왜냐면 y를 바꿔주고 깊이 차이를 비교한 후 i를 바꾸기 때문이다
            // 이때, i를 왜 처음부터 하지 않는가를 생각해보면
            // 깊이는 계속 작아지기에 전의 i보다 작아지는 것이 확실하기 때문

            cnt += (1 << k); // 올라간 만큼 개수를 더해준다
        }

        // depth를 맞추는 2번째 방법
        // if (depth[x] <= depth[parent[y][k]]) {
        //     // 이것은 역순으로 비교하면서 y가 x의 깊이 최대한 가까워 질때까지
        //     // 계속 y를 업데이트 해준다
        //     y = parent[y][k];
        // }
    }

    // depth가 같다면 부모를 확인해서 같다면 lca를 찾은 것이고 다르다면
    // 공통 부모를 찾을 때까지 부모를 바꿔가며 확인한다

    // 부모가 같을 때까지 찾는다
    if (parent[x][0] != parent[y][0])
    {
        // 깊이가 같은데 부모가 다르다면 공통 부모가 아니기에
        // 공통 부모를 찾을 때가지 부모를 올리면서 확인한다
        for (int k = 17; k >= 0; k--)
        {
            // if (parent[x][k] == parent[y][k]) break;
            // 위에처럼 break 하면 역순이기에 바로 공통 조상이 되어서 멈춘다
            // 물론 다른 순간이 나와도 그것의 부모로 x, y를 넣어주기에 다시
            // k값이 줄어들면서 정확한 최소 공통 부모가 나온다
            // 따라서 아래처럼 부모가 다른 순간에 멈춰서 x, y를 넣어줘야
            // 아래 부모가 같은지 확인할 때, 같다고 나온다
            if (parent[x][k] != parent[y][k])
            {
                x = parent[x][k];
                y = parent[y][k];
                cnt += 2 * (1 << k);
            }
        }

        // 위에는 위에서부터 내려가면서 찾았다
        // 한번 아래부터 올라가면서 부모가 같을 때, 그냥 리턴하는 형식은 어떨까?
        // 2의 제곱수로 올라가기에 같은 부모를 찾았을 때, 최소 공통 부모가 아닐 수 있다.
        // 따라서 역순으로 내려가면서 부모가 틀린 순간을 찾는 것이 정확하다
        // for (int k = 0; k < 18; k++) {
        //     if (parent[x][k] == parent[y][k]) {
        //         return cnt + 2 * (1 << k);
        //     }
        //     x = parent[x][k];
        //     y = parent[y][k];
        // }
    }

    if (parent[x][0] == parent[y][0])
    {
        // 부모가 같다면 문제에서 이동시 2번 걸리기 때문에 2를 더하고 리턴
        return cnt + 2;
    }
}

long long bfs() // long long으로 해줘야 한다. 10만개의 노드를 깊게 왔다 갔다하면 21억 초과함
{
    long long result = 0;
    int pre, cur; // bfs를 진행하면서 이전의 값이 기억해야지 거쳐간 노드를 셀 수 있음
    queue<int> q;
    q.push(1);
    pre = 1;
    while (!q.empty())
    {
        int pnt = q.front();
        q.pop();
        for (auto k : tree[pnt])
        {
            cur = k;
            q.push(k);
            depth[k] = depth[pnt] + 1;
            result += lca(pre, cur);
            pre = cur;
        }
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> n;
        init();
        int pnt;
        parent[1][0] = 0; // 루트 노드의 조상은 0
        depth[1] = 0;     // 루트 노드의 깊이는 0
        // 사실 0으로 초기화 해서 해줄 필요는 없지만 명시해주는 느낌
        for (int i = 2; i <= n; i++)
        {
            cin >> pnt; // i 가 노드의 번호고 pnt가 그 부모
            depth[i] = depth[pnt] + 1;
            parent[i][0] = pnt;
            tree[pnt].push_back(i);
        }
        lca2_dp();
        cout << "#" << tc << " " << bfs() << "\n";
    }
}