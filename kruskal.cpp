#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define edge pair<int, int>

class Graph {
   private:
  vector<pair<int, edge> > G;  // graph
  vector<pair<int, edge> > T;  // mst
  int *parent;
  int V;  // number of vertices/nodes in graph
   public:
  Graph(int V);
  void AddWeightedEdge(int u, int v, int w);
  int find_set(int i);
  void union_set(int u, int v);
  void kruskal();
  void print();
};
Graph::Graph(int V) {
  parent = new int[V];

  //i 0 1 2 3 4 5
  //parent[i] 0 1 2 3 4 5
  for (int i = 0; i < V; i++)
    parent[i] = i;

  G.clear();
  T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
  G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
  // If i is the parent of itself
  if (i == parent[i])
    return i;
  else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
    return find_set(parent[i]);
}
void Graph::union_set(int u, int v) {
  parent[u] = parent[v];
}
void Graph::kruskal() {
  int i, uRep, vRep;
  sort(G.begin(), G.end());  // increasing weight
  for (i = 0; i < G.size(); i++) {
    uRep = find_set(G[i].second.first);
    vRep = find_set(G[i].second.second);
    if (uRep != vRep) {
      T.push_back(G[i]);  // add to tree
      union_set(uRep, vRep);
    }
  }
}
//      0
//      |
//      1--5  
//      |
//      2--6       2 is parent
//      |
//      3--7       3 is parent
//      |
//      4
void Graph::print() {
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < T.size(); i++) {
    cout << T[i].second.first << " - " << T[i].second.second << " : "
       << T[i].first;
    cout << endl;
  }
}
int main()
{
    int vertices;
    int edges;
    ifstream in;
    in.open("kruskal.txt");
    string str;
    getline(in, str);
    stringstream ve(str);
    string n;
    getline(ve, n, ',');
    vertices = stoi(n);
    cout << "Total vertices are : " << vertices << endl;
    getline(ve, n);
    edges = stoi(n);
    cout << "Total edges are : " << edges << endl;
    Graph g1(vertices);
    int v1, v2, weight;
    for (int i = 0; i < edges; i++)
    {
        getline(in, str);
        stringstream ss(str);
        string num;
        getline(ss, num, ',');
        v1 = stoi(num);
        cout << v1 << " ";
        getline(ss, num, ',');
        v2 = stoi(num);
        cout << v2 << " ";
        getline(ss, num, ',');
        weight = stoi(num);
        cout << weight << " ";
        cout << endl;
        g1.AddWeightedEdge(v1, v2, weight);
        g1.AddWeightedEdge(v2, v1, weight);
    }
    g1.kruskal();
    cout << "==============" << endl;
    g1.print();
    cout << "==============" << endl;
    return 0;
}