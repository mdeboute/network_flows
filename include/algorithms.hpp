#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Structures.hpp"

void printArr(int dist[], int n);
void BellmanFord(Graph graph, int src);
bool bfs(Graph rgraph, int s, int t, int parent[]);
void FordFulkerson(Graph graph, int src, int sink);

#endif

