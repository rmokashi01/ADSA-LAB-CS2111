#include <stdio.h>
#include <string.h>
#include "boyer_moore.h"

/*
    Experiment 11: Boyer–Moore Pattern Matching
    Using the "Bad Character Heuristic"

    Real Scenario:
    Searching critical medical terms in large patient diagnosis reports.

    Boyer-Moore works from RIGHT → LEFT.
*/

// Function to preprocess the pattern for bad-character heuristic
static void badCharHeuristic(const char pattern[], int m, int badchar[])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (int i = 0; i < m; i++)
        badchar[(unsigned char)pattern[i]] = i;
}

int boyerMooreSearch(const char text[], const char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0 || n == 0 || m > n)
    {
        printf("\nInvalid input: Pattern empty or longer than text.\n");
        return 0;
    }

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badchar);

    printf("\n=== Boyer–Moore Pattern Matching Trace ===\n");
    printf("Text length = %d, Pattern length = %d\n", n, m);

    int shift = 0;
    int matchCount = 0;

    while (shift <= (n - m))
    {
        int j = m - 1; // start comparing from end of pattern

        printf("\nChecking alignment at shift %d:\n", shift);

        // Match pattern backwards
        while (j >= 0 && pattern[j] == text[shift + j])
        {
            printf("Matched: pattern[%d] = '%c' with text[%d] = '%c'\n",
                   j, pattern[j], shift + j, text[shift + j]);
            j--;
        }

        if (j < 0)
        {
            printf("✔ Match found at index %d\n", shift);
            matchCount++;

            // Shift so that next character after match aligns correctly
            shift += (shift + m < n) ? m - badchar[(unsigned char)text[shift + m]] : 1;
        }
        else
        {
            char mismatched = text[shift + j];
            int badIndex = badchar[(unsigned char)mismatched];

            printf("Mismatch at text[%d] = '%c'\n", shift + j, mismatched);
            printf("Bad-character last seen at pattern[%d]\n", badIndex);

            int skip = (j - badIndex > 1) ? j - badIndex : 1;

            printf("Shifting pattern by %d positions\n", skip);

            shift += skip;
        }
    }

    if (matchCount == 0)
        printf("\nNo occurrences of \"%s\" found.\n", pattern);
    else
        printf("\nTotal matches found: %d\n", matchCount);

    return matchCount;
}
