#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "PreflowPush.hpp"
#include "benchmarks.hpp"
using namespace std;

int main()
{
<<<<<<< HEAD
  maxFlowComparison("../data/maxflow/instance_1.max");

  //Graph graph = maxflow::parse("../data/maxflow/instance_1.max");
  //graph.print();
  //cout << endl;
  //cout << "Residual graph:\n";
  //cout << endl;
  //Graph graphMax = maxflow::parse("../data/maxflow/instance_1.max");
  //PL::maxFlow(graphMax);

  //Graph *rGraph = graph.getResidualGraph(true);
  //shortestAugmentingPath(rGraph);
  //graph.fillGraphFromResidual(rGraph);
  //graph.print();
  //cout << endl;

  //cout << endl;



  //cout << "Max flow: " << graph.getValueObjMaxFlow() << endl;
  //saveSolution(&graph, "../sol/maxflow_1");
  //validFlow(&graph);
=======
  Graph graph = maxflow::parse("../data/maxflow/instance_1.max");
  // graph.print();
  // cout << endl;
  // cout << "Residual graph:\n";
  // cout << endl;
  Graph *rGraph = graph.getResidualGraph(true);
  shortestAugmentingPath(rGraph);
  graph.fillGraphFromResidual(rGraph);
  graph.print();
  // cout << endl;
  cout << "Max flow: " << graph.getValueObjMaxFlow() << endl;
  // saveSolution(&graph, "../sol/maxflow_1");
  validFlow(&graph);

  // cout << endl;

  // Graph graphMax = maxflow::parse("../data/maxflow/instance_1.max");
  // PL::maxFlow(graphMax);
>>>>>>> ab56983b5c41ee042a13a3b8ee208fac2a4d9eba

  // Graph graphMin = mincost::parse("../data/mincost/simple_min_cost.min");
  // PL::minCostFlow(graphMin);


  // Test Preflow Push
  // Graph graph = maxflow::parse("../data/simple_max_flot.max");
  // preflowPush(&graph);

  // cycleCancelling(&graph);

  // Problème: on trouve pas la même solution pour l'algo et le solveur...
  return 0;
}
