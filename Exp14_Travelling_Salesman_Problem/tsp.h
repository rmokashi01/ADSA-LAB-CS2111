#ifndef TSP_H
#define TSP_H

#define MAX_CITIES 10
#define INF 1000000000  // A very large value

// Solve TSP for given distance matrix and city names.
// n          : number of cities
// dist       : distance matrix (n x n)
// cityNames  : array of city names (strings)
void solveTSP(int n, int dist[MAX_CITIES][MAX_CITIES], const char *cityNames[]);

#endif
