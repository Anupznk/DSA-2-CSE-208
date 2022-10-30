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
    vector< vector<pair<int, int> > > tree;
    vector<vector<pair<int, double> > > adjPrim;
    vector<ResultSet> resultSet;

public:
    Graph(int v){
        this->v = v;
        parent.resize(v, -1);
        adjPrim.resize(v, vector<pair<int, double> >());
        tree.resize(v, vector<pair<int, int> >());    // will keep track of all the spanning trees including MST
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
        parent.resize(v, -1);
    }

    int findSet(int i){
        if(parent[i] == i)
            return i;
        else
            return findSet(parent[i]);
    }

    void printTree(int treeIdx){
        cout << "List of edges selected: ";
        cout<<"{";
        for (int j = 0; j<tree[treeIdx].size(); j++){
            int v1 = tree[treeIdx][j].first;
            int v2 = tree[treeIdx][j].second;
            cout << "(" << v1 << ", " << v2 << ")";
            if (j < tree[treeIdx].size() -1)
                cout << ",";
        }
        cout<<"}";
        cout<<endl;
    }

    double second_MST_Kruskal() {   // O(V x E)
        // O(E lg E)
      vector<double> result (v, 0.0);

      int i, j;
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
            tree[0].push_back(pair<int, int> (v1, v2));
            result[0] += adjKruskal[i].first;
            parent[u] = parent[v];  // assigning to the same disjoint set
        }
      }

      for (j = 0; j<tree[0].size(); j++){
        int v1 = tree[0][j].first; // v1 - v2 is one of the edges in the best MST
        int v2 = tree[0][j].second;// need to ignore one by one and call kruskal every time

        //  the edges are already sorted, no worries
        //   now need to ignore edges from the MST one by one

        for (i = 0; i<v; i++){
            parent[i] = i;
        }
        for (i = 0; i<adjKruskal.size(); i++){
            int u, v;
            int x, y;
            x = adjKruskal[i].second.first;
            y = adjKruskal[i].second.second;
            u = findSet(x);   // O(lg V)
            v = findSet(y);
            if ((x == v1 && y == v2) || (x == v2 && y == v1))
                continue;  // ignoring edges from the MST one by one
            if(u != v){ // not on the same disjoint set, meaning they do no form cycle
                tree[j+1].push_back(pair<int, int> (x, y));
                result[j+1] += adjKruskal[i].first;
                parent[u] = parent[v];  // assigning to the same disjoint set
            }
          }
      }

      int mstIdx = 0;
      cout << "best mst set:\n";
      printTree(mstIdx);

      int secondMstIdx = 1;
      double bestMstWt = result[0];
      double secBestMstWt = result[1];

      for(i = 1; i<result.size(); i++){
            if (result[i] < secBestMstWt && result[i] > bestMstWt){
                secondMstIdx = i;
                secBestMstWt = result[i];
            }
      }

      cout << "2nd best mst wt: " << secBestMstWt<< endl;
      cout << "2nd best mst set:\n";
      printTree(secondMstIdx);

      return bestMstWt;
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

  cout << "Cost of the minimum spanning tree using Kruskal's : " << graph.second_MST_Kruskal() << endl;
  graph.clearMST();


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








