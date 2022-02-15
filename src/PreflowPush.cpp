#include <iostream>
#include "PreflowPush.hpp"
#include "Graph.hpp"
#include <cstdio>
#include <limits.h>
#include <climits> // for INT_MAX
#include <queue>
#include <string.h>


/*//Calcul l'excédant de flot
int exceedingFlow(Graph *graph, int vertexId)
{
  Vertex current = graph->vertices[vertexId];
  int tmp = 0;
  for(int id : current.enteringEdgesId)
  {
    tmp += graph->edges[id].flow;
  }
  for(int id : current.leavingEdgesId)
  {
    tmp -= graph->edges[id].flow;
  }
  return tmp;
}
*/
int min (int a, int b){
  if (a > b)
    return b;
  return a;
}
//Retourne l'indice de la première arrête ayant un excédant de flot
int overFlow(Graph *graph)
{
  for(Vertex ver : graph->vertices)
  {
    if(ver.exceedingFlow > 0)
    {
      return ver.id;
    }
  }
  return -1;
}

//Fonction qui pousse le flot vers des sommets de hauteurs inf
bool push(Graph *graph, int vertexId)
{
  Vertex u = graph->vertices[vertexId];
  for(int id : u.leavingEdgesId)
  {
    Edge e = graph->edges[id];
    Vertex v = graph->vertices[e.endId];
    if(e.flow == e.maxCapacity)
    {
      continue;
    }
    if(u.height > v.height)
    {
      int f = min(e.maxCapacity - e.flow, u.exceedingFlow);
      u.exceedingFlow -= f;
      e.flow += f;
      v.exceedingFlow += f;
      e.increaseResidualCapacity(*graph, f);
      return true;
    }
  }
  return false;
}

//Mise à jour des hauteurs pour pouvoir push
void relabel(Graph *graph, int vertexId)
{
  Vertex u = graph->vertices[vertexId];
  int h_best = INT_MAX;
  for(int id : u.leavingEdgesId)
  {
    Vertex v = graph->vertices[graph->edges[id].endId];
    if(graph->edges[id].flow == graph->edges[id].maxCapacity)
    {
      continue;
    }
    //actualisation des hauteurs
    if(v.height < h_best)
    {
      h_best = v.height;
      u.height = h_best + 1;
    }
  }
}

void preflowPush(Graph *graph)
{
  Graph *graph_res = graph->getResidualGraph();

  //Initialisation des valeurs
  for(int i = 0; i < graph->nbVertices; ++i)
  {
    graph->vertices[i].exceedingFlow = 0;
    graph->vertices[i].height = 0;
  }
  graph->vertices[graph->src].height = graph->nbVertices;
  for(int id : graph->vertices[graph->src].leavingEdgesId)
  {
    graph->edges[id].flow = graph->edges[id].maxCapacity;
    int end = graph->edges[id].endId;
    graph->vertices[end].exceedingFlow = graph->edges[end].flow;
  }
  for(int id : graph_res->vertices[graph->src].enteringEdgesId)
  {
    graph_res->edges[id].flow = 0;
  }
  //Tant qu'il existe du flot en exces
  while(overFlow(graph) != -1)
  {
    int v = overFlow(graph);
    if(!push(graph, v))
    {
      relabel(graph, v);
    }
  }
  std::cout << graph->vertices[graph->sink].exceedingFlow << std::endl;
}
