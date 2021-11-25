#include "Structures.cpp"



int main()
{
  // (s,e,w,c) -> arête du sommet s vers e, avec pois w et capacité c
  int edgeArray[][4] = {{0,1,5,10},{1,2,5,10},{2,0,5,10},{3,1,5,10}};
  Graph graph(4,4,edgeArray);
  graph.print();
  return 0;
}
