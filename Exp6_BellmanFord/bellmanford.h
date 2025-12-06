#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#define MAX_EDGES 200
#define MAX_VERTICES 50
#define INF 99999

// Edge contains: from-currency → to-currency with weight = -log(rate)
typedef struct
{
    int src;
    int dest;
    float weight;
} Edge;

// Bellman-Ford Algorithm for Arbitrage Detection
void bellmanFord(int V, int E, Edge edges[], int src);

#endif
