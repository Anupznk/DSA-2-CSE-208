#include<bits/stdc++.h>
using namespace std;

class ResultSet {
public:
    int parent;
    double weight;

    ResultSet(){
        parent = -1;
        weight = 0.0;
    }
};

class Graph{
    int v;
    vector<int> parent;
    vector<pair<double, pair<int, int> > > adjKruskal;
    vector<pair<int, int> > tree;
    vector<vector<pair<int, double> > > adjPrim;
    vector<ResultSet> resultSet;

public:
    Graph(int v){
        this->v = v;
        parent.resize(v, -1);
        adjPrim.resize(v, vector<pair<int, double> >());
        resultSet.resize(v);
    }

    void addEdge(double wt, int v1, int v2){
        adjKruskal.push_back(make_pair(wt, pair<int, int>(v1, v2)));
        adjPrim[v1].push_back(make_pair(v2, wt));
        adjPrim[v2].push_back(make_pair(v1, wt));
    }

    void clearMST(){
        tree.clear();
        parent.clear();
    }

    int findSet(int i){
        if(parent[i] == i)
            return i;
        else
            return findSet(parent[i]);
    }

    double MST_Kruskal() {
        // O(E lg E)
      double result = 0.0;

      int i;
      for (i = 0; i<v; i++){
        parent[i] = i;
      }

      sort(adjKruskal.begin(), adjKruskal.end()); // O(E lg E)
      for (i = 0; i<adjKruskal.size(); i++){
        int u, v;
        int v1, v2;
        v1 = adjKruskal[i].second.first;
        v2 = adjKruskal[i].second.second;
        u = findSet(v1);   // O(lg V)
        v = findSet(v2);
        if(u != v){ // not on the same disjoint set, meaning they do no form cycle
            tree.push_back(pair<int, int> (v1, v2));
            result += adjKruskal[i].first;
            parent[u] = parent[v];  // assigning to the same disjoint set
        }
      }
      cout << "List of edges selected by Kruskal's: ";
      cout<<"{";
      for (i = 0; i<tree.size(); i++){
        cout << "(" << tree[i].first << ", " << tree[i].second << ")";
        if (i < tree.size() -1)
            cout << ",";
      }
      cout<<"}";
      cout<<endl;

      return result;
    }

    double MST_Prim(int root){
        // O(E lg V)
        double result = 0.0;
        double key[v];
        priority_queue< pair<int, int>, vector <pair<int, int> > , greater<pair<int, int> > > pq; // greater<pair<int, int> > for min heap
        for(int i = 0; i<v; i++){
            key[i] = INT_MAX;   // for min heap
            parent[i] = -1;
        }

        vector<bool> mstSet(v, false);
        key[root] = 0;
        pq.push(make_pair(key[root], root));

        while(!pq.empty()){ // O(E lg V) + O(V lg V)
            int currVertex = pq.top().second; // O(lg V)
            pq.pop();

            if (mstSet[currVertex])
                continue;   // ignoring the vertex that is already in the MST

            for(int i = 0; i<adjPrim[currVertex].size(); i++){
                int v = adjPrim[currVertex][i].first;
                int wt = adjPrim[currVertex][i].second;

                if (!mstSet[v] && key[v] > wt){ // O(E/V)
                    key[v] = wt;
                    pq.push(make_pair(key[v], v));  // O(lg V)
                    parent[v] = currVertex;
                    resultSet[v].parent = currVertex;
                    resultSet[v].weight = wt;
                }
            }

            mstSet[currVertex] = true;
        }

        cout << "List of edges selected by Prim's: ";
        cout<<"{";
        for (int i = 1; i<v; i++){
            result += resultSet[i].weight;
            cout << "(" << parent[i] << ", " << i << ")";
            if (i < v-1)
                cout << ",";
        }
        cout<<"}";
        cout<<endl;

        return result;
    }
};


int main() {
    int v, e;
    fstream f("mst.in");

    string word;
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());
    Graph graph(v);

    while(!f.eof()){
        int v1, v2;
        float wt;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());
        f >> word;
        wt = atof(word.c_str());

        graph.addEdge(wt, v1, v2);
    }
    f.close();

  cout << "Cost of the minimum spanning tree using Kruskal's : " << graph.MST_Kruskal() << endl;
  graph.clearMST();
  cout << "Cost of the minimum spanning tree using Prim's : " << graph.MST_Prim(0) << endl;

}

/*

6 9
0 1 1.0
1 3 5.0
3 0 3.0
3 4 1.0
1 4 1.0
1 2 6.0
5 2 2.0
2 4 4.0
5 4 4.0

9 14
0 1 4
1 2 8
2 3 7
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
7 8 7
6 8 6
8 2 2
2 5 4
1 7 11
0 7 8

*/








