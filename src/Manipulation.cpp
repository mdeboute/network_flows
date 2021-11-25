#include "Structures.hpp"



void Graph::addEdge(Edge edge)
{
  edges.push_back(edge);

  edge.start->nbLeavingEdges += 1;
  edge.start->leavingEdges.push_back(&edges[nbEdges]);

  edge.end->nbEnteringEdges += 1;
  edge.end->enteringEdges.push_back(&edges[nbEdges]);

  nbEdges += 1;
}



Graph* Graph::getResidualGraph()
{
  Graph* residualGraph = new Graph(nbVertices,0,{});

  for(Edge edge : edges){

    int residualCapacity = edge.capacity - edge.flow;

    if(residualCapacity > 0){

      Vertex* start = &residualGraph->vertices[edge.end->id];
      Vertex* end = &residualGraph->vertices[edge.start->id];

      Edge residualEdge(nbEdges,0,residualCapacity,start,end);

      residualEdge.pairedEdge = &edge;

      residualGraph->addEdge(residualEdge);

      edge.pairedEdge = &edges[nbEdges-1];
    }
  }
  return residualGraph;
}
