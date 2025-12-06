#include <stdio.h>
#include <math.h>
#include "bellmanford.h"

/*
   Currency Arbitrage Detection using Bellman-Ford

   Each currency = vertex
   Exchange rate = edge

   We transform:
   weight = -log(rate)

   Arbitrage exists when:
   cycle weight sum < 0 (negative weight cycle)
*/

void bellmanFord(int V, int E, Edge edges[], int src)
{
    float dist[MAX_VERTICES];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[src] = 0;

    printf("\n=== Bellman-Ford for Currency Arbitrage (Source = %d) ===\n", src);

    // Step 2: Relax edges V-1 times
    for (int i = 1; i <= V - 1; i++)
    {
        int updated = 0;
        printf("\nIteration %d:\n", i);

        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            float w = edges[j].weight;

            if (dist[u] + w < dist[v])
            {
                printf("Updating %d -> %d : %.4f -> %.4f\n", 
                        u, v, dist[v], dist[u] + w);
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }

        if (!updated)
        {
            printf("No update in this iteration. Early stop.\n");
            break;
        }
    }

    // Step 3: Check for negative weight cycle (arbitrage)
    printf("\nChecking for negative weight cycles...\n");

    for (int j = 0; j < E; j++)
    {
        int u = edges[j].src;
        int v = edges[j].dest;
        float w = edges[j].weight;

        if (dist[u] + w < dist[v])
        {
            printf("\n⚠ Arbitrage Detected! (Negative cycle found)\n");
            printf("Profit can be made by cycling through currencies.\n");
            return;
        }
    }

    printf("\nNo arbitrage opportunity found.\n");
}
