#include <stdio.h>
#include <string.h>
#include "pattern_matching.h"

/*
    Scenario in comments:
    Text = patient's medical report or doctor's notes.
    Pattern = disease name / symptom keyword (e.g., "fever", "cough", "diabetes").
*/

void loadDemoMedicalReport(char text[])
{
    // Simple demo report
    strcpy(text,
           "Patient reports mild fever and headache since two days. "
           "No history of diabetes or hypertension. "
           "Fever pattern is intermittent with slight cough.");
    printf("\nLoaded Demo Medical Report Text:\n%s\n", text);
}

int main()
{
    int choice;
    char text[MAX_TEXT];
    char pattern[MAX_PATTERN];

    while (1)
    {
        printf("\n===== Brute-Force Pattern Matching (String Search) =====\n");
        printf("1. Use Demo Medical Report Text\n");
        printf("2. Enter Custom Text\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume leftover newline

        if (choice == 1)
        {
            loadDemoMedicalReport(text);
        }
        else if (choice == 2)
        {
            printf("\nEnter the text (max %d characters):\n", MAX_TEXT - 1);
            fgets(text, sizeof(text), stdin);

            // Remove trailing newline from fgets
            size_t len = strlen(text);
            if (len > 0 && text[len - 1] == '\n')
                text[len - 1] = '\0';
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

        printf("\nEnter the pattern to search (max %d characters):\n", MAX_PATTERN - 1);
        fgets(pattern, sizeof(pattern), stdin);

        // Remove trailing newline
        size_t plen = strlen(pattern);
        if (plen > 0 && pattern[plen - 1] == '\n')
            pattern[plen - 1] = '\0';

        bruteForceSearch(text, pattern);
    }

    return 0;
}
