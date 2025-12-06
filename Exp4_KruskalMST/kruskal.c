#include <stdio.h>
#include "kruskal.h"

#define MAX_VERTICES 100

// Disjoint Set (Union-Find) parent array
int parent[MAX_VERTICES];

// Initialize each vertex as its own parent
void makeSet(int V)
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
    }
}

// Find with simple path compression
int findSet(int v)
{
    if (parent[v] == v)
        return v;
    parent[v] = findSet(parent[v]);  // path compression
    return parent[v];
}

// Union of two sets
void unionSet(int a, int b)
{
    a = findSet(a);
    b = findSet(b);
    if (a != b)
    {
        parent[b] = a;
    }
}

// Simple bubble sort by weight
void sortEdgesByWeight(Edge edges[], int E)
{
    for (int i = 0; i < E - 1; i++)
    {
        for (int j = 0; j < E - 1 - i; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal's MST Algorithm
void kruskalMST(int V, int E, Edge edges[])
{
    Edge mst[V]; // to store MST edges (maximum V-1 edges)
    int mstEdgeCount = 0;
    int totalCost = 0;

    // Sort all edges by increasing weight
    sortEdgesByWeight(edges, E);

    printf("\nEdges sorted by weight (candidate roads):\n");
    for (int i = 0; i < E; i++)
    {
        printf("%d -- %d  (cost = %d)\n", edges[i].src, edges[i].dest, edges[i].weight);
    }

    makeSet(V);

    printf("\n=== Selecting edges for Minimum Spanning Tree (Kruskal) ===\n");

    for (int i = 0; i < E && mstEdgeCount < V - 1; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        int setU = findSet(u);
        int setV = findSet(v);

        printf("\nConsidering edge %d -- %d (cost = %d)\n", u, v, w);

        if (setU != setV)
        {
            printf(" → Accepted (no cycle formed)\n");
            mst[mstEdgeCount++] = edges[i];
            totalCost += w;
            unionSet(setU, setV);
        }
        else
        {
            printf(" → Rejected (would form a cycle)\n");
        }
    }

    printf("\n=== Final Minimum Spanning Tree (Road Network) ===\n");
    printf("Edge\tCost\n");
    printf("-----------------\n");
    for (int i = 0; i < mstEdgeCount; i++)
    {
        printf("%d -- %d\t%d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
    printf("-----------------\n");
    printf("Total Minimum Cost = %d\n", totalCost);

    if (mstEdgeCount != V - 1)
    {
        printf("\nNote: Graph was not fully connected, MST could not include all vertices.\n");
    }
}
