#include <stdio.h>
#include <math.h>
#include "bellmanford.h"

/*
    Application:
    Currency Exchange Arbitrage Detection

    Currencies = nodes
    Exchange rates = edges

    For Bellman-Ford:
    weight = -log(rate)

    Negative cycle => arbitrage opportunity exists.
*/

void loadDemoCurrencyGraph(int *V, int *E, Edge edges[])
{
    /*
        Demo Currency Set:
        0 = USD
        1 = EUR
        2 = INR
        3 = GBP

        Example exchange rates:

        USD → EUR = 0.9
        EUR → INR = 90
        INR → USD = 0.0112  (may give arbitrage)
        USD → GBP = 0.79
        GBP → INR = 100
        INR → EUR = 0.012
    */

    *V = 4;
    *E = 6;

    float rate[] = {
        0.9,      // USD → EUR
        90,       // EUR → INR
        0.0112,   // INR → USD
        0.79,     // USD → GBP
        100,      // GBP → INR
        0.012     // INR → EUR
    };

    int s[] = {0, 1, 2, 0, 3, 2};
    int d[] = {1, 2, 0, 3, 2, 1};

    for (int i = 0; i < *E; i++)
    {
        edges[i].src = s[i];
        edges[i].dest = d[i];
        edges[i].weight = -log(rate[i]);  // Bellman-Ford weight
    }

    printf("\nLoaded demo currency exchange graph.\n");
    printf("Currencies:\n0 = USD\n1 = EUR\n2 = INR\n3 = GBP\n");
}

int main()
{
    int V, E, choice, src;
    Edge edges[MAX_EDGES];

    while (1)
    {
        printf("\n===== Bellman-Ford Algorithm - Currency Arbitrage Detection =====\n");
        printf("1. Use Demo Exchange Rates\n");
        printf("2. Enter Custom Exchange Rates\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoCurrencyGraph(&V, &E, edges);
        }
        else if (choice == 2)
        {
            printf("\nEnter number of currencies: ");
            scanf("%d", &V);

            printf("Enter number of exchange rates: ");
            scanf("%d", &E);

            printf("\nEnter edges as:\nsource_currency dest_currency rate\n");
            printf("(Indices 0 to %d)\n", V - 1);

            for (int i = 0; i < E; i++)
            {
                int s, d;
                float rate;

                printf("Edge %d: ", i + 1);
                scanf("%d %d %f", &s, &d, &rate);

                edges[i].src = s;
                edges[i].dest = d;
                edges[i].weight = -log(rate);  // transformation
            }
        }
        else if (choice == 3)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
            continue;
        }

        printf("\nEnter source currency (0 to %d): ", V - 1);
        scanf("%d", &src);

        bellmanFord(V, E, edges, src);
    }

    return 0;
}
