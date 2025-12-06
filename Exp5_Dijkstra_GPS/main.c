#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

/*
   Scenario: GPS Navigation System in a Small City

   Each vertex = Area / Junction in the city
   Each edge weight = Distance (in km) between those two locations

   We use adjacency matrix:
   - 0  => No direct road between locations
   - >0 => Distance between them
*/

void loadDemoGPSGraph(int *V, int graph[MAX_VERTICES][MAX_VERTICES])
{
    /*
       Demo City Map (Example):

       Node to Place Mapping:
       0 - Home
       1 - City Center
       2 - Railway Station
       3 - Shopping Mall
       4 - Hospital
       5 - University

       Distances (in km, symmetric for undirected roads):

                  0   1   2   3   4   5
            0 [   0   4   0   2   0   0 ]
            1 [   4   0   5   1   7   3 ]
            2 [   0   5   0   6   2   0 ]
            3 [   2   1   6   0   0   4 ]
            4 [   0   7   2   0   0   3 ]
            5 [   0   3   0   4   3   0 ]
    */

    *V = 6;

    int demo[6][6] =
    {
        {0, 4, 0, 2, 0, 0},
        {4, 0, 5, 1, 7, 3},
        {0, 5, 0, 6, 2, 0},
        {2, 1, 6, 0, 0, 4},
        {0, 7, 2, 0, 0, 3},
        {0, 3, 0, 4, 3, 0}
    };

    for (int i = 0; i < *V; i++)
    {
        for (int j = 0; j < *V; j++)
        {
            graph[i][j] = demo[i][j];
        }
    }

    printf("\nLoaded demo city road network graph for GPS Navigation.\n");
    printf("Nodes and their corresponding places:\n");
    printf("0 - Home\n");
    printf("1 - City Center\n");
    printf("2 - Railway Station\n");
    printf("3 - Shopping Mall\n");
    printf("4 - Hospital\n");
    printf("5 - University\n");
}

int main()
{
    int V, choice, src;
    int graph[MAX_VERTICES][MAX_VERTICES];

    while (1)
    {
        printf("\n===== Experiment - Dijkstra's Algorithm (GPS Navigation System) =====\n");
        printf("1. Use Demo City Road Network\n");
        printf("2. Enter Custom Road Network (Adjacency Matrix)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoGPSGraph(&V, graph);
        }
        else if (choice == 2)
        {
            printf("\nEnter number of locations (vertices): ");
            scanf("%d", &V);

            if (V <= 0 || V > MAX_VERTICES)
            {
                printf("Invalid number of locations.\n");
                continue;
            }

            printf("\nEnter adjacency matrix (0 = no road, >0 = distance):\n");
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    scanf("%d", &graph[i][j]);
                }
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

        printf("\nEnter source location (0 to %d): ", V - 1);
        scanf("%d", &src);

        if (src < 0 || src >= V)
        {
            printf("Invalid source location.\n");
            continue;
        }

        // Run Dijkstra on the chosen graph and source
        dijkstra(V, graph, src);
    }

    return 0;
}
