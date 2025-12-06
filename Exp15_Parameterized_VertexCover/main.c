#include <stdio.h>
#include "pvertexcover.h"

/*
    Experiment 15: Parameterized Algorithm
    Problem: k-Vertex Cover

    Application:
    - Network Security: Select limited number (k) of machines
      to monitor such that every communication link is covered.
*/

// Demo network scenario:
void loadDemoNetwork(Graph *g, const char *names[])
{
    /*
        Example Graph (5 vertices):

        0: Gateway
        1: Web Server
        2: Database Server
        3: File Server
        4: Backup Server

        Edges:
        0 - 1
        0 - 2
        1 - 3
        2 - 3
        3 - 4

        A vertex cover of size 2 exists:
        e.g., {0, 3}
    */

    g->n = 5;

    static const char *localNames[] = {
        "Gateway",
        "Web Server",
        "Database Server",
        "File Server",
        "Backup Server"
    };

    for (int i = 0; i < g->n; i++)
        names[i] = localNames[i];

    // Initialize adjacency matrix to 0
    for (int i = 0; i < g->n; i++)
        for (int j = 0; j < g->n; j++)
            g->adj[i][j] = 0;

    // Undirected edges
    g->adj[0][1] = g->adj[1][0] = 1;
    g->adj[0][2] = g->adj[2][0] = 1;
    g->adj[1][3] = g->adj[3][1] = 1;
    g->adj[2][3] = g->adj[3][2] = 1;
    g->adj[3][4] = g->adj[4][3] = 1;

    printf("\nLoaded Demo Network Scenario:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("Vertex %d -> %s\n", i, names[i]);
    }
}

// Custom graph input
void loadCustomGraph(Graph *g)
{
    printf("\nEnter number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &g->n);

    if (g->n <= 0 || g->n > MAX_VERTICES)
    {
        printf("Invalid number of vertices.\n");
        g->n = 0;
        return;
    }

    printf("\nEnter adjacency matrix (0 or 1) for an undirected graph:\n");
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            printf("Edge %d-%d (0/1): ", i, j);
            scanf("%d", &g->adj[i][j]);
        }
    }

    // Optional: make symmetric (ensure undirected)
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            if (g->adj[i][j] || g->adj[j][i])
            {
                g->adj[i][j] = g->adj[j][i] = 1;
            }
        }
    }
}

int main()
{
    int choice;
    Graph g;
    int k;
    int solution[MAX_VERTICES];
    const char *names[MAX_VERTICES];

    while (1)
    {
        printf("\n===== Experiment 15 – Parameterized Algorithm (k-Vertex Cover) =====\n");
        printf("1. Use Demo Network Security Scenario\n");
        printf("2. Enter Custom Graph\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoNetwork(&g, names);
        }
        else if (choice == 2)
        {
            loadCustomGraph(&g);
            // For custom graph, simple numeric names
            for (int i = 0; i < g.n; i++)
                names[i] = NULL; // we'll print just indices
        }
        else if (choice == 3)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        if (g.n == 0)
        {
            printf("Graph is empty. Try again.\n");
            continue;
        }

        printf("\nEnter parameter k (max number of vertices allowed in cover): ");
        scanf("%d", &k);

        int res = findVertexCover(&g, k, solution);

        if (res)
        {
            printf("\nSelected vertices in vertex cover (detailed):\n");
            for (int i = 0; i < g.n; i++)
            {
                if (solution[i])
                {
                    if (names[i] != NULL)
                        printf("Vertex %d (%s)\n", i, names[i]);
                    else
                        printf("Vertex %d\n", i);
                }
            }
        }
    }

    return 0;
}
