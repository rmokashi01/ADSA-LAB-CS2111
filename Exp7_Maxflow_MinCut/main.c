#include <stdio.h>
#include <stdlib.h>
#include "maxflow.h"

/*
   Scenario:
   Water distribution network.

   Each vertex = junction / tank / plant
   Each directed edge capacity[u][v] = maximum water (units/sec) pipe u->v can carry.

   We want to know: maximum water that can flow from
   Source (reservoir) 's' to Sink (treatment plant) 't'.
*/

void loadDemoWaterNetwork(int *V, int capacity[MAX_VERTICES][MAX_VERTICES],
                          int *s, int *t)
{
    /*
       Classic example graph (6 vertices)

       0 - Source Reservoir
       1 - Junction A
       2 - Junction B
       3 - Junction C
       4 - Junction D
       5 - City Treatment Plant (Sink)

       Edges (u -> v) with capacities:
       0 -> 1 : 16
       0 -> 2 : 13
       1 -> 2 : 10
       2 -> 1 : 4
       1 -> 3 : 12
       3 -> 2 : 9
       2 -> 4 : 14
       4 -> 3 : 7
       3 -> 5 : 20
       4 -> 5 : 4

       This example's known max flow = 23.
    */

    *V = 6;
    *s = 0;
    *t = 5;

    // Initialize all capacities to 0
    for (int i = 0; i < *V; i++)
        for (int j = 0; j < *V; j++)
            capacity[i][j] = 0;

    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[2][1] = 4;
    capacity[1][3] = 12;
    capacity[3][2] = 9;
    capacity[2][4] = 14;
    capacity[4][3] = 7;
    capacity[3][5] = 20;
    capacity[4][5] = 4;

    printf("\nLoaded demo water distribution network.\n");
    printf("Vertices (0-5):\n");
    printf("0-Source Reservoir, 5-City Treatment Plant (Sink)\n");
}

int main()
{
    int V, s, t, choice;
    int capacity[MAX_VERTICES][MAX_VERTICES];

    while (1)
    {
        printf("\n===== Experiment 7 - Maxflow–Mincut (Ford–Fulkerson) =====\n");
        printf("1. Use Demo Water Distribution Network\n");
        printf("2. Enter Custom Capacity Network (Adjacency Matrix)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoWaterNetwork(&V, capacity, &s, &t);
        }
        else if (choice == 2)
        {
            printf("\nEnter number of vertices: ");
            scanf("%d", &V);

            if (V <= 0 || V > MAX_VERTICES)
            {
                printf("Invalid number of vertices.\n");
                continue;
            }

            printf("\nEnter adjacency matrix of capacities (0 = no pipe):\n");
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    scanf("%d", &capacity[i][j]);
                }
            }

            printf("\nEnter source vertex (0 to %d): ", V - 1);
            scanf("%d", &s);
            printf("Enter sink vertex (0 to %d): ", V - 1);
            scanf("%d", &t);

            if (s < 0 || s >= V || t < 0 || t >= V || s == t)
            {
                printf("Invalid source/sink.\n");
                continue;
            }
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

        // Run Max Flow + Min Cut analysis
        maxFlowMinCut(V, capacity, s, t);
    }

    return 0;
}
