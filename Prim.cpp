// Prim算法可以处理负权边，但不能处理负权环路。
// 输入图必须是连通的无向图，否则无法生成覆盖所有节点的最小生成树。
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int weight;
};

class Graph {
    std::vector<std::vector<Edge>> adj;

public:
    Graph(int n) : adj(n) {}
    const std::vector<Edge>& neighbors(int u) const {
        return adj[u];
    }
    std::size_t numNodes() const {
        return adj.size();
    }
};

struct State {
    int node;
    int distFromStart;
    State(int _node, int _distFromStart) : node(_node), distFromStart(_distFromStart) {}
    bool operator>(const State& other) const {
        return distFromStart > other.distFromStart;
    }
};

int prim(const Graph& graph) {
    int totalWeight = 0;
    std::vector<bool> visited(graph.numNodes(), false);
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push(State(0, 0));
    visited[0] = true;
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int curNode = cur.node;
        int curDistFromStart = cur.distFromStart;
        if(visited[curNode]) {
            continue;
        }
        visited[curNode] = true;
        totalWeight += curDistFromStart;
        for(const Edge& edge : graph.neighbors(curNode)) {
            if(!visited[edge.to]) {
                pq.push(State(edge.to, edge.weight));
            }
        }
    }
    return totalWeight;
}