#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "Graph.hpp"

void printArr(int dist[], int n);
int BellmanFord(Graph graph, int src);
void cycleCancelling(Graph *graph);
void shortestAugmentingPath(Graph *graph);

#endif
