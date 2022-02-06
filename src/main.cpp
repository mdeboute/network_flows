#include <iostream>
#include "Structures.hpp"
#include "parser.hpp"
using namespace std;

int main()
{
  Graph graph = mincost::parse("../data/mincost/test.txt");
  graph.print();
  // cout << endl;
  // cout << "Residual graph:\n"
  //      << endl;
  // Graph *rGraph = graph.getResidualGraph(); //undefined reference to `Graph::getResidualGraph()' ?
  // rGraph->print();

  cout << endl;
  Graph graph2 = maxflow::parse("../data/maxflow/instance_1.max");
  // graph2.print();

  return 0;
}
