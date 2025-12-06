#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#define MAX_VERTICES 20
#define INF 1000000000

// Edmonds-Karp (BFS based Ford–Fulkerson)
// V      : number of vertices
// capacity: capacity matrix [V][V]
// s      : source vertex
// t      : sink vertex
void edmondsKarp(int V, int capacity[MAX_VERTICES][MAX_VERTICES], int s, int t);

#endif
