#include <stdio.h>
#include <string.h>
#include "boyer_moore.h"

/*
    Demo Scenario:
    A long medical report text.
*/

void loadDemoMedicalReport(char text[])
{
    strcpy(text,
           "Patient shows signs of chronic infection and mild fever. "
           "Further tests show no indication of cancer or thyroid disorder. "
           "Secondary infection suspected based on lab results.");
    
    printf("\nLoaded Demo Medical Report:\n%s\n", text);
}

int main()
{
    int choice;
    char text[MAX_TEXT];
    char pattern[MAX_PATTERN];

    while (1)
    {
        printf("\n===== Experiment 11 - Boyer–Moore Algorithm =====\n");
        printf("1. Use Demo Medical Report\n");
        printf("2. Enter Custom Text\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            loadDemoMedicalReport(text);
        }
        else if (choice == 2)
        {
            printf("\nEnter text:\n");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0';
        }
        else if (choice == 3)
        {
            printf("Exiting...\n");
            return 0;
        }
        else
        {
            printf("Invalid option.\n");
            continue;
        }

        printf("\nEnter pattern to search:\n");
        fgets(pattern, sizeof(pattern), stdin);
        pattern[strcspn(pattern, "\n")] = '\0';

        boyerMooreSearch(text, pattern);
    }

    return 0;
}
