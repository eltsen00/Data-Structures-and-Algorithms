/*Dijkstra 算法是一种用于计算图中单源最短路径的算法，其本质是标准 BFS 算法 + 贪心思想。
如果图中包含负权重边，会让贪心思想失效，所以 Dijkstra 只能处理不包含负权重边的图。

Dijkstra 算法和标准的 BFS 算法的区别只有两个：
1、标准 BFS 算法使用普通队列，Dijkstra 算法使用优先级队列，让距离起点更近的节点优先出队（贪心思想的体现）。
2、标准 BFS 算法使用一个 visited 数组记录访问过的节点，确保算法不会陷入死循环；Dijkstra 算法使用一个 distTo
数组，确保算法不会陷入死循环，(重点)同时记录起点到其他节点的最短路径。*/
// 当节点i第一次出队时，对应的distFromStart就是从起点到节点i的最小路径权重和。（推理成立的前提是，经过的的边越多，路径的权重和越大。）

/*队列中可能存在重复节点：
需要注意的是，对于标准的 BFS 算法，因为入队时就会更新 visited 数组，所以队列中不会存在重复的节点。而 Dijkstra
算法在入队时不会更新 distTo 数组，仅在出队时更新 distTo 数组，所以队列中可能存在重复的节点 state。*/
#include <cstddef>
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
    const std::vector<Edge>& neighbors(int u) {
        return adj[u];
    }
    std::size_t numNodes() {
        return adj.size();
    }
};

// 记录队列中的状态
struct State {
    // 当前节点 ID
    int node;
    // 从起点 s 到当前 node 节点的最小路径权重和
    int distFromStart;
    State(int _node, int _distFromStart) : node(_node), distFromStart(_distFromStart) {}
    bool operator>(const State& other) const {
        return distFromStart > other.distFromStart;
    }
};

// 自定义比较器，使得 distFromStart 较小的 State 先出队
struct Compare {
    bool operator()(const State& a, const State& b) const {
        return a.distFromStart > b.distFromStart;
    }
};

// 重点：一个节点第一次出队时，对应的 distFromStart 就是从起点到该节点的最小路径权重和
std::vector<int> dijkstra(Graph& graph, int src) {
    // 初始化 distTo 数组
    std::vector<int> distTo(graph.numNodes(), INT_MAX);
    distTo[src] = 0;  // 记得写
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push(State(src, 0));
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int curNode = cur.node;
        int curDistFromStart = cur.distFromStart;
        // 必须保留！
        // 因为优先级队列中可能存在同一个节点的多个状态（旧的长路径），
        // 当一个节点通过更短的路径被更新并再次入队后，旧的状态依然在队列中。
        // 这里用于过滤掉那些已经过时的、比当前最短路径更长的状态。
        if(curDistFromStart > distTo[curNode]) {
            continue;
        }
        for(const Edge& child : graph.neighbors(curNode)) {
            int nextTo = child.to;
            int nextDistFromStart = child.weight + curDistFromStart;
            if(nextDistFromStart < distTo[nextTo]) {  // 发现更短的路，更新路径
                pq.push(State(nextTo, nextDistFromStart));
                distTo[nextTo] = nextDistFromStart;
            }
        }
    }
    return distTo;
}