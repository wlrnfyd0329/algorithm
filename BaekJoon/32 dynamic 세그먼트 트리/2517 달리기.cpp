// 정수 값이 너무 크기 때문에 그냥 다이나믹 세그먼트 트리로 해보자
// 기본 1 ~ 10억으로 노드를 정하니까 확실히 오래 걸린다. 깊이가 30정도 나온다.
// 그냥 세그먼트로 하면 500,000이기에 깊이가 19정도로 거의 2/3의 시간으로 해결할 수 있다.

#include <iostream>
#include <vector>
#define MAX_V 1'000'000'000
#define endl "\n"

using namespace std;

struct Node {
    Node *left, *right;
    int value;
    Node() {
        left = right = nullptr;
        value = 0;
    }
} *root = new Node();

void update(Node *node, int start, int end, int index) {
    if (start == end) {
        node->value++;
        return;
    }
    int mid = (start + end) >> 1;
    if (index <= mid) {
        if (!node->left) node->left = new Node();
        update(node->left, start, mid, index);
    }
    else {
        if (!node->right) node->right = new Node();
        update(node->right, mid + 1, end, index);
    }
    int tmp1 = (node->left) ? node->left->value : 0;
    int tmp2 = (node->right) ? node->right->value : 0;
    node->value = tmp1 + tmp2;
}

int query(Node *node, int start, int end, int left, int right) {
    if (!node || right < start || end < left) return 0;
    if (left <= start && end <= right) return node->value;
    int mid = (start + end) >> 1;
    return query(node->left, start, mid, left, right) + query(node->right, mid + 1, end, left, right);
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        update(root, 1, MAX_V, num);
        cout << query(root, 1, MAX_V, num + 1, MAX_V) + 1 << endl;
    }
}