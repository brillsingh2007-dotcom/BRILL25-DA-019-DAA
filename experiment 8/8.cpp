#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100

// Structure for an edge
struct Edge
{
    int u, v, weight;
};

// For Kruskal's algorithm
int parent[MAX];

// Find parent
int findParent(int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent[x]);
}

// Union two sets
void unionSet(int a, int b)
{
    a = findParent(a);
    b = findParent(b);

    if (a != b)
        parent[b] = a;
}

// Sort edges according to weight
bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// ---------------- PRIM'S ALGORITHM ----------------

void prims(int graph[MAX][MAX], int n)
{
    int selected[MAX] = {0};
    int edges = 0;
    int total = 0;

    selected[0] = 1;

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    cout << "Edge\tWeight\n";

    while (edges < n - 1)
    {
        int minimum = 99999;
        int x = -1, y = -1;

        for (int i = 0; i < n; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (!selected[j] && graph[i][j] != 0 &&
                        graph[i][j] < minimum)
                    {
                        minimum = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if (x == -1)
        {
            cout << "Graph is not connected.\n";
            return;
        }

        cout << x + 1 << " - " << y + 1
             << "\t" << minimum << endl;

        total += minimum;
        selected[y] = 1;
        edges++;
    }

    cout << "Total MST Weight = " << total << endl;
}

// ---------------- KRUSKAL'S ALGORITHM ----------------

void kruskals(Edge edges[], int n, int e)
{
    sort(edges, edges + e, compare);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int count = 0;
    int total = 0;

    cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:\n";
    cout << "Edge\tWeight\n";

    for (int i = 0; i < e && count < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (findParent(u) != findParent(v))
        {
            cout << u + 1 << " - " << v + 1
                 << "\t" << edges[i].weight << endl;

            total += edges[i].weight;

            unionSet(u, v);
            count++;
        }
    }

    if (count != n - 1)
    {
        cout << "Graph is not connected.\n";
        return;
    }

    cout << "Total MST Weight = " << total << endl;
}

// ---------------- MAIN FUNCTION ----------------

int main()
{
    int n, e;
    int graph[MAX][MAX] = {0};
    Edge edges[MAX * MAX];

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "\nEnter edges (source destination weight):\n";

    for (int i = 0; i < e; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        graph[u - 1][v - 1] = w;
        graph[v - 1][u - 1] = w;

        edges[i].u = u - 1;
        edges[i].v = v - 1;
        edges[i].weight = w;
    }

    prims(graph, n);
    kruskals(edges, n, e);

    return 0;
}
