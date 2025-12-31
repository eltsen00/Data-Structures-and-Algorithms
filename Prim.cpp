// Prim算法可以处理负权边，但不能处理负权环路。
// 输入图必须是连通的无向图，否则无法生成覆盖所有节点的最小生成树。
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class Graph {
private:
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
    int weightFromTree;
    State(int _node, int _weight) : node(_node), weightFromTree(_weight) {}
    bool operator>(const State& other) const {
        return weightFromTree > other.weightFromTree;
    }
};

// 重点：贪心，每次都选择连接树和非树节点的最小权边
int prim(const Graph& graph) {
    int totalWeight = 0;
    std::vector<bool> visited(graph.numNodes(), false);
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push(State(0, 0));
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int curNode = cur.node;
        int curWeight = cur.weightFromTree;
        if(visited[curNode]) {
            continue;
        }
        visited[curNode] = true;
        totalWeight += curWeight;
        for(const Edge& edge : graph.neighbors(curNode)) {
            if(!visited[edge.to]) {
                pq.push(State(edge.to, edge.weight));
            }
        }
    }
    // 检查是否所有节点都被访问过
    bool allVisited = true;
    for(bool v : visited) {
        if(!v) {
            allVisited = false;
            break;
        }
    }
    return allVisited ? totalWeight : -1; // 如果图不连通，返回 -1
}