#include <stdio.h>
#include "edmonds_karp.h"

/*
    Experiment 8: Edmonds–Karp Implementation of Ford–Fulkerson

    Real-time Scenario:
    Hospital Oxygen Supply Network

    Each vertex = oxygen junction / building / unit in the hospital.
    Each edge capacity[u][v] = maximum oxygen flow (e.g., liters per minute)
    that the pipeline u -> v can carry.

    We use BFS (Edmonds–Karp) to find:
    - Maximum oxygen flow from source (central tank) to sink (critical unit).
*/

static int bfs(int V, int rGraph[MAX_VERTICES][MAX_VERTICES],
               int s, int t, int parent[MAX_VERTICES])
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front < rear)
    {
        int u = queue[front++];

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;

                if (v == t)
                    return 1;  // sink reached
            }
        }
    }

    return 0;  // no path from s to t
}

void edmondsKarp(int V, int capacity[MAX_VERTICES][MAX_VERTICES], int s, int t)
{
    int rGraph[MAX_VERTICES][MAX_VERTICES];

    // Initialize residual graph as original capacities
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            rGraph[i][j] = capacity[i][j];
        }
    }

    int parent[MAX_VERTICES];
    int maxFlow = 0;
    int iteration = 1;

    printf("\n=== Edmonds–Karp (BFS) for Max Oxygen Flow ===\n");
    printf("Source = %d, Sink = %d\n", s, t);

    // While there is an augmenting path from s to t
    while (bfs(V, rGraph, s, t, parent))
    {
        // Find minimum residual capacity along the path found
        int pathFlow = INF;
        int v = t;

        while (v != s)
        {
            int u = parent[v];
            if (rGraph[u][v] < pathFlow)
                pathFlow = rGraph[u][v];
            v = u;
        }

        // Update residual capacities along the path
        v = t;
        while (v != s)
        {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;   // reverse edge
            v = u;
        }

        maxFlow += pathFlow;

        // Print path
        printf("\nAugmenting Path %d (oxygen flow added = %d): ", iteration++, pathFlow);
        int pathVertices[MAX_VERTICES];
        int pathLen = 0;
        v = t;
        while (v != -1)
        {
            pathVertices[pathLen++] = v;
            v = parent[v];
        }
        for (int i = pathLen - 1; i >= 0; i--)
        {
            printf("%d", pathVertices[i]);
            if (i != 0)
                printf(" -> ");
        }
        printf("\nCurrent Maximum Oxygen Flow = %d\n", maxFlow);
    }

    printf("\n=== Final Maximum Oxygen Flow from %d to %d = %d units ===\n", s, t, maxFlow);
}
