#include<bits/stdc++.h>
#include "min_heap.h"
using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

// O(V+E) for cycle detection

bool isCyclicDirected(vector< vector<int> > adj, vector<int> & color, int vertex){
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

void lexicoToposort(vector< vector<int> > adj, int v, vector<int> inDeg){
    // O(V X E)
    queue<int> s;
    for (int i = 0; i < v; i++){ //taking the vertices in lexicographical order
        if (inDeg[i] == 0)
            s.push(i);
    }

    vector<int> toposorted;

    while (!s.empty()) {    // O(V X E)
        int u = s.front();
        s.pop();
        toposorted.push_back(u);

        for (int i = 0; i<adj[u].size(); i++){  // O(E)
            int currVertex = adj[u][i];
            inDeg[currVertex]--;
            if (inDeg[currVertex] == 0)
                s.push(currVertex);
        }
    }

    for (int i = 0; i < toposorted.size(); i++)
        cout << toposorted[i] << " ";
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

    vector<int> inDeg (v, 0);

    while(!f.eof()){    // O(n log n)
        int v1, v2;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());

        adj[v1].push_back(v2);
        inDeg[v2]++;
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

    lexicoToposort(adj, v, inDeg);
    f.close();

}






