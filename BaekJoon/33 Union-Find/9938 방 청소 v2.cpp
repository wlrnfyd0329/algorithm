#include <iostream>
#include <vector>
#define endl "\n";

using namespace std;

struct Drink {
    int a, b;
};

int N, L;

vector<Drink> drink;
vector<int> parent;
vector<bool> drawer;

int find(int a) {
    if (a == parent[a]) return a;
    else return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
    parent[find(a)] = find(b);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> L;

    drink = vector<Drink>(N + 1);
    parent = vector<int>(L + 1);

    drawer = vector<bool>(L + 1, false);

    for (int i = 1; i <= N; i++) {
        cin >> drink[i].a >> drink[i].b;
    }

    for (int i = 0; i <= L; i++) {
        parent[i] = i;
    }



    for (int i = 1; i <= N; i++) {
        bool canMove = true;
        Drink curr = drink[i];
        if (!drawer[curr.a]) {
            drawer[curr.a] = true;
            uni(curr.a, curr.b);
        }
        else if (!drawer[curr.b]) {
            drawer[curr.b] = true;
            uni(curr.b, curr.a);
        }
        else if (!drawer[find(curr.a)]) {
            drawer[find(curr.a)] = true;
            uni(curr.a, curr.b);
        }
        else if (!drawer[find(curr.b)]) {
            drawer[find(curr.b)] = true;
            uni(curr.b, curr.a);
        }
        else canMove = false;


        string ans = canMove ? "LADICA" : "SMECE";
        cout << ans << endl;
    }
    return 0;
}