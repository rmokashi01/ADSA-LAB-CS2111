#include <stdio.h>
#include "knapsack.h"

/*
    Experiment 9: 0/1 Knapsack Problem (Dynamic Programming)

    Real Scenario: Emergency Ambulance Kit Packing
    You must choose medical items that maximize importance (value)
    without exceeding ambulance bag weight capacity.
*/

void knapsack(int n, int capacity, int weights[], int values[])
{
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1];

    // Build DP Table
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
            {
                int include = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print DP Table
    printf("\n=== DP Table (Knapsack) ===\n");
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            printf("%3d ", dp[i][w]);
        }
        printf("\n");
    }

    printf("\nMaximum Total Value that can be carried = %d\n", dp[n][capacity]);

    // Traceback selected items
    printf("\nSelected Medical Items:\n");
    int w = capacity;
    for (int i = n; i > 0 && w > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            printf("Item %d (Weight=%d, Value=%d)\n", i, weights[i - 1], values[i - 1]);
            w -= weights[i - 1];
        }
    }
}
