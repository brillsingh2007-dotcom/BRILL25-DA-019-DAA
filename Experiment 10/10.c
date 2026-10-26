```c
#include <stdio.h>
#include <limits.h>

#define MAX 100

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, struct Edge edges[], int source) {
    int dist[MAX];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < V; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }

        if (!updated)
            break;
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if (dist[u] != INT_MAX &&
            dist[u] + w < dist[v]) {
            printf("\nNegative-weight cycle detected!\n");
            return;
        }
    }

    printf("\nVertex\tShortest Distance from Source\n");

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d\tUnreachable\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    int V, E, source;
    struct Edge edges[MAX * MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    if (V <= 0 || V > MAX || E < 0 ||
        E > MAX * MAX) {
        printf("Invalid graph size!\n");
        return 1;
    }

    printf("Enter edges (source destination weight):\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);

        if (edges[i].src < 0 || edges[i].src >= V ||
            edges[i].dest < 0 || edges[i].dest >= V) {
            printf("Invalid vertex!\n");
            return 1;
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= V) {
        printf("Invalid source vertex!\n");
        return 1;
    }

    bellmanFord(V, E, edges, source);

    return 0;
}
```
