#ifndef CHECKER_HPP
#define CHECKER_HPP

#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <iostream>

bool validFlow(Graph* graph);
bool flowConservation(Graph* graph);
bool flowLimitations(Graph* graph);

#endif
