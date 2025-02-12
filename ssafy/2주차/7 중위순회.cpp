#include <iostream>

using namespace std;

struct Node
{
    char data;
    int left;
    int right;
} tree[101];

void cycle(int index) {
    if (index == 0) {
        return;
    }

    cycle(tree[index].left);
    cout << tree[index].data;
    cycle(tree[index].right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int tc = 1; tc <= 10; tc++) {
        cout << "#" << tc << " ";
        int N;
        cin >> N;
        for(int i = 1; i <= N; i++) {
            char b;
            int a, c = 0, d = 0;
            if (N % 2 == 0) {
                if (i < N / 2) {
                    cin >> a >> b >> c >> d;
                }
                else if (i == N / 2) {
                    cin >> a >> b >> c;
                }
                else {
                    cin >> a >> b;
                }
            }
            else {
                if (i <= N / 2) {
                    cin >> a >> b >> c >> d;
                }
                else {
                    cin >> a >> b;
                }
            }
            
            tree[a] = {b, c, d};
        }
        
        cycle(1);
        cout << "\n";
    }
}