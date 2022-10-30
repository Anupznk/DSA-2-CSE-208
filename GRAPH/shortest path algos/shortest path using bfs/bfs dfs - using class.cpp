#include<bits/stdc++.h>
using namespace std;

class Graph{
    int v;
    vector <vector<int> > adj;
    vector<bool> vis;
    vector<int> parent;

public:
    Graph(int v){
        this->v = v;
        adj.resize(v, vector<int>());
        vis.resize(v, false);
        parent.resize(v, -1);
    }

    void addEdge(int v1, int v2){
        adj[v1].push_back(v2);
    }

    void clearVisits(){
        for(int i = 0; i<v; i++){
            vis[i] = false;
        }
    }

    void dfs(int vertex){
        if(!vis[vertex]){
            cout << vertex << " "; // reachable from "vertex"
            vis[vertex] = true;
        }

        for(int i = 0; i<adj[vertex].size(); i++){
            int currVertex = adj[vertex][i];
            if(!vis[currVertex]){
                dfs(currVertex);
            }
        }
    }

    vector<int> bfs(int vertex){
        queue<int> q;
        vector<int> dist (v, INT_MIN);

        if(!vis[vertex]){
            q.push(vertex);
            vis[vertex] = true;
//            cout << vertex << " "; // reachable from "int vertex"

            dist[vertex] = 0;
        }
        while(!q.empty()){
            int adjVertex = q.front();
            q.pop();
            for(int i=0; i<adj[adjVertex].size(); i++){
                int currVertex = adj[adjVertex][i];
                if(!vis[currVertex]){
                    q.push(currVertex);
                    vis[currVertex] = true;
                    dist[currVertex] = dist[adjVertex] + 1;
                    parent[currVertex] = adjVertex;
//                    cout << currVertex << " "; // reachable from "int vertex"
                }
            }
        }
        return dist;
    }

    int shortestDist(int sou, int dest){
        vector <int> dist;
        clearVisits();
        dist = bfs(sou);
        clearVisits();
        return dist[dest];
    }

    void printShortestPathUtil(int sou, int dest){
        if(sou ==  dest);
//            cout << sou << " ";
        else if(parent[dest] == -1){
            cout<< "Not reachable" ;
        } else {
            printShortestPath(sou, parent[dest]);
        }
        cout << dest << " ";
    }

    void printShortestPath(int sou, int dest){
        bfs(sou);
        printShortestPathUtil(sou, dest);
    }


};

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

    Graph graph(v);

    while(!f.eof()){
        int v1, v2;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());

        graph.addEdge(v1, v2);
        graph.addEdge(v2, v1);  // for undirected graph
    }
    f.close();
//
//    graph.dfs(1);
    graph.clearVisits();

    int sou = 0;
    int dest = 3;
    int shortestDist = graph.shortestDist(sou, dest);

    if(shortestDist < 0)
        cout<< "\n\nNot reachable";
    else
        cout <<  "\n\nShortest distance: " << shortestDist << endl;

    cout<< "Shortest path: "<< endl;
    graph.printShortestPath(sou, dest);

}
