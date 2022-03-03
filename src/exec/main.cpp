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

  Graph graph = minCost::parse("../data/mincost/gte/gte_bad.508829");
  

  Graph graphMin = minCost::parse("../data/mincost/gte/gte_bad.508829");

  PL::minCost(graph, true);
  cycleCancelling(&graphMin);
  cout << graphMin.getValueObjMinCost() << endl;
  return 0;
}
