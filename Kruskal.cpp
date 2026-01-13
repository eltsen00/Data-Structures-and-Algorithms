// 生成树: 给定一个无向连通图G,其生成树是G的一个子图，它包含G中的所有顶点，并且是一棵树（即无环连通图）。生成树具有以下特性：1.
// 包含原图中的所有顶点。2. 边的数量为顶点数减一（V-1条边）。3. 连通且无环。
// Kruskal 算法，主要的难点是利用Union-Find并查集算法向最小生成树中添加边，配合排序的贪心思路，从而得到一棵权重之和最小的生成树
#include <vector>
// 并查集实现
std::vector<int> parent;
int uf_count = 0;
int find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}
bool unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if(rootA == rootB) {
        return false;
    }
    parent[rootA] = rootB;
    uf_count--;
    return true;
}

// Kruskal 算法主体
int Kruskal(const std::vector<std::vector<int>>& edges, int n) {
    parent.resize(n);
    uf_count = n;
    for(int i = 0; i < n; i++) {
        parent[i] = i;
    }
    int mst = 0; // 最小生成树的权重和
    for(const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        if(unite(u, v)) {
            mst += weight;
        }
    }
    return uf_count == 1 ? mst : -1;  // 如果最终并查集只有一个连通分量，说明生成树构建成功
}