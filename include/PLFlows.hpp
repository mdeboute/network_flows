#ifndef PLFLOWS_HPP
#define PLFLOWS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "gurobi_c++.h"
#include "Graph.hpp"

namespace PL
{
  int maxFlow(Graph &graph); //par défault sans affichage
  int maxFlow(Graph &graph, bool verbose); //boolean pour l'affichage
  int minCostFlow(Graph &graph); //par défault sans affichage
  int minCostFlow(Graph &graph, bool verbose); //boolean pour l'affichage
}

#endif
