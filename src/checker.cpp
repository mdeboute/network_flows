#include "checker.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <iostream>

bool validFlow(Graph *graph)
{

  if (not flowConservation(graph))
  {
    return false;
  }
  if (not flowLimitations(graph))
  {
    return false;
  }
  return true;
}

bool flowConservation(Graph *graph)
{
  for (Vertex vertex : graph->vertices)
  {
    int enteringFlow = 0;
    int leavingFlow = 0;

    for (int edgeId : vertex.leavingEdgesId)
    {
      Edge edge = graph->edges[edgeId];
      leavingFlow += edge.flow;
    }

    for (int edgeId : vertex.enteringEdgesId)
    {
      Edge edge = graph->edges[edgeId];
      enteringFlow += edge.flow;
    }

    if (enteringFlow != leavingFlow and vertex.id != graph->src and vertex.id != graph->sink)
    {
      std::cout << "Vertex " << vertex.id << ": different entering (" << enteringFlow << ") and leaving (" << leavingFlow << ") flows\n";
      return false;
    }
  }
  return true;
}

bool flowLimitations(Graph *graph)
{
  for (Edge edge : graph->edges)
  {

    if (edge.flow < edge.minCapacity)
    {
      std::cout << "Edge " << edge.id << ": flow (" << edge.flow << ") below minimal capacity (" << edge.minCapacity << ")\n";
      return false;
    }

    if (edge.flow > edge.maxCapacity)
    {
      std::cout << "Edge " << edge.id << ": flow (" << edge.flow << ") above maximal capacity (" << edge.maxCapacity << ")\n";
      return false;
    }
  }
  return true;
}
