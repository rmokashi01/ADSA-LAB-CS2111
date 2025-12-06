#ifndef PVERTEXCOVER_H
#define PVERTEXCOVER_H

#define MAX_VERTICES 20
#define INF 1000000000

// Graph structure
typedef struct
{
    int n;                                // number of vertices
    int adj[MAX_VERTICES][MAX_VERTICES];  // adjacency matrix (0/1)
} Graph;

/*
    Parameterized Vertex Cover Problem

    Input:
        - Graph *g : undirected graph
        - int k    : parameter (max allowed vertices in cover)

    Output:
        - solution[] : array of size g->n
                       solution[i] = 1 if vertex i is in the vertex cover
                                     0 otherwise

    Returns:
        - 1 (true)  : if a vertex cover of size ≤ k exists
        - 0 (false) : otherwise
*/
int findVertexCover(Graph *g, int k, int solution[]);

#endif
