// author: 류호석(rhs0266)

struct Node {
    int id;
    int v;
    Node* nxt;
    Node() {}
    Node(int id, int v) :id(id), v(v), nxt(nullptr) {}
    Node(int id, int v, Node* nxt) : id(id), v(v), nxt(nxt) {}
}node[500055];
int cnt;
int version[100055], num[100055];
 
Node* getNewNode(int id, Node* nxt = nullptr) {
    Node* ret = &node[cnt++];
    ret->id = id;
    ret->nxt = nxt;
    ret->v = ++version[id];
    return ret;
}
 
struct Team {
    Node* head[6];
    Node* tail[6];
}t[6];
 
void init()
{
    cnt = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            t[i].tail[j] = t[i].head[j] = getNewNode(0);
        }
    }
 
    for (int i = 0; i <= 100000; i++) {
        version[i] = 0;
        num[i] = 0;
    }
}
 
void hire(int mID, int mTeam, int mScore)
{
    Node* newNode = getNewNode(mID);
    t[mTeam].tail[mScore]->nxt = newNode;
    t[mTeam].tail[mScore] = newNode;
    num[mID] = mTeam;
}
 
void fire(int mID)
{
    version[mID] = -1;
}
 
void updateSoldier(int mID, int mScore)
{
    hire(mID, num[mID], mScore);
}
 
void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore < 0) {
        for (int j = 1; j <= 5; j++) {
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            // j -> k
            if (j == k) continue;
 
            if (t[mTeam].head[j]->nxt == nullptr) continue;
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            t[mTeam].head[j]->nxt = nullptr;
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
    if (mChangeScore > 0) {
        for (int j = 5; j >= 1; j--) {
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            // j -> k
            if (j == k) continue;
 
            if (t[mTeam].head[j]->nxt == nullptr) continue;
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            t[mTeam].head[j]->nxt = nullptr;
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
}
 
int bestSoldier(int mTeam)
{
    for (int j = 5; j >= 1; j--) {
        Node* node = t[mTeam].head[j]->nxt;
        if (node == nullptr) continue;
 
        int ans = 0;
        while (node) {
            if (node->v == version[node->id]) {
                ans = ans < node->id ? node->id : ans;
            }
            node = node->nxt;
        }
        if (ans != 0) return ans;
    }
    return 0;
}