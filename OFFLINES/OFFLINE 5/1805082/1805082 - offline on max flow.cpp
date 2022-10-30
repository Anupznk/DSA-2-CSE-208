#include<bits/stdc++.h>
using namespace std;
const int MAX_VERTEX = 100;
const bool DEBUG = false;

bool bfs(int res_graph[][MAX_VERTEX], int v, int s, int t, int parent[]){
    // O(V^2)
    bool vis[v];
    memset(vis, 0, sizeof(vis));
    memset(parent, 0, sizeof(parent));
    queue<int> q;

    q.push(s);
    vis[s] = true;
    parent[s] = -1;

    while(!q.empty()){ // O(V^2)
        int adjVertex = q.front();
        q.pop();
        for(int i=0; i<v; i++){ // O(V)
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

    fstream f ("flow-graph.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    int v = atoi(word.c_str());

    int tot_teams = v;
    int tot_games = (v) * (v-1) / 2;  // we are removing the team from the graph that we are trying to eliminate
    int tot_vertex = tot_teams + tot_games + 2;

    int graph[MAX_VERTEX][MAX_VERTEX];
    string team_names[v];
    int team_wins[v];
    int team_match_left[v];
    int rem_match_matrix [v][v]; // the columns after the first 3 cols

    for(int i = 0; i<tot_vertex; i++){
        for (int j = 0; j<tot_vertex; j++){
            graph[i][j] = 0;
        }
    }

    int i = 0;
    while(i<v){
        f >> word;
        team_names[i] = word;

        f >> word;
        team_wins[i] = atoi(word.c_str());

        f >> word;

        f >> word;
        team_match_left[i] = atoi(word.c_str());

        for(int j = 0; j < v; j++){

            f >> word;
            rem_match_matrix[i][j] = atoi(word.c_str());
        }
        i++;
    }
    f.close();

    int parent[tot_vertex];

    int s = 0;  // setting the 0 index as source
    int t = tot_vertex-1;   // setting the last index as sink

    int index_mat[tot_teams][tot_teams];    // index tracking for all the vertices
    // filling the index array
    int currIndex = 1;
    for(int i = 0; i<tot_teams; i++){
        for(int j = i+1; j<tot_teams; j++){
            index_mat[i][j] = currIndex++;
        }
    }
    for(int i = 0; i<tot_teams; i++){
        index_mat[i][i] = currIndex++;
    }

    for(int x = 0; x<tot_teams; x++){
        // now add the edges and complete the flow graph for x (ignoring x in the graph)
        int maxFlow = 0;
        for(int i = 0; i<tot_vertex; i++){  // resetting the graph
            for (int j = 0; j<tot_vertex; j++){
                graph[i][j] = 0;
            }
        }

        int saturationVal = 0;  // if this is greater than flow value, then some matches left for other teams to win over team x
                                //so, x gets eliminated
        for(int i = 0; i<tot_teams; i++){

            for(int j = i+1; j<tot_teams; j++){
                if(i == x || j == x)
                    continue;   // ignoring the edges from sou to the node x
                graph[0][index_mat[i][j]] = rem_match_matrix[i][j]; // adding the edges from sou to game nodes
                saturationVal += rem_match_matrix[i][j];

                graph[index_mat[i][j]][index_mat[i][i]] = INT_MAX;  // adding the edges from game nodes to team nodes
                graph[index_mat[i][j]][index_mat[j][j]] = INT_MAX;  // adding the edges from game nodes to team nodes
            }

            graph[index_mat[i][i]][tot_vertex-1] = team_wins[x] + team_match_left[x] - team_wins[i];  // adding the edges from team nodes to sink node
        }

        if (DEBUG){
            for(int m = 0; m < tot_vertex; m++){
                for(int n = 0; n < tot_vertex; n++){
                    if(graph[m][n] == INT_MAX)
                        cout << "INF" << "\t";
                    else
                        cout << graph[m][n] << "\t";
                }
                cout << endl;
            }
        }

        while(bfs(graph, tot_vertex, s, t, parent)){    // running bfs as long as there is a path from s to t
                // O(VE * (O(V^2) + O(V))
                // O(V^3E + V^3)
                // O(EV^3)
                // O(En^6)  // n = num of teams
            int pathFlow = INT_MAX;
            for(int v = t; v!=s; v = parent[v]){
                int u = parent[v];
                pathFlow = min(pathFlow, graph[u][v]);  // finding the bottleneck capacity
            }

            // updating the residual graph along the chosen path
            // the path is chosen by bfs via the parent array
            for(int v = t; v!=s; v = parent[v]){    // O(V)
                int u = parent[v];
                graph[u][v] -= pathFlow;
                graph[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        if(saturationVal > maxFlow){
            cout << team_names[x] << " is eliminated." << endl;
        }
// bonus part
        stack <int> responsibleTeams;
        for(int i = 0; i<tot_teams; i++){

            for(int j = i+1; j<tot_teams; j++){
                if(i == x || j == x)
                    continue;   // ignoring the edges from sou to the node x

                if(graph[0][index_mat[i][j]] > 0)   // still flow remaining
                    responsibleTeams.push(i);
            }

        }
        // bonus part
    }
}

/*
4
Atlanta       83 71  8  0 1 6 1
Philadelphia  80 79  3  1 0 0 2
New_York      78 78  6  6 0 0 0
Montreal      77 82  3  1 2 0 0

Philadelphia is eliminated.
Montreal is eliminated.
*/


