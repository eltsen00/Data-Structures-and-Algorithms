#include <iostream>
#include <vector>
using namespace std;

vector<bool> visited;
vector<bool> onPath;
bool hasCycle = false;
int countNode = 0;

// 判断无向图是否为树：连通且无环
void traverse(vector<vector<int>>& graph, int node, int parent) {
    if(hasCycle) return;
    visited[node] = true;
    onPath[node] = true;
    countNode++;
    for(int neighbor : graph[node]) {
        if(!visited[neighbor]) {
            traverse(graph, neighbor, node);
        }
        else if(onPath[neighbor] && neighbor != parent) {// 无向图记录parent避免误判成环
            hasCycle = true;
            return;
        }
    }
    onPath[node] = false;
}

int main() {
    int count;
    cin >> count;
    while(count--) {
        int n;
        cin >> n;
        int m;
        cin >> m;
        vector<vector<int>> graph(n + 1, vector<int>());
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        visited.assign(n + 1, false);
        onPath.assign(n + 1, false);
        countNode = 0;
        hasCycle = false;
        traverse(graph, 1, -1);
        if(countNode == n && !hasCycle) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}