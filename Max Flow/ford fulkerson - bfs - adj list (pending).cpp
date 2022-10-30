#include<bits/stdc++.h>
using namespace std;

int bfs(vector<vector<int> > adj, vector<vector<int> > capacity, int v, int s, int t, int parent[]){
    memset(parent, -1, v);
    parent[s] = -2;
    queue<pair<int, int> > q;   // <vertex, wt>
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int next = 0; next<adj[cur].size(); next++) {
                cout << "in" <<endl;
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push( pair <int, int> (next, new_flow));
            }
        }
    }

    return 0; // We couldn't reach sink in BFS starting from source, FFS algo will terminate if no more augmenting path is found
}

int main(){
    int e;
    int v;

    fstream f ("flow-graph.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());

    vector<vector<int> > capacity (v, vector<int>());
    vector<vector<int> > adj (v, vector<int>());

//    int res_graph[v][v];
//    for(int i = 0; i<v; i++){
//        for (int j = 0; j<v; j++){
//            res_graph[i][j] = 0;
//        }
//    }

    while(!f.eof()){

        int v1, v2, wt;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());
        f >> word;
        wt = atoi(word.c_str());

//        res_graph[v1][v2] = wt;
        adj[v1].push_back(v2);
        capacity[v1].push_back(wt);
        capacity[v2].push_back(0);  // for reverse edges

    }
    f.close();

    int parent[v];
    int maxFlow = 0;
    int s = 0;
    int t = 5;


    int pathFlow;
    while(pathFlow = bfs(adj, capacity, v, s, t, parent)){    // running bfs as long as there is a path from s to t

//        for(int v = t; v!=s; v = parent[v]){
//            int u = parent[v];
//            pathFlow = min(pathFlow, res_graph[u][v]);  // finding the bottleneck capacity
//        }

        // updating the residual graph along the chosen path
        // the path is chosen by bfs via the parent[]
        for(int v = t; v!=s; v = parent[v]){
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
            cout << pathFlow << endl;
        }

        maxFlow += pathFlow;
    }

    cout << "Max flow: " << maxFlow;


}
