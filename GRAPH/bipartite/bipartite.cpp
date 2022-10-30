#include<bits/stdc++.h>
using namespace std;

bool isBipartite(vector<vector<int> > adj, vector<bool> vis, int v, int src){
    // O(V+E)
    // this is based on BFS
    int colorArr[v];
    for(int i=0; i<v; i++){
        colorArr[i] = -1;
    }
    colorArr[src] = 1;
    queue<int> q;
    q.push(src);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0; i<adj[u].size(); i++){
            int currVertex = adj[u][i];
            if(u == currVertex) // self-loop
                return false;
            if(colorArr[currVertex] == -1){ // means unvisited
                colorArr[currVertex] = 1 - colorArr[u];
                q.push(currVertex);

            } else if(colorArr[currVertex] == colorArr[u])
                return false;
        }
    }
    return true;
}

int main(){
    int v;  // v = num of vertices
    int e;  // e = num of edges
    fstream f ("bipartite.txt");
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

        adj[v1-1].push_back(v2-1);
        adj[v2-1].push_back(v1-1);  // for undirected graph
    }
    f.close();

    vector<bool> vis (v, false);

    if(isBipartite(adj, vis, v, 0))
        cout << "Bipartite";
    else
        cout << "Not Bipartite";
}
