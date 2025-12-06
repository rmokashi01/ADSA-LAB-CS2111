#include <stdio.h>
#include "tsp.h"

// Global variables for backtracking
static int g_n;
static int g_dist[MAX_CITIES][MAX_CITIES];

static int g_bestPath[MAX_CITIES + 1];
static int g_currentPath[MAX_CITIES + 1];
static int g_visited[MAX_CITIES];

static int g_bestCost;

// Recursive utility for TSP (backtracking)
static void tspUtil(int currentCity, int countVisited, int costSoFar, int startCity)
{
    // Pruning: if cost already exceeds best, stop
    if (costSoFar >= g_bestCost)
        return;

    // If all cities are visited, close the tour and update best
    if (countVisited == g_n)
    {
        int returnCost = g_dist[currentCity][startCity];
        if (returnCost > 0)  // there is a path back
        {
            int totalCost = costSoFar + returnCost;
            if (totalCost < g_bestCost)
            {
                g_bestCost = totalCost;

                // Copy best path
                for (int i = 0; i < g_n; i++)
                    g_bestPath[i] = g_currentPath[i];
                g_bestPath[g_n] = startCity;  // return to start at the end
            }
        }
        return;
    }

    // Try next city
    for (int nextCity = 0; nextCity < g_n; nextCity++)
    {
        if (!g_visited[nextCity] && g_dist[currentCity][nextCity] > 0)
        {
            g_visited[nextCity] = 1;
            g_currentPath[countVisited] = nextCity;

            tspUtil(nextCity, countVisited + 1,
                    costSoFar + g_dist[currentCity][nextCity],
                    startCity);

            g_visited[nextCity] = 0; // backtrack
        }
    }
}

void solveTSP(int n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[])
{
    g_n = n;

    // Copy distance matrix
    for (int i = 0; i < g_n; i++)
    {
        for (int j = 0; j < g_n; j++)
        {
            g_dist[i][j] = dist[i][j];
        }
    }

    g_bestCost = INF;

    // Assume starting city = 0 (first city)
    int startCity = 0;

    // Initialize path and visited array
    for (int i = 0; i < g_n; i++)
        g_visited[i] = 0;

    g_visited[startCity] = 1;
    g_currentPath[0] = startCity;

    printf("\nExploring all possible tours using backtracking...\n");
    tspUtil(startCity, 1, 0, startCity);

    if (g_bestCost == INF)
    {
        printf("\nNo valid tour found.\n");
        return;
    }

    // Print result
    printf("\n=== Optimal Travelling Salesman Tour ===\n");
    printf("Path: ");

    for (int i = 0; i <= g_n; i++)
    {
        int cityIndex = g_bestPath[i];
        printf("%s", cityNames[cityIndex]);
        if (i != g_n)
            printf(" -> ");
    }

    printf("\nTotal Minimum Cost: %d\n", g_bestCost);
}
