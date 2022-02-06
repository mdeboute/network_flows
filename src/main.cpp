#include <iostream>
#include "Structures.hpp"
#include "parser.hpp"
using namespace std;

int main()
{
  Graph graph = mincost::parse("../data/mincost/test.txt");
  graph.print();
  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph();
  rGraph->print();

  cout << endl;
  Graph graph2 = maxflow::parse("../data/maxflow/instance_1.max");
  // graph2.print();

  // TODO:
  // inclure les headers (en créer si besoin) et non les fichiers .cpp
  // les protéger avec des #ifndef et #define

  return 0;
}
