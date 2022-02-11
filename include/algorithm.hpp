#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "Graph.hpp"

void printArr(int dist[], int n);
int BellmanFord(Graph graph, int src);
bool bfs(Graph *rgraph, int s, int t, int parent[]);
void FordFulkerson(Graph *graph, int src, int sink);
void cycleCancelling(Graph *graph);
void shortestAugmentingPath(Graph *graph);

#endif
