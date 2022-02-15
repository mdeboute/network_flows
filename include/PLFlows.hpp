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
  void maxFlow(Graph &graph);
  void minCostFlow(Graph &graph);
}

#endif
