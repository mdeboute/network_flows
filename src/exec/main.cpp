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
  // ligne suivante pour débugger prepush
  //   maxFlowComparison("../data/maxflow/instance_10_20_39.max", "instance_10_20_39.max", true);
  //   maxFlowBenchmarks(true);
  Graph graphMin = minCost::parse("../data/mincost/small_instances/boop3.max.min");

  Graph graphMinCobaye = minCost::parse("../data/mincost/small_instances/boop3.max.min");

  Graph graph = minCost::parse("../data/mincost/small_instances/boop3.max.min");

  int maxPossibleFlow = setMaxPossibleFlow(&graphMinCobaye);

  graph.vertices[graph.src].exceedingFlow = maxPossibleFlow;
  graph.vertices[graph.sink].exceedingFlow = -maxPossibleFlow;
  graph.vertices[graph.src].exceedingFlow = maxPossibleFlow;
  graph.vertices[graph.sink].exceedingFlow = -maxPossibleFlow;

  for(int i = 0; i < graph.nbEdges; i++){
    int rndInt = rand() % 100;
    graph.edges[i].cost = rndInt;
    graphMin.edges[i].cost = rndInt;
    cout << graph.edges[i].cost << endl;
  }

  PL::minCost(graphMin, true);

  meanCycleCancelling(&graph);
  //   cycleCancelling(&graph);
  cout << graph.getValueObjMinCost() << endl;

  return 0;
}
