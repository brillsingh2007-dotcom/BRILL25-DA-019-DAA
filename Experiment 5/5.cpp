#include <iostream>
using namespace std;

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int disc[MAX];
int low[MAX];
int parent[MAX];
bool articulation[MAX];

int timer = 0;
int n;

// DFS to find articulation points
void DFS(int u)
{
    visited[u] = 1;
    disc[u] = low[u] = ++timer;

    int children = 0;

    for (int v = 0; v < n; v++)
    {
        if (graph[u][v] == 0)
            continue;

        // If v is not visited
        if (!visited[v])
        {
            children++;
            parent[v] = u;

            DFS(v);

            // Update low value
            low[u] = min(low[u], low[v]);

            // Case 1: u is root
            if (parent[u] == -1 && children > 1)
                articulation[u] = true;

            // Case 2: u is not root
            if (parent[u] != -1 && low[v] >= disc[u])
                articulation[u] = true;
        }

        // Back edge
        else if (v != parent[u])
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main()
{
    int edges;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> edges;

    // Initialize graph
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        articulation[i] = false;

        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    cout << "Enter edges (source destination):\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u - 1][v - 1] = 1;
        graph[v - 1][u - 1] = 1;
    }

    // Run DFS for all components
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            DFS(i);
    }

    cout << "\nCut Vertices (Articulation Points):\n";

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        if (articulation[i])
        {
            cout << "Vertex " << i + 1 << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No articulation points found." << endl;

    return 0;
}
