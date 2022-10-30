#include<bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
const int MAX_VERTEX = 100;
int parent [MAX_VERTEX][MAX_VERTEX];

void printPath(int v1, int v2){
    if(v1 != v2)
        printPath(v1, parent[v1][v2]);
    cout << v2 << " ";
}

void allPairShortestPath(int v, int graph [][MAX_VERTEX]){
    //  O(n^3)
    int distArr [v][v];

    int i, j, k;
    for (i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            distArr[i][j] = graph[i][j];
            parent[i][j] = i;
        }
    }

    for (k = 0; k < v; k++) {
        for (i = 0; i < v; i++) {
            for (j = 0; j < v; j++) {
                if (distArr[i][j] > (distArr[i][k] + distArr[k][j]) // testing path from i to j via k
                    && distArr[i][k]!=INF && distArr[k][j]!=INF ){
                        distArr[i][j] = distArr[i][k] + distArr[k][j];
                        parent[i][j] = parent[k][j];
                }
            }
        }
    }

    // if dist of any vertex from itself is neg, then there is a neg cycle
    bool hasNegCycle = false;
    for(i = 0; i<v; i++){
        if(distArr[i][i] < 0)
            hasNegCycle = true;
    }
    if(hasNegCycle)
        cout << "Has negative cycle" << endl;
    else
        cout << "No negative cycle" << endl;

    cout << "Shortest distance matrix" << endl;
    for (i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            if (distArr[i][j] == INF)
                cout << "INF" << "\t";
            else
                cout << distArr[i][j] << "\t";
        }
        cout << endl;
    }

//    printPath(3, 4);

}

int main(){
    int v;
    int e;
    fstream f ("all-pair-shorteset-path.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string word;
    f >> word;
    v = atoi(word.c_str());
    f >> word;
    e = atoi(word.c_str());

    int graph [MAX_VERTEX][MAX_VERTEX];
    for (int i = 0; i<v; i++){
        for (int j = 0; j<v; j++){
            if (i ==j)
                graph[i][j] = 0;    // for self loop
            else
                graph[i][j] = INF;
        }
    }

    for(int i=0; i<e; i++){
        int v1, v2;
        int w;
        f >> word;
        v1 = atoi(word.c_str());
        f >> word;
        v2 = atoi(word.c_str());
        f >> word;
        w = atoi(word.c_str());

        graph[v1-1][v2-1] = min(graph[v1-1][v2-1], w);  // for parallel edges
        // nodes starting from 1
    }

    f.close();
    allPairShortestPath(v, graph);

}


/*

4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9

4 4
1 2 5
2 3 3
3 4 1
1 4 10

negative cycle
4 4
0 1 1
1 2 -1
2 3 -1
3 0 -1
0 3

*/
