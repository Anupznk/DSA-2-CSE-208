#include<bits/stdc++.h>
#include "min_heap.h"
using namespace std;

#define INF 0x3f3f3f3f

void printPath(vector <int> parent, int vertex){
    if (parent[vertex] ==  -1){
        cout << vertex << " -> ";
        return;
    }

    printPath(parent, parent[vertex]);

        cout << vertex << " -> ";
}

int dijkstra(vector<vector<int> > &adj, vector<vector<double> > &wt, int s, int d){
    // O(V lg V + E lg V)
    Heap pq;
    int v = adj.size();
    vector <int> len(v, INF);
    vector <int> parent(v, -1);

    pq.insert(LenPair(0, s));
    len[s] = 0;

    while(!pq.isEmpty()){
        LenPair p = pq.getMin();
        int x = p.getVertex();
        pq.deleteKey(); // O(lg V)
        for (int i = 0; i<adj[x].size(); i++){  // O (E lg V)
            int y = adj[x][i];
            if(len[y] > len[x]+wt[x][i]){
                len[y] = len[x]+wt[x][i];
                parent[y] = x;
                pq.insert(LenPair(len[y], y));  // O(lg V)
            }
        }
    }

    if(len[d] == INF)
        return -1;
    else{
        cout << "Shortest path cost: " << len[d] << endl;
        printPath(parent, d);

        return len[d];
    }


}

int main(){
    int v;  // v = num of vertices
    int e;  // e = num of edges
    fstream f ("dijkstra.txt");
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
    }

    f >> word;
    int sou = atoi(word.c_str());
    f >> word;
    int dest = atoi(word.c_str());
    f.close();

    dijkstra(adj, wt, sou, dest);

}
