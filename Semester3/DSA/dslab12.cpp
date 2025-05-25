/*
Implement a graph and find transpose of a graph where Transpose of a directed graph 
G is another directed graph on the same set of vertices with all of the edges
reversed compared to the orientation of the corresponding edges in G.
That is, if G contains an edge (u, v) then the converse/transpose/reverse of G contains an edge (v, u) and vice versa.
Implement it with the help of adjacency list and adjacency matrix
*/

#include<iostream>
using namespace std;

const int max_vertices=5;

struct Graph{
    int V;
    int adjMatrix[max_vertices][max_vertices];
    int adjList[max_vertices][max_vertices];
    int adjListSize[max_vertices];

    Graph(int v){
        V=v;
        for(int i=0;i<V;i++){
            adjListSize[i]=0;
            for(int j=0;j<V;j++){
                adjMatrix[i][j]=0;
                adjList[i][j]=-1;
            }
        }
    }

    void addEdge(int u,int v){
        if(u<V && v<V){
            adjMatrix[u][v]=1;
            adjList[u][adjListSize[u]++]=v;
        }
    }

    void PrintAdjList(){
        for(int i=0;i<V;i++){
            cout<<i<<"->";
            for(int j=0;j<adjListSize[i];j++){
                cout<<adjList[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void PrintAdjMatrix(){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                cout<<adjMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    Graph TransposeList(){
        Graph Transpose(V);
        for(int i=0;i<V;i++){
            for(int j=0;j<adjListSize[i];j++){
                Transpose.addEdge(adjList[i][j],i);
            }
        }
        return Transpose;
    }

    Graph TransposeMatrix(){
        Graph Transpose(V);
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(adjMatrix[i][j]==1){
                    Transpose.addEdge(j,i);
                }
            }
        }
        return Transpose;
    }
};

int main(){
    Graph g(max_vertices);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(2,1);

    cout << "Original Graph:" << endl;
    g.PrintAdjList();
    g.PrintAdjMatrix();

    // Get transpose graphs
    Graph transposeList = g.TransposeList();
    Graph transposeMatrix = g.TransposeMatrix();

    cout << "\nTranspose Graph (Adjacency List):" << endl;
    transposeList.PrintAdjList();

    cout << "\nTranspose Graph (Adjacency Matrix):" << endl;
    transposeMatrix.PrintAdjMatrix();
    return 0;
}

