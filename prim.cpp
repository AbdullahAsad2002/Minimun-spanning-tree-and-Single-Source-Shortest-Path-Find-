#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define INT_MAX 2147483647
using namespace std;
class graph
{
private:
    int **matrix;
    int *key;
    bool *MSTset;
    int v;

public:
    graph()
    {
        matrix = new int *[4];
        v = 4;
        for (int i = 0; i < 4; i++)
        {
            matrix[i] = new int[4];
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] = 0;
            }
            key[i] = 0;
        }
    }
    graph(int vertices)
    {
        matrix = new int *[vertices];
        v = vertices;
        for (int i = 0; i < vertices; i++)
        {
            matrix[i] = new int[vertices];
        }
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    void insertInmatrix(int v1, int v2, int e)
    {
        matrix[v1][v2] = e;
        matrix[v2][v1] = e;
    }
    void prim_mst()
    {
        int parent[v];
        key = new int[v];
        MSTset = new bool[v];
        for (int i = 0; i < v; i++)
        {
            key[i] = INT_MAX;
            MSTset[i] = false;
        }
        key[0] = 0;
        parent[0] = -1;
        for (int i = 0; i < v-1; i++)
        {
            int u = minKey(MSTset, key);
            MSTset[u] = true;
            for (int j = 0; j < v; j++)
            {
                if (matrix[u][j] != 0 && MSTset[j] == false && matrix[u][j] < key[j])
                {
                    parent[j] = u;
                    key[j] = matrix[u][j];
                }
            }
        }
        printMST(parent);
    }
    void printMST(int parent[])
    {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < v; i++)
            cout << parent[i] << " - " << i << " \t"
                 << matrix[i][parent[i]] << " \n";
    }
    int minKey(bool mstSet[], int key[])
    {
        int min = INT_MAX, minIndex;
        for (int i = 0; i < v; i++)
        {
            if (mstSet[i] == false && key[i] < min)
            {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
    void printMatrix()
    {
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    ~graph()
    {
        for (int i = 0; i < v; i++)
        {
            delete (matrix[i]);
        }
        delete matrix;
        delete key;
        delete MSTset;
    }
};
int main()
{
    int vertices;
    int edges;
    ifstream in;
    in.open("topology.txt");
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
    graph g1(vertices);
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
        g1.insertInmatrix(v1, v2, weight);
        g1.insertInmatrix(v2, v1, weight);
    }
    cout << "The Adjacency Matrix is :" << endl;
    cout << "==============" << endl;
    g1.printMatrix();
    cout << "==============" << endl;
    g1.prim_mst();
    return 0;
}