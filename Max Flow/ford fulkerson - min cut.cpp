#include<bits/stdc++.h>
using namespace std;
const int v = 100;

bool bfs(int res_graph[][v], vector <bool> &vis, int s, int t, int parent[]){

    for(int i = 0; i<vis.size(); i++){
        vis[i] = false;
    }
    queue<int> q;

    q.push(s);
    vis[s] = true;
    parent[s] = -1;

    while(!q.empty()){
        int adjVertex = q.front();
        q.pop();
        for(int i=0; i<v; i++){
            int currVertex = i;
            if(!vis[currVertex] && res_graph[adjVertex][i] > 0){ // wt[adjVertex][i] > 0 ensures that it is possible to give more flow via this edge

                if (currVertex == t){
                    parent[currVertex] = adjVertex;
                    return true;
                }
                q.push(currVertex);
                vis[currVertex] = true;
                parent[currVertex] = adjVertex;

            }
        }
    }
    return false;   // We couldn't reach sink in BFS starting from source, FFS algo will terminate if no more augmenting path is found
}

int main(){
    int e;  // e = num of edges
    fstream f ("flow-graph.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    int tot_vertex = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());

    int res_graph[v][v];
    int main_graph[v][v];
    for(int i = 0; i<v; i++){
        for (int j = 0; j<v; j++){
            res_graph[i][j] = 0;
        }
    }

    while(!f.eof()){
        int v1, v2, wt;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());
        f >> word;
        wt = atoi(word.c_str());

        res_graph[v1][v2] = wt;

    }
    f.close();

    // keeping backup of the original graph
    for(int i = 0; i<v; i++){
        for (int j = 0; j<v; j++){
            main_graph[i][j] = res_graph[i][j];
        }
    }

    int parent[v];
    vector <bool> vis(tot_vertex);
    int maxFlow = 0;
    int s = 0;
    int t = 5;

    while(bfs(res_graph,vis, s, t, parent)){    // running bfs as long as there is a path from s to t
        int pathFlow = INT_MAX;
        for(int v = t; v!=s; v = parent[v]){
            int u = parent[v];
            pathFlow = min(pathFlow, res_graph[u][v]);  // finding the bottleneck capacity
        }

        // updating the residual graph along the chosen path
        // the path is chosen by bfs via the parent[]
        for(int v = t; v!=s; v = parent[v]){
            int u = parent[v];
            res_graph[u][v] -= pathFlow;
            res_graph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    cout << "Max flow: " << maxFlow << endl;

    // now the graph has max flow, let's find the min cut
    vector< pair<int, int> > edge_list;
    bfs(res_graph, vis, s, t, parent);
    for(int i = 0; i<tot_vertex; i++){
        for(int j = 0; j<tot_vertex; j++){
            if(vis[i] && !vis[j] && main_graph[i][j] > 0){
                edge_list.push_back({i, j});
            }
        }
    }

    cout << "min cut edge list:" << endl;
    for(int i = 0; i<edge_list.size(); i++){
        cout << edge_list[i].first << ", " << edge_list[i].second << endl;
    }




}
