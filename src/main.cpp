#include <iostream>
#include "Structures.hpp"
#include "parser.hpp"
#include "algorithms.hpp"
using namespace std;

int main()
{
  Graph graph = mincost::parse("../data/negative_weight_cycle.min");
  graph.print();
  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph();
  rGraph->print();

  cout << endl;
  BellmanFord(graph, 0);

  // TODO: régler le problème de la fonction setFlow et getResidualGraph ('undefined reference to')
  return 0;
}
