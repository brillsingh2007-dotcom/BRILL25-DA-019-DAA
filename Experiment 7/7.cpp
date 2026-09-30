```c
#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int disc[MAX];
int low[MAX];
int parent[MAX];
int articulation[MAX];

int timer = 0;
int vertices;

// DFS function to find articulation points
void DFS(int u)
{
    int children = 0;

    visited[u] = 1;
    disc[u] = low[u] = ++timer;

    for (int v = 0; v < vertices; v++)
    {
        if (graph[u][v])
        {
            // If vertex v is not visited
            if (!visited[v])
            {
                children++;
                parent[v] = u;

                DFS(v);

                // Update low value of u
                if (low[v] < low[u])
                    low[u] = low[v];

                // Check if u is an articulation point
                if (parent[u] == -1 && children > 1)
                    articulation[u] = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    articulation[u] = 1;
            }

            // Back edge
            else if (v != parent[u])
            {
                if (disc[v] < low[u])
                    low[u] = disc[v];
            }
        }
    }
}

// Function to find articulation points
void findArticulationPoints()
{
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        articulation[i] = 0;
    }

    timer = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
            DFS(i);
    }

    printf("\nCut Vertices (Articulation Points):\n");

    int found = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (articulation[i])
        {
            printf("Vertex %d\n", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("No articulation points found.\n");
}

int main()
{
    int edges;
    int u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize graph
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph[i][j] = 0;
        }
    }

    printf("\nEnter edges (source destination):\n");

    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        graph[u - 1][v - 1] = 1;
        graph[v - 1][u - 1] = 1;
    }

    findArticulationPoints();

    return 0;
}
```
