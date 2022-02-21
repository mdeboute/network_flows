#include <iostream>
#include "PreflowPush.hpp"
#include "Graph.hpp"
#include <cstdio>
#include <limits.h>
#include <climits> // for INT_MAX
#include <queue>
#include <string.h>
using namespace std;

void distanceLabelling(Graph *graph)
{
  bool marks[graph->nbVertices];
  for (int i = 0; i < graph->nbVertices; i++)
  {
    marks[i] = false;
    graph->vertices[i].height = -1;
  }
  marks[graph->sink] = true;
  graph->vertices[graph->sink].height = 0;
  std::queue<int> List;
  List.push(graph->sink);
  while (List.size() > 0)
  {
    bool hasAdmissibleArc = false;
    for (int i = 0; i < graph->vertices[List.front()].leavingEdgesId.size(); i++)
    {
      if (marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] == false)
      {
        hasAdmissibleArc = true;
        marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] = true;
        graph->vertices[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId].height = graph->vertices[List.front()].height + 1;
        List.push(graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId);
      }
    }
    List.pop();
  }
  return;
}

void preflowPush(Graph *original_graph)
{
  Graph *graph = original_graph->getResidualGraph(true);
  queue<int> activeNodes;

  // Initialisation des valeurs
  for (int i = 0; i < graph->nbVertices; ++i)
  {
    graph->vertices[i].exceedingFlow = 0;
  }
  // distance
  distanceLabelling(graph);

  for (int id : graph->vertices[graph->src].leavingEdgesId)
  {
    graph->vertices[graph->edges[id].endId].exceedingFlow = graph->edges[id].residualCapacity;
    graph->edges[id].increaseResidualCapacity(*graph, -graph->vertices[graph->edges[id].endId].exceedingFlow);
    activeNodes.push(graph->edges[id].endId);
  }

  // Tant qu'il existe du flot en exces
  while (!activeNodes.empty())
  {
    int v = activeNodes.front();
    bool admissibleEdge = false;
    for (int id : graph->vertices[v].leavingEdgesId)
    {
      if (graph->edges[id].residualCapacity > 0 && graph->vertices[graph->edges[id].endId].height + 1 == graph->vertices[v].height)
      {
        admissibleEdge = true;
        int delta = min(graph->vertices[v].exceedingFlow, graph->edges[id].residualCapacity);
        graph->edges[id].increaseResidualCapacity(*graph, -delta);
        graph->vertices[v].exceedingFlow -= delta;
        if (graph->edges[id].endId != graph->src && graph->edges[id].endId != graph->sink && graph->vertices[graph->edges[id].endId].exceedingFlow == 0)
        {
          activeNodes.push(graph->edges[id].endId);
        }
        graph->vertices[graph->edges[id].endId].exceedingFlow += delta;
        if (graph->vertices[v].exceedingFlow == 0)
        {
          activeNodes.pop();
          break;
        }
      }
    }
    if (!admissibleEdge)
    {
      int min_height = 2 * graph->nbVertices;
      for (int id : graph->vertices[v].leavingEdgesId)
      {
        if (graph->edges[id].residualCapacity > 0 && graph->vertices[graph->edges[id].endId].height + 1 < min_height)
        {
          min_height = graph->vertices[graph->edges[id].endId].height + 1;
        }
      }
      graph->vertices[v].height = min_height;
    }
  }
  original_graph->fillGraphFromResidual(graph);
}
