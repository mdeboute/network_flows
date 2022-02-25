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
  maxFlowComparison("../data/maxflow/instance_10_20_39.max","instance_10_20_39.max",true);
  //maxFlowBenchmarks(true);

  //Graph graphMin = mincost::parse("../data/mincost/simple_min_cost.min");
  //cycleCancelling(&graphMin);

  return 0;
}
