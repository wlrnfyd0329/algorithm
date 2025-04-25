// 다이나믹 세그먼트 트리만 생각했었는데, 그냥 이진 트리도 Node를 생성하면서 가도 된다.
// 근데 이진 검색트리는 순차적인 정렬된 데이터가 들어오면 편향트리가 된다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

struct Node {
    int value;
    Node *left, *right;
    Node(int value) : value(value) {
        left = right = nullptr;
    }
} *root;

void pre_order(Node *node, int value) { // O(logN)
    if (node->value > value) {
        if (node->left) pre_order(node->left, value);
        else node->left = new Node(value);
    }
    else {
        if (node->right) pre_order(node->right, value);
        else node->right = new Node(value);
    }
}

void post_order(Node *node) {
    if (node->left) post_order(node->left);
    if (node->right) post_order(node->right);
    cout << node->value << endl;
}

int main() { 
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    root = new Node(n);
    while (cin >> n) { // O(NlogN) : 120,000
		pre_order(root, n);
	}

    post_order(root); // O(N) : 10,000
}   