#include<iostream>
#include<vector>
using namespace std;

vector<bool> visited;
vector<bool> color;
bool ok=true;

void isBipartiteDFS(vector<vector<int>>& graph,int node){
    if(!ok){
        return;
    }
    visited[node]=true;
    for(int& nextNode:graph[node]){
        if(!visited[nextNode]){
            color[nextNode]=!color[node];
            isBipartiteDFS(graph,nextNode);
        }
        else{
            if(color[nextNode]==color[node]){
                ok=false;
                return;
            }
        }
    }
}

int main(){
    vector<vector<int>> graph={
        {1,3},
        {0,2},
        {1,3},
        {0,2}
    };
    visited.resize(graph.size(),false);
    color.resize(graph.size(),false);
    for(int i=0;i<graph.size();i++){
        if(!visited[i]){
            isBipartiteDFS(graph,i);
            if(!ok){
                break;
            }
        }
    }
    if(ok){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    return 0;
}