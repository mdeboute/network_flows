#include "Structures.cpp"
#include "Manipulation.cpp"
#include "MinCostParser.cpp"


int main()
{
  Graph graph = parse("../data/test.txt");
  graph.print();
  std::cout << std::endl;
  std::cout << "Residual graph:\n" << std::endl;
  Graph* rGraph = graph.getResidualGraph();
  rGraph->print();
  return 0;
}
