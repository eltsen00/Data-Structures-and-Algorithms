#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 图的邻接表表示法
class Graph {
public:
    struct Edge {
        int to;
        int weight;
        Edge(int t, int w = 1) : to(t), weight(w) {}
    };

private:
    // 图的邻接表
    std::vector<std::vector<Edge>> adj;

public:
    Graph(int n) : adj(n) {}

    // 添加边
    void addEdge(int from, int to, int weight = 1) {
        adj[from].push_back({to, weight});
    }

    // 删除边
    void removeEdge(int from, int to) {
        auto& edges = adj[from];
        for(auto it = edges.begin(); it != edges.end(); ++it) {
            if(it->to == to) {
                edges.erase(it);
                break;
            }
        }
    }

    // 判断是否有边
    bool hasEdge(int from, int to) const {
        const auto& edges = adj[from];
        for(const auto& edge : edges) {
            if(edge.to == to) {
                return true;
            }
        }
        return false;
    }

    // 获取邻接节点
    const std::vector<Edge>& neighbors(int node) const {
        return adj[node];
    }

    // 获取图的大小
    size_t size() const {
        return adj.size();
    }
};

// 遍历图的所有节点
void traverseNodes(const Graph& graph, int s, std::vector<bool>& visited) {
    // base case
    if(s < 0 || s >= graph.size()) {
        return;
    }
    // 前序位置
    visited[s] = true;
    std::cout << "visit " << s << std::endl;
    for(const Graph::Edge& e : graph.neighbors(s)) {
        if(!visited[s]) traverseNodes(graph, e.to, visited);
    }
    // 后序位置
}

// 遍历图的所有边
void traverseEdges(const Graph& graph, int s, vector<vector<bool>>& visited) {
    // base case
    if(s < 0 || s >= graph.size()) {
        return;
    }
    for(const Graph::Edge& e : graph.neighbors(s)) {
        if(visited[s][e.to]) {  // visited表示从s到e.to的边是否被访问过
            continue;
        }
        // 前序位置
        visited[s][e.to] = true;
        std::cout << "traverse edge: " << s << " -> " << e.to << std::endl;
        traverseEdges(graph, e.to, visited);
        // 后序位置
    }
}

// 遍历图的所有路径(onPath数组与visited数组的区别在于，onPath表示当前路径上的节点，visited表示所有访问过的节点，但没有本质区别)
void traversePaths(const Graph& graph, int src, int dst, std::vector<bool>& onPath, std::vector<int>& path) {
    // base case
    if(src < 0 || src >= graph.size()) {
        return;
    }
    if(onPath[src]) {
        // 防止死循环
        return;
    }
    // 前序位置
    onPath[src] = true;
    path.push_back(src);
    if(src == dst) {
        // 到达目标节点，输出路径
        std::cout << "path: ";
        for(int node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
    for(const Graph::Edge& e : graph.neighbors(src)) {
        if(onPath[e.to]) traversePaths(graph, e.to, dst, onPath, path);
    }
    // 后序位置
    path.pop_back();
    onPath[src] = false;
}

void bfs(Graph& graph, int start) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    int step = 0;
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        int sz = (int)q.size();
        for(int i = 0; i < sz; i++) {
            int node = q.front();
            q.pop();
            // 访问节点
            cout << "visit " << node << endl;
            for(const Graph::Edge& e : graph.neighbors(node)) {
                if(visited[e.to]) {
                    continue;
                }
                visited[e.to] = true;
                q.push(e.to);
            }
        }
        step++;
    }
    cout << "bfs step: " << step << endl;
}