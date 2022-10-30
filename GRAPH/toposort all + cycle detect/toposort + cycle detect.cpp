#include<bits/stdc++.h>
using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

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

bool isCyclicUndirected(vector< vector<int> > adj, vector<int> & color, int vertex, int parent){
    color[vertex] = GRAY;
    for(int i = 0; i<adj[vertex].size(); i++){
        int u = adj[vertex][i];
        if(color[u] == WHITE){
            if(isCyclicUndirected(adj, color, u, vertex))
                return true;

        } else if(color[u] == GRAY && u != parent)  // found back edge
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

int main(){
    int v;  // v = num of vertices
    int e;  // e = num of edges
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
    stack<int> st;

    while(!f.eof()){
        int v1, v2;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());

        adj[v1-1].push_back(v2-1);
//        adj[v2-1].push_back(v1-1);  // for undirected graph
    }

    vector<bool> vis (v, false);
    vector<int> color;
    for(int i = 0; i<v; i++){
        color.push_back(WHITE);
    }

    int startVertex = 1;
    int parent = -1;
    if(isCyclicDirected(adj, color, startVertex-1)){
        cout << "Cyclic, cannot sort topologically";
        exit(1);
    } else  cout<< "Not cyclic"<< endl;

//    if(isCyclicUndirected(adj, color, startVertex-1, parent)){
//        cout << "Cyclic, cannot sort topologically";
//        exit(1);
//    } else  cout<< "Not cyclic"<< endl;

    for(int i = 0; i<v; i++){
        if(!vis[i])
            dfs(adj, vis, st, i);
    }

    while(!st.empty()){
        int v = st.top();
        st.pop();
        cout<< v << " ";
    }

    f.close();

}





