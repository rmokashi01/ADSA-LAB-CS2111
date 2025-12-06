#include <stdio.h>
#include <string.h>
#include "tsp.h"

/*
    Experiment 14: Travelling Salesman Problem (TSP)
    Approach: Brute-Force using Backtracking (tries all permutations)

    Application Examples:
    1. Delivery Route Optimization
    2. Ambulance / Medical Supply Routing
    3. Tourist City Visit Planning
    4. Custom Distance Matrix
*/

// Scenario 1: Delivery Route (4 cities)
void loadDeliveryScenario(int *n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[])
{
    *n = 4;

    static const char *names[] = {
        "Warehouse",
        "Area A",
        "Area B",
        "Area C"
    };

    for (int i = 0; i < *n; i++)
        cityNames[i] = names[i];

    // Symmetric distance matrix (in km)
    int temp[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            dist[i][j] = temp[i][j];

    printf("\nLoaded Scenario 1: Delivery Route Optimization (Courier / Food Delivery)\n");
}

// Scenario 2: Ambulance / Medical Supply Routing (5 cities)
void loadAmbulanceScenario(int *n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[])
{
    *n = 5;

    static const char *names[] = {
        "Central Hospital",
        "Clinic 1",
        "Clinic 2",
        "Diagnostic Lab",
        "Trauma Center"
    };

    for (int i = 0; i < *n; i++)
        cityNames[i] = names[i];

    // Example distances (in km)
    int temp[5][5] = {
        {0,  8, 15, 20, 10},
        {8,  0,  5, 12, 14},
        {15, 5,  0, 10, 18},
        {20,12, 10, 0,  7},
        {10,14, 18, 7,  0}
    };

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            dist[i][j] = temp[i][j];

    printf("\nLoaded Scenario 2: Ambulance / Medical Supply Routing\n");
}

// Scenario 3: Tourist City Visit Planning (5 cities)
void loadTouristScenario(int *n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[])
{
    *n = 5;

    static const char *names[] = {
        "Karad",
        "Satara",
        "Pune",
        "Mumbai",
        "Kolhapur"
    };

    for (int i = 0; i < *n; i++)
        cityNames[i] = names[i];

    // Example approximate distances (not real highway distances, just demo values)
    int temp[5][5] = {
        {0,  50, 150, 300, 80},
        {50, 0, 130, 280, 120},
        {150,130, 0, 150, 230},
        {300,280,150, 0, 380},
        {80, 120,230,380, 0}
    };

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            dist[i][j] = temp[i][j];

    printf("\nLoaded Scenario 3: Tourist City Visit Planning\n");
}

// Scenario 4: Custom distance matrix
void loadCustomScenario(int *n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[])
{
    static char customNamesStorage[MAX_CITIES][30];

    printf("\nEnter number of cities (max %d): ", MAX_CITIES);
    scanf("%d", n);

    if (*n <= 1 || *n > MAX_CITIES)
    {
        printf("Invalid number of cities.\n");
        return;
    }

    printf("\nEnter name for each city:\n");
    for (int i = 0; i < *n; i++)
    {
        printf("City %d name: ", i);
        scanf("%s", customNamesStorage[i]);
        cityNames[i] = customNamesStorage[i];
    }

    printf("\nEnter distance matrix (0 for same city):\n");
    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            printf("Distance from %s to %s: ", cityNames[i], cityNames[j]);
            scanf("%d", &dist[i][j]);
        }
    }

    printf("\nLoaded Scenario 4: Custom Distance Matrix\n");
}

int main()
{
    int choice;
    int n = 0;
    int dist[MAX_CITIES][MAX_CITIES];
    const char *cityNames[MAX_CITIES];

    while (1)
    {
        printf("\n===== Experiment 14 – Travelling Salesman Problem (TSP) =====\n");
        printf("1. Delivery Route Optimization (Courier / Food Delivery)\n");
        printf("2. Ambulance / Medical Supply Routing\n");
        printf("3. Tourist City Visit Planning\n");
        printf("4. Enter Custom Distance Matrix\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDeliveryScenario(&n, dist, cityNames);
            solveTSP(n, dist, cityNames);
        }
        else if (choice == 2)
        {
            loadAmbulanceScenario(&n, dist, cityNames);
            solveTSP(n, dist, cityNames);
        }
        else if (choice == 3)
        {
            loadTouristScenario(&n, dist, cityNames);
            solveTSP(n, dist, cityNames);
        }
        else if (choice == 4)
        {
            loadCustomScenario(&n, dist, cityNames);
            if (n > 1)
                solveTSP(n, dist, cityNames);
        }
        else if (choice == 5)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
