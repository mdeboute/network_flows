#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "PreflowPush.hpp"
using namespace std;

int main()
{
  Graph graph = maxflow::parse("../data/maxflow/instance_1.max");
  graph.print();
  cout << endl;
  cout << "Residual graph:\n";
  cout << endl;
  Graph *rGraph = graph.getResidualGraph(true);
  shortestAugmentingPath(rGraph);
  graph.fillGraphFromResidual(rGraph);
  graph.print();
  cout << endl;
  cout << "Max flow: " << rGraph->getValueObjMaxFlow() << endl;
  saveSolution(&graph, "../sol/maxflow_1");
  validFlow(&graph); // flow pas valide cf. l'execution du programme

  cout << endl;

  Graph graphMax = maxflow::parse("../data/maxflow/instance_1.max");
  PL::maxFlow(graphMax);
  
  //Graph graphMin = mincost::parse("../data/simple_min_cost.min");
  //PL::minCostFlow(graphMin);

  //Test Preflow Push
  //Graph graph = maxflow::parse("../data/simple_max_flot.max");
  //preflowPush(&graph);
  //std::cout << graph.getValueObjMaxFlow();

  // Problème: on trouve pas la même solution pour l'algo et le solveur...
  return 0;
}
