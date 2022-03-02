#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithms.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "benchmarks.hpp"
#include <fstream>
using namespace std;

int main()
{
  // maxFlowComparison("../data/maxflow/instance_10_20_39.max", "instance_10_20_39.max", true);
  // maxFlowBenchmarks(true);

  Graph graph = minCost::parse("../data/mincost/small_instances/instance_10_20_1.max.min");
  PL::minCost(graph, true);

  Graph graphMin = minCost::parse("../data/mincost/small_instances/instance_10_20_1.max.min");
  cycleCancelling(&graphMin);

  return 0;
}
