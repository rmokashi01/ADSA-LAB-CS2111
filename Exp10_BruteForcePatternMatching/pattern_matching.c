#include <stdio.h>
#include <string.h>
#include "pattern_matching.h"

/*
    Experiment: Brute-Force Pattern Matching

    Real Scenario:
    Searching a medical keyword (e.g., "fever", "diabetes")
    inside a patient's medical report or doctor's notes.

    Algorithm:
    For each possible shift i in text:
        Compare pattern with text[i..i+m-1]
        If all characters match, record occurrence.
*/

int bruteForceSearch(const char text[], const char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;

    if (m == 0 || n == 0 || m > n)
    {
        printf("\nPattern cannot be matched (empty or longer than text).\n");
        return 0;
    }

    printf("\n=== Brute-Force Pattern Matching Trace ===\n");

    // For each possible starting position in text
    for (int i = 0; i <= n - m; i++)
    {
        int j;

        printf("\nChecking at text index %d: ", i);
        // Show current comparison window
        for (int k = 0; k < m; k++)
            printf("%c", text[i + k]);
        printf("\n");

        // Compare pattern with text substring
        for (j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
            {
                printf("Mismatch at j = %d (text[%d] = '%c', pattern[%d] = '%c')\n",
                       j, i + j, text[i + j], j, pattern[j]);
                break;
            }
        }

        if (j == m)
        {
            // full match
            printf("✔ Match found at index %d\n", i);
            count++;
        }
    }

    if (count == 0)
        printf("\nNo match found for pattern \"%s\" in the given text.\n", pattern);
    else
        printf("\nTotal %d occurrence(s) of pattern \"%s\" found in text.\n", count, pattern);

    return count;
}
