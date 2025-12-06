#include <stdio.h>
#include "maxflow.h"

/*
   Experiment 7: Maxflow–Mincut Theorem

   Real-time Scenario:
   Water distribution network from a source reservoir (s)
   to a city treatment plant (t). Each edge capacity[i][j] is
   the maximum water (e.g., liters/second) that pipe i→j can carry.

   We implement Ford–Fulkerson (using DFS) to find:
   - Maximum flow from s to t
   - Minimum cut: set of edges whose total capacity equals max flow
*/

static int dfsPath(int V, int rGraph[MAX_VERTICES][MAX_VERTICES],
                   int u, int t, int visited[MAX_VERTICES], int parent[MAX_VERTICES])
{
    visited[u] = 1;
    if (u == t)
        return 1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && rGraph[u][v] > 0)
        {
            parent[v] = u;
            if (dfsPath(V, rGraph, v, t, visited, parent))
                return 1;
        }
    }
    return 0;
}

void maxFlowMinCut(int V, int capacity[MAX_VERTICES][MAX_VERTICES], int s, int t)
{
    int rGraph[MAX_VERTICES][MAX_VERTICES]; // residual capacities

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

    printf("\n=== Ford–Fulkerson for Max Flow (Source = %d, Sink = %d) ===\n", s, t);

    // Augment the flow while there is a path from s to t
    while (1)
    {
        int visited[MAX_VERTICES] = {0};
        for (int i = 0; i < V; i++)
            parent[i] = -1;

        if (!dfsPath(V, rGraph, s, t, visited, parent))
            break; // no more augmenting path

        // Find minimum residual capacity along the path found
        int pathFlow = INF;
        int v = t;
        while (v != s)
        {
            int u = parent[v];
            if (u == -1)
                break;
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
            rGraph[v][u] += pathFlow;
            v = u;
        }

        maxFlow += pathFlow;

        // Print augmenting path
        printf("\nAugmenting Path %d (flow = %d): ", iteration++, pathFlow);
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
        printf("\nCurrent Max Flow = %d\n", maxFlow);
    }

    printf("\n=== Final Maximum Flow from %d to %d = %d ===\n", s, t, maxFlow);

    // Now find vertices reachable from s in residual graph
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES];
    int top = -1;

    // Simple DFS using stack
    stack[++top] = s;
    visited[s] = 1;

    while (top >= 0)
    {
        int u = stack[top--];
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                visited[v] = 1;
                stack[++top] = v;
            }
        }
    }

    // Print Min-Cut edges: u in reachable set, v not reachable, original capacity > 0
    int minCutCapacity = 0;
    printf("\n=== Min-Cut Edges (S-side → T-side) ===\n");
    printf("Edge\tCapacity\n");
    printf("-----------------\n");

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (visited[u] && !visited[v] && capacity[u][v] > 0)
            {
                printf("%d -> %d\t%d\n", u, v, capacity[u][v]);
                minCutCapacity += capacity[u][v];
            }
        }
    }
    printf("-----------------\n");
    printf("Sum of Min-Cut capacities = %d\n", minCutCapacity);
    printf("According to Maxflow–Mincut Theorem: Max Flow (%d) = Min Cut (%d)\n",
           maxFlow, minCutCapacity);
}
