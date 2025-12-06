#include <stdio.h>
#include <stdlib.h>
#include "edmonds_karp.h"

/*
    Scenario:
    Hospital Oxygen Supply Network

    Vertices (demo mapping):
    0 - Central Oxygen Tank (Source)
    1 - ICU Block
    2 - Operation Theatre
    3 - Emergency Ward
    4 - General Ward
    5 - Ventilator Support Unit (Sink)

    Edge capacity[u][v] = max oxygen flow capacity (e.g., liters/min).
*/

void loadDemoOxygenNetwork(int *V, int capacity[MAX_VERTICES][MAX_VERTICES],
                           int *s, int *t)
{
    /*
       We reuse a classic max-flow structure but interpret it
       as oxygen pipe capacities.

       Known max flow for this example = 23 units.
    */

    *V = 6;
    *s = 0;  // Central Oxygen Tank
    *t = 5;  // Ventilator Support Unit

    // Initialize all capacities to 0
    for (int i = 0; i < *V; i++)
        for (int j = 0; j < *V; j++)
            capacity[i][j] = 0;

    // Pipes and capacities
    capacity[0][1] = 16;  // Tank -> ICU
    capacity[0][2] = 13;  // Tank -> OT
    capacity[1][2] = 10;  // ICU -> OT (bypass)
    capacity[2][1] = 4;   // OT -> ICU (return / balancing line)
    capacity[1][3] = 12;  // ICU -> Emergency
    capacity[3][2] = 9;   // Emergency -> OT
    capacity[2][4] = 14;  // OT -> General Ward
    capacity[4][3] = 7;   // General -> Emergency
    capacity[3][5] = 20;  // Emergency -> Ventilator Unit
    capacity[4][5] = 4;   // General -> Ventilator Unit

    printf("\nLoaded demo Hospital Oxygen Supply Network.\n");
    printf("Vertices (0-5):\n");
    printf("0 - Central Oxygen Tank (Source)\n");
    printf("1 - ICU Block\n");
    printf("2 - Operation Theatre\n");
    printf("3 - Emergency Ward\n");
    printf("4 - General Ward\n");
    printf("5 - Ventilator Support Unit (Sink)\n");
}

int main()
{
    int V, s, t, choice;
    int capacity[MAX_VERTICES][MAX_VERTICES];

    while (1)
    {
        printf("\n===== Experiment 8 - Edmonds–Karp (Hospital Oxygen Network) =====\n");
        printf("1. Use Demo Oxygen Network\n");
        printf("2. Enter Custom Capacity Network (Adjacency Matrix)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoOxygenNetwork(&V, capacity, &s, &t);
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

        // Run Edmonds–Karp Max Flow
        edmondsKarp(V, capacity, s, t);
    }

    return 0;
}
