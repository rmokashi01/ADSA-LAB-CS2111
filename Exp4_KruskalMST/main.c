#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

/*
   Real-time scenario:
   Designing a minimum-cost road/network between cities or campus buildings.
   Each vertex = City / Building
   Each edge   = Possible road / cable connection with given cost.
*/

void loadDemoGraph(int *V, int *E, Edge edges[])
{
    /*
       Demo Graph:
       0 - Admin Block
       1 - CSE Department
       2 - Library
       3 - Hostel
       4 - Workshop

       Edges (undirected):
       0--1 (10), 0--2 (6), 0--3 (5),
       1--3 (15), 2--3 (4), 1--4 (7), 3--4 (8)
    */

    *V = 5;
    *E = 7;

    edges[0].src = 0; edges[0].dest = 1; edges[0].weight = 10;
    edges[1].src = 0; edges[1].dest = 2; edges[1].weight = 6;
    edges[2].src = 0; edges[2].dest = 3; edges[2].weight = 5;
    edges[3].src = 1; edges[3].dest = 3; edges[3].weight = 15;
    edges[4].src = 2; edges[4].dest = 3; edges[4].weight = 4;
    edges[5].src = 1; edges[5].dest = 4; edges[5].weight = 7;
    edges[6].src = 3; edges[6].dest = 4; edges[6].weight = 8;

    printf("\nLoaded demo campus road network graph (GCEK-style).\n");
    printf("Vertices (0-4): 0-Admin, 1-CSE, 2-Library, 3-Hostel, 4-Workshop\n");
}

int main()
{
    int V, E, choice;
    Edge edges[100];  // adjust size if needed

    while (1)
    {
        printf("\n===== Experiment 4 - Kruskal's Algorithm (MST) =====\n");
        printf("1. Use Demo Campus Road Network\n");
        printf("2. Enter Custom Graph\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoGraph(&V, &E, edges);
        }
        else if (choice == 2)
        {
            printf("\nEnter number of vertices: ");
            scanf("%d", &V);

            printf("Enter number of edges: ");
            scanf("%d", &E);

            if (V <= 0 || E <= 0)
            {
                printf("Invalid graph size. Try again.\n");
                continue;
            }

            printf("\nEnter edges in the format: src dest cost\n");
            printf("(Vertices should be numbered from 0 to %d)\n", V - 1);

            for (int i = 0; i < E; i++)
            {
                printf("Edge %d: ", i + 1);
                scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
            }
        }
        else if (choice == 3)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
        {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        // Run Kruskal on the chosen graph
        kruskalMST(V, E, edges);
    }

    return 0;
}
