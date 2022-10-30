#include<bits/stdc++.h>
using namespace std;

void dfs(vector< vector<int> > adj, vector<bool> & vis, int vertex){
    if(!vis[vertex]){
        cout << vertex << " "; // reachable from "vertex"
        vis[vertex] = true;
    }

    for(int i = 0; i<adj[vertex].size(); i++){
        int currVertex = adj[vertex][i];
        if(!vis[currVertex]){
            dfs(adj, vis, currVertex);
        }
    }
}

void bfs(vector<vector<int> > adj, vector<bool> &vis, int vertex){
    queue<int> q;
    if(!vis[vertex]){
        q.push(vertex);
        vis[vertex] = true;
        cout << vertex << " "; // reachable from "int vertex"
    }
    while(!q.empty()){
        int adjVertex = q.front();
        q.pop();
        for(int i=0; i<adj[adjVertex].size(); i++){
            int currVertex = adj[adjVertex][i];
            if(!vis[currVertex]){
                q.push(currVertex);
                vis[currVertex] = true;
                cout << currVertex << " "; // reachable from "int vertex"
            }
        }
    }
}

int main(){
    int v;  // v = num of vertices
    int e;  // e = num of edges
    fstream f ("graph.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());

    vector <vector<int> > adj (v, vector<int>());

    while(!f.eof()){
        int v1, v2;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());

        adj[v1].push_back(v2);
        adj[v2].push_back(v1);  // for undirected graph
    }
    f.close();

    vector<bool> vis (v, false);
    dfs(adj, vis, 9);

}
