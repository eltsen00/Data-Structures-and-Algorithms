// 并查集底层其实是一片森林（若干棵多叉树），每棵树代表一个连通分量，使用父亲表示法
#include <vector>
#include <unordered_map>
using namespace std;
class DSU{
private:
    vector<int> parent; // parent[i]表示节点i的父亲节点
    vector<int> size;   // 记录每棵树包含的节点数
    int _count; // 连通分量个数
public:
    DSU(int n):parent(n),size(n,1), _count(n){
        for(int i=0; i<n; i++) {
            parent[i] = i; // 初始化时每个节点的父亲是自己
        }
    }
    // 查找节点x所在的连通分量的代表节点（根节点）
    int find(int x){
        if(parent[x] != x){ // 根节点特有的性质：parent[x]==x
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
        //迭代写法
        /*
        int root = x;
        while(parent[root] != root){
            root = parent[root];
        }
        int old_parent = parent[x];
        while(x != root){
            parent[x] = root;
            x = old_parent;
            old_parent = parent[x];
        }
        return root;
        */
    }
    // 合并节点x和节点y所在的连通分量
    void unite(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX==rootY) return; // 已经在同一个连通分量中
        // 按秩合并
        if(size[rootX]<size[rootY]){
            parent[rootX]=rootY;
            size[rootY]+=size[rootX];
        }
        else{
            parent[rootY]=rootX;
            size[rootX]+=size[rootY];
        }
        _count--; // 连通分量个数减少1
    }
    // 判断节点x和节点y是否在同一个连通分量中
    bool connected(int x, int y){
        return find(x)==find(y);
    }

    // 获取当前的连通分量个数
    int getCount() const {
        return _count;
    }

    // 返回所有连通分量
    unordered_map<int,vector<int>> getComponents() {
        unordered_map<int, vector<int>> components;
        for (int i = 0; i < parent.size(); ++i) {
            int root = find(i);
            components[root].push_back(i);
        }
        return components;
    }

    // 返回某个连同分量的大小
    int getSize(int x) {
        int root = find(x);
        return size[root];
    }
};