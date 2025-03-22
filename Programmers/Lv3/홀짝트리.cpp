#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

int origin = 0, reverse_origin = 0;
unordered_map<int, unordered_set<int>> graph;
unordered_map<int, bool> chk;
vector<vector<int>> tree;

void set_tree(vector<int> &n) {
    queue<int> q;
    for(auto node : n) {
        if (chk[node]) continue;
        vector<int> sub_tree;
        chk[node] = true;
        q.push(node);
        sub_tree.push_back(node);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto k : graph[cur]) {
                if (chk[k]) continue;
                chk[k] = true;
                q.push(k);
                sub_tree.push_back(k);
            }
        }
        tree.push_back(sub_tree);
    }
}

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
    vector<int> ans;
    for(auto k : edges) {
        graph[k[0]].insert(k[1]);
        graph[k[1]].insert(k[0]);
    }
    
    set_tree(nodes);
    
    for(int i = 0; i < tree.size(); i++) {
        int ori = 0, rev = 0;
        for(auto k : tree[i]) {
            if (k % 2 == 0 && graph[k].size() % 2 == 0) ori++;  
            if (k % 2 == 1 && graph[k].size() % 2 == 1) ori++;  
            if (k % 2 == 0 && graph[k].size() % 2 == 1) rev++;  
            if (k % 2 == 1 && graph[k].size() % 2 == 0) rev++;  
        }
        if (ori == 1) origin++;
        if (rev == 1) reverse_origin++;
    }
    
    ans.push_back(origin);
    ans.push_back(reverse_origin);
    return ans;
}