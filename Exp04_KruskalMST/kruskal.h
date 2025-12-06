#ifndef KRUSKAL_H
#define KRUSKAL_H

// Edge structure: represents a road between two cities/buildings
typedef struct
{
    int src;
    int dest;
    int weight;
} Edge;

void kruskalMST(int V, int E, Edge edges[]);

#endif
