#include<bits/stdc++.h>
using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
#define INF 0x3f3f3f3f

//O(V+E)

bool isCyclicDirected(vector< vector<int> > adj, vector<int> & color, int vertex){
    // this is based on DFS
    color[vertex] = GRAY;
    for(int i = 0; i<adj[vertex].size(); i++){
        int u = adj[vertex][i];
        if(color[u] == WHITE){
            if(isCyclicDirected(adj, color, u))
                return true;

        } else if(color[u] == GRAY)
                return true;
    }

    color[vertex] = BLACK;
    return false;
}

void dfs(vector< vector<int> > adj, vector<bool> & vis, stack<int> &st, int vertex){
    if(!vis[vertex]){
        vis[vertex] = true;
    }

    for(int i = 0; i<adj[vertex].size(); i++){
       if(!vis[adj[vertex][i]]){
            dfs(adj, vis, st, adj[vertex][i]);
       }
    }

    st.push(vertex);
}

void shortestPath(vector< vector<int> > adj, vector< vector<double> > wt, int s){
    //O(V+E)
    stack<int> st;
    int v = adj.size();
    vector<bool> vis (v, false);
    vector<int> color;
    for(int i = 0; i<v; i++){
        color.push_back(WHITE);
    }

    int startVertex = 0;
    for(int i = 0; i<v; i++){
        if(!vis[i]){
            if(isCyclicDirected(adj, color, i)){
                cout << "Cyclic, cannot continue.";
                exit(1);
            }
        }
    }

    for(int i = 0; i<v; i++){
        vis[i] = false;
    }

    for(int i = 0; i<v; i++){
        if(!vis[i])
            dfs(adj, vis, st, i);
            // toposorting and populating the stack
    }

    vector <int> dist(v, INF);
    vector <int> parent(v, -1);

    dist[s] = 0;
    // after toposorting, all the edges will be going forward
    // so, we don't need to go back and try to relax the edges backwards
    while(!st.empty()){
        int u = st.top();
        st.pop();
        if(dist[u] != INF){
            for(int i = 0; i<adj[u].size(); i++){
                int v = adj[u][i];
                if(dist[v] > dist[u] + wt[u][i]){
                    dist[v] = dist[u] + wt[u][i];
                    parent[v] = u;
                }
            }
        }
    }

    for (int i = 0; i < v; i++)
        (dist[i] == INF)? cout << "INF ": cout << dist[i] << " ";
}

int main(){
    int v;
    int e;
    fstream f ("toposort.txt");
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
    vector <vector<double> > wt (v, vector<double>());


    while(!f.eof()){
        int v1, v2;
        double w;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());
        f >> word;
        w = atof(word.c_str());

        adj[v1].push_back(v2);
        wt[v1].push_back(w);
    }
    f.close();

    int source = 1;
    shortestPath(adj, wt, source);



}





