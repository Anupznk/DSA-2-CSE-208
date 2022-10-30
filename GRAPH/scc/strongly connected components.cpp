#include<bits/stdc++.h>
using namespace std;

void dfs(vector< vector<int> > adj, vector<bool> & vis, stack<int> &st, int vertex, bool show){
    // O(V+E)
    if(!vis[vertex]){
        if (show){
            cout << vertex << " ";
        }
        vis[vertex] = true;
    }

    for(int i = 0; i<adj[vertex].size(); i++){
       if(!vis[adj[vertex][i]]){
            dfs(adj, vis, st, adj[vertex][i], show);
       }
    }
    if(!show)
        st.push(vertex);
}

int main(){
    int v;  // v = num of vertices
    int e;  // e = num of edges
    fstream f ("scc.txt");
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

        adj[v1].push_back(v2);
    }

    vector<bool> vis (v, false);
    dfs(adj, vis, st, 0, false);

    vis.clear();
    for(int i=0; i<v; i++){
        vis[i] = false;
    }
    vector <vector<int> > adj_rev (v, vector<int>());

    f.seekg(0, ios::beg);
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());
    while(!f.eof()){
        int v1, v2;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());

        adj_rev[v2].push_back(v1);  // taking the reverse of G
    }

    while(!st.empty()){
        int v = st.top();
        st.pop();
        dfs(adj_rev, vis, st, v, true);
        cout<<endl;
    }

    f.close();

}





