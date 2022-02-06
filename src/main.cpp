#include <iostream>
#include "Structures.hpp"
#include "parser.hpp"
using namespace std;

int main()
{
  Graph graph = maxflow::parse("../data/maxflow/instance_1.max"); // undefined reference to `Graph::setFlow(int, int)'
  graph.print();
  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph();
  rGraph->print();

  // TODO: régler le problème de la fonction setFlow et getResidualGraph
  return 0;
}
