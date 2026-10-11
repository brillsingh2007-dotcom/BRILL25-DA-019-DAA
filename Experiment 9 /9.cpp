#include <stdio.h>

#define INF 99999
#define MAX 100

int main()
{
    int n, graph[MAX][MAX];
    int distance[MAX], visited[MAX];
    int i, j, source, count, min, u;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if (i == j)
                graph[i][j] = 0;
            else if (graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    for (i = 0; i < n; i++)
    {
        distance[i] = graph[source][i];
        visited[i] = 0;
    }

    distance[source] = 0;
    visited[source] = 1;

    for (count = 1; count < n; count++)
    {
        min = INF;
        u = -1;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] && distance[i] < min)
            {
                min = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] &&
                graph[u][i] != INF &&
                distance[u] != INF &&
                distance[u] + graph[u][i] < distance[i])
            {
                distance[i] = distance[u] + graph[u][i];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", source);

    for (i = 0; i < n; i++)
    {
        if (distance[i] == INF)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, distance[i]);
    }

    return 0;
}
