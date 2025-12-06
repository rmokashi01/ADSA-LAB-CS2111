#include <stdio.h>
#include "dijkstra.h"

/*
   Real-time scenario:
   GPS Navigation System for a City

   Each vertex = Area / Junction in the city
   Each edge weight = Road distance or travel time between two points

   Goal: From a given SOURCE location, find shortest paths to all other locations.
*/

// Helper to find vertex with minimum distance not yet visited
static int minDistance(int dist[], int visited[], int V)
{
    int min = INF;
    int min_index = -1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Recursive function to print path from source to j using parent[]
static void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        printf("%d", j);
        return;
    }

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void dijkstra(int V, int graph[MAX_VERTICES][MAX_VERTICES], int src)
{
    int dist[MAX_VERTICES];     // shortest distance from src to i
    int visited[MAX_VERTICES];  // visited set
    int parent[MAX_VERTICES];   // to reconstruct path

    // Initialize all distances as INF and visited[] as 0
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;  // distance of source to itself is 0

    printf("\n=== Dijkstra's Algorithm for GPS Navigation (Source = %d) ===\n", src);
    printf("Note: 0 in adjacency matrix means 'no direct road'.\n");

    // Main Dijkstra loop
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited, V);

        if (u == -1)
        {
            // Remaining vertices are unreachable
            break;
        }

        visited[u] = 1;

        printf("\nSelected location %d with current shortest distance = %d\n", u, dist[u]);
        printf("Relaxing roads from %d to its neighbours...\n", u);

        // Update dist[v] for all adjacent vertices of u
        for (int v = 0; v < V; v++)
        {
            int weight = graph[u][v];

            // If there is a road and v is not visited
            if (!visited[v] && weight > 0 && weight < INF)
            {
                if (dist[u] + weight < dist[v])
                {
                    printf("  Found shorter route to %d: old dist = %d, new dist = %d\n",
                           v, dist[v], dist[u] + weight);

                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    printf("\n=== Final Shortest Routes from Source %d ===\n", src);
    printf("Location\tDistance\tPath (by node index)\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INF)
        {
            printf("%d\t\tINF\t\tNo path\n", i);
        }
        else
        {
            printf("%d\t\t%d\t\t", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}
