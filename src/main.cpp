#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "PreflowPush.hpp"
#include "benchmarks.hpp"
#include <fstream>
using namespace std;

int main()
{
  //maxFlowComparison("../data/maxflow/instance_10_20_1.max", true);
  // maxFlowBenchmarks(true);

  Graph graphMin = mincost::parse("../data/mincost/gte/gte_bad.20");
  PL::minCostFlow(graphMin, true);

  Graph graph = mincost::parse("../data/mincost/gte/gte_bad.20");
  cycleCancelling(&graph);
  std ::cout << graph.getValueObjMinCost() << std::endl;


  return 0;
}
