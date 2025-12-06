#include <stdio.h>
#include "knapsack.h"

/*
    Scenario:
    Ambulance has max capacity.
    Items = emergency medical supplies.
*/

void loadDemoMedicalItems(int *n, int weights[], int values[], int *capacity)
{
    /*
        Items:
        1. Oxygen Cylinder      (weight 10, value 60)
        2. First Aid Kit        (weight 20, value 100)
        3. Ventilator Mask      (weight 30, value 120)
        4. Injection Pack       (weight 25, value 90)

        Bag Capacity = 50
    */

    *n = 4;
    *capacity = 50;

    weights[0] = 10;  values[0] = 60;
    weights[1] = 20;  values[1] = 100;
    weights[2] = 30;  values[2] = 120;
    weights[3] = 25;  values[3] = 90;

    printf("\nLoaded Demo Medical Items\n");
    printf("Index   Weight   Value   Description\n");
    printf(" 1        10       60     Oxygen Cylinder\n");
    printf(" 2        20      100     First Aid Kit\n");
    printf(" 3        30      120     Ventilator Mask\n");
    printf(" 4        25       90     Injection Pack\n");
}

int main()
{
    int n, capacity, choice;
    int weights[MAX_ITEMS], values[MAX_ITEMS];

    while (1)
    {
        printf("\n===== Experiment 9 - 0/1 Knapsack Problem =====\n");
        printf("1. Use Demo Medical Items\n");
        printf("2. Enter Custom Items\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loadDemoMedicalItems(&n, weights, values, &capacity);
        }
        else if (choice == 2)
        {
            printf("Enter number of items: ");
            scanf("%d", &n);

            printf("Enter knapsack capacity: ");
            scanf("%d", &capacity);

            for (int i = 0; i < n; i++)
            {
                printf("Enter weight and value for item %d: ", i + 1);
                scanf("%d %d", &weights[i], &values[i]);
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

        knapsack(n, capacity, weights, values);
    }

    return 0;
}
