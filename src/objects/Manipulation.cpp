#include "Structures.hpp"



void Graph::addEdge(Edge edge)
{
  edges.push_back(edge);

  vertices[edge.startId].nbLeavingEdges += 1;
  vertices[edge.startId].leavingEdgesId.push_back(nbEdges);

  vertices[edge.endId].nbEnteringEdges += 1;
  vertices[edge.endId].enteringEdgesId.push_back(nbEdges);

  nbEdges += 1;
}


Graph* Graph::getResidualGraph()
{
  Graph* residualGraph = new Graph(nbVertices);

  for(Edge edge : edges){

    int residualCapacity = edge.maxCapacity - edge.flow;

    if(residualCapacity > 0){

      int id = residualGraph->nbEdges;
      int cost = edge.cost;
      int minCapacity = 0;
      int maxCapacity = residualCapacity;
      int startId = edge.endId;
      int endId = edge.startId;

      Edge residualEdge(id,cost,minCapacity,maxCapacity,startId,endId);

      residualEdge.pairedEdgeId = edge.id;
      edge.pairedEdgeId = residualGraph->nbEdges;

      residualGraph->addEdge(residualEdge);
    }
  }
  return residualGraph;
}
