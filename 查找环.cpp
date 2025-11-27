#include<iostream>
#include<vector>
using namespace std;

vector<bool> visited;
vector<bool> onPath;
bool hasCycle=false;

// 有向图
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
        else{
            if(onPath[node]){
                hasCycle=true;
                return;
            }
        }
        if(hasCycle){
            return; // 已经找到环，提前返回
        }
    }
    onPath[node] = false; // 回溯
}

// 无向图
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

int main(){
    vector<vector<int>> graph = {
        {1},
        {2},
        {0}
    };
    int n = graph.size();
    visited.resize(n, false);
    onPath.resize(n, false);
    for(int i=0;i<n;i++){
        if(!visited[i]){
            findCycleUtil(i, graph);
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