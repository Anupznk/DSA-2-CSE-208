#include<bits/stdc++.h>
#include "min_heap.h"
using namespace std;

#define INF 0x3f3f3f3f

class Edge{
    int v1, v2;
    double wt;
public:
    Edge(int a, int b, double c){
        v1 = a;
        v2 = b;
        wt = c;
    }

    int getSou(){
        return v1;
    }

    int getDest(){
        return v2;
    }

    double getWt(){
        return wt;
    }
};

class Graph{
    vector <Edge> edges;
    int e;
    int v;
public:
    Graph(int a, int b){
        v = a;
        e = b;
    }

    void addEdge(int v1, int v2, double wt){
        Edge newEdge(v1, v2, wt);
        edges.push_back(newEdge);
    }

    Edge getEdge(int pos){
        return edges[pos];
    }

    int getNumVertices(){
        return v;
    }

    int getNumEdges(){
        return e;
    }

};

void printPath(vector <int> parent, int vertex){
    if (parent[vertex] ==  -1){
        cout << vertex << " -> ";
        return;
    }

    printPath(parent, parent[vertex]);

        cout << vertex << " -> ";
}

int bellman_ford(Graph graph, int s, int d){
    // O(|v| |E|)
    int v = graph.getNumVertices();
    int e = graph.getNumEdges();
    vector <int> len(v, INF);
    vector <int> parent(v, -1);

    len[s] = 0;

    for (int i = 1; i<v; i++){  // O(|v| |E|)
        for (int j = 0; j<e; j++){
            int u = graph.getEdge(j).getSou();
            int v = graph.getEdge(j).getDest();
            double w = graph.getEdge(j).getWt();

            if (len[u] != INF && len[u] + w < len[v]){
                len[v] = len[u] + w;
                parent[v] = u;
            }
        }
    }

    // the graph is fully relaxed
    // let's check if it can be relaxed again
    // if yes, this means there is a negative cycle

    for (int j = 0; j<e; j++){  // O(E)
        int u = graph.getEdge(j).getSou();
        int v = graph.getEdge(j).getDest();
        double w = graph.getEdge(j).getWt();

        if (len[u] != INF && len[u] + w < len[v]){
            cout << "The graph contains a negative cycle";
            return -1;
        }
    }


    cout << "The graph does not contain a negative cycle" << endl;

    if(len[d] == INF){
        printf("%d is not reachable from %d", d, s);
        exit(1);
    } else{
        cout << "Shortest path cost: " << len[d] << endl;
        printPath(parent, d);
        return len[d];
    }


}

int main(){
    int v;
    int e;
    fstream f ("bellman.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());

    Graph graph(v, e);


    vector <vector<int> > adj (v, vector<int>());
    vector <vector<double> > wt (v, vector<double>());

    for(int i=0; i<e; i++){
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

        graph.addEdge(v1, v2, w);
    }

    f >> word;
    int sou = atoi(word.c_str());
    f >> word;
    int dest = atoi(word.c_str());
    f.close();
    bellman_ford(graph, sou, dest);

}
