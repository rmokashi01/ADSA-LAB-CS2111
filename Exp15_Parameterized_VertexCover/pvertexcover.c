#include <stdio.h>
#include <string.h>
#include "pvertexcover.h"

/*
    Experiment 15: Parameterized Algorithm
    Problem: k-Vertex Cover (Parameter = k)

    Real-time Scenario:
    Network Security Hardening

    - Vertices = Servers / Systems
    - Edges    = Communication links
    - Goal     = Choose at most k machines to monitor
                 such that every link has at least one monitored endpoint.

    This is solved via a Parameterized Algorithm:

    Running Time ≈ O(2^k * n^2), which is efficient
    when k is small even if n is moderate.
*/

// Helper: find an uncovered edge (u, v)
// i.e., adj[i][j] == 1 and both i, j are not in chosen[]
static int findUncoveredEdge(Graph *g, int chosen[],
                             int *u, int *v)
{
    for (int i = 0; i < g->n; i++)
    {
        for (int j = i + 1; j < g->n; j++)
        {
            if (g->adj[i][j] == 1 && !chosen[i] && !chosen[j])
            {
                *u = i;
                *v = j;
                return 1;   // Found an uncovered edge
            }
        }
    }
    return 0;               // All edges are covered
}

// Recursive Parameterized Vertex Cover
static int vertexCoverRec(Graph *g, int k, int chosen[], int solution[])
{
    int u, v;

    // If all edges are covered -> success
    if (!findUncoveredEdge(g, chosen, &u, &v))
    {
        // Copy current chosen[] to final solution
        for (int i = 0; i < g->n; i++)
            solution[i] = chosen[i];
        return 1;
    }

    // If k is 0 but some edge remains -> fail
    if (k == 0)
        return 0;

    // Branch 1: include u in the vertex cover
    chosen[u] = 1;
    if (vertexCoverRec(g, k - 1, chosen, solution))
        return 1;
    chosen[u] = 0;  // backtrack

    // Branch 2: include v in the vertex cover
    chosen[v] = 1;
    if (vertexCoverRec(g, k - 1, chosen, solution))
        return 1;
    chosen[v] = 0;  // backtrack

    // Neither branch worked
    return 0;
}

int findVertexCover(Graph *g, int k, int solution[])
{
    int chosen[MAX_VERTICES];

    // Initialize
    for (int i = 0; i < g->n; i++)
    {
        chosen[i] = 0;
        solution[i] = 0;
    }

    printf("\n=== Parameterized Vertex Cover (k = %d) ===\n", k);
    printf("Running bounded search tree algorithm with branching.\n");

    int result = vertexCoverRec(g, k, chosen, solution);

    if (!result)
    {
        printf("\nNo vertex cover of size ≤ %d exists for this graph.\n", k);
    }
    else
    {
        printf("\nA vertex cover of size ≤ %d was found.\n", k);
        printf("Vertices included in vertex cover (by index): ");
        for (int i = 0; i < g->n; i++)
        {
            if (solution[i])
                printf("%d ", i);
        }
        printf("\n");
    }

    return result;
}
