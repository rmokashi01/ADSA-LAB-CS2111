#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#define MAX_TEXT 1000
#define MAX_PATTERN 100
#define NO_OF_CHARS 256

// Boyer-Moore (Bad Character Rule)
// Returns number of matches and prints shifting trace
int boyerMooreSearch(const char text[], const char pattern[]);

#endif
