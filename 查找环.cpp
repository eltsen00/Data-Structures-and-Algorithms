#include<iostream>
#include<vector>
using namespace std;

vector<bool> visited;
vector<bool> onPath;
bool hasCycle=false;

// 有向图
// 逻辑正确：利用 onPath 数组记录当前递归栈中的节点（相当于三色标记法中的灰色）
// 如果遇到已在 onPath 中的节点，说明发现了后向边，存在环
void findCycleUtil(int node, vector<vector<int>>& graph) {
    if(hasCycle){
        return; // 已经找到环，提前返回
    }
    visited[node] = true;
    onPath[node] = true;
    for(int &nextNode:graph[node]){
        if(!visited[nextNode]){
            findCycleUtil(nextNode, graph);
            if(hasCycle){
                return; // 已经找到环，提前返回
            }
        }
        else if(onPath[nextNode]){
            hasCycle = true;
            return; // 找到环
        }
    }
    onPath[node] = false; // 回溯
}

// 无向图
// 逻辑正确：利用 visited 数组和 parent 指针
// 如果遇到已访问的节点，且该节点不是父节点，说明构成了环
//
// 【注意】：无向图不能直接复用这份有向图的代码。
// 原因：无向图的边是双向的。当从 A 走到 B 时，B 的邻居列表里一定有 A。
// 此时 A 还在 onPath 中，有向图算法会误判 B->A 是环。
// 若要复用，必须增加 parent 参数，并在遍历时跳过 parent (if (nextNode == parent) continue;)。
void findCycleUtilUndirected(int node, int parent, vector<vector<int>>& graph) {
    if(hasCycle){
        return; // 已经找到环，提前返回
    }
    visited[node] = true;
    for(int &nextNode:graph[node]){
        if(!visited[nextNode]){
            findCycleUtilUndirected(nextNode, node, graph);
            if(hasCycle){
                return; // 已经找到环，提前返回
            }
        }
        else if(nextNode != parent){
            hasCycle = true;
            return; // 找到环
        }
    }
}

// 对于无向图的环检测，也可以使用并查集算法。

int main(){
    vector<vector<int>> graph = {
        {1},
        {2},
        {0}
    };
    int n = (int)graph.size();
    visited.resize(n, false);
    onPath.resize(n, false);
    for(int i=0;i<n;i++){
        if(!visited[i]){
            // 针对有向图检测
            findCycleUtil(i, graph); 
            // 如果是无向图，应该调用：
            // findCycleUtilUndirected(i, -1, graph);
            if(hasCycle){
                break;
            }
        }
    }
    if(hasCycle){
        cout << "有环" << endl;
    }
    else{
        cout << "无环" << endl;
    }
    return 0;
}