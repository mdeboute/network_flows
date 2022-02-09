#include <iostream>
#include <vector>
#include "Structures.hpp"

Vertex::Vertex(int id)
{
  this->id = id;
  exceedingFlow = 0;
}

Vertex::Vertex(int id, int exceedingFlow)
{
  this->id = id;
  this->exceedingFlow = exceedingFlow;
}

Edge::Edge(int id, int cost, int minCapacity, int maxCapacity, int startId, int endId)
{
  this->id = id;
  this->cost = cost;
  this->minCapacity = minCapacity;
  this->maxCapacity = maxCapacity;
  residualCapacity = 0;
  this->startId = startId;
  this->endId = endId;
  this->flow = 0; // normalement pas nécessaire mais c++ l'initialise à 1 sinon (??)
}

Edge::Edge(int id, int startId, int endId, int maxCapacity)
{
  this->id = id;
  this->cost = 0;
  this->minCapacity = 0;
  this->maxCapacity = maxCapacity;
  residualCapacity = 0;
  this->startId = startId;
  this->endId = endId;
  this->flow = 0; // normalement pas nécessaire mais c++ l'initialise à 1 sinon (??)
}

Graph::Graph(int nbVertices, int nbEdges, int src, int sink, int edgeArray[][3])
{
  this->nbVertices = nbVertices;
  this->nbEdges = nbEdges;
  this->src = src;
  this->sink = sink;

  // création des sommets
  // les listes d'adjacences ne sont pas directement affectées
  for (int id = 0; id < nbVertices; id++)
  {
    Vertex newVertice(id);
    vertices.push_back(newVertice);
  }

  // création des arêtes
  for (int id = 0; id < nbEdges; id++)
  {

    int startId = edgeArray[id][0];
    int endId = edgeArray[id][1];
    int maxCapacity = edgeArray[id][2];

    Edge newEdge(id, startId, endId, maxCapacity);
    edges.push_back(newEdge);

    // affectation des listes d'adjacences des sommets
    vertices[newEdge.startId].nbLeavingEdges += 1;
    vertices[newEdge.startId].leavingEdgesId.push_back(id);

    vertices[newEdge.endId].nbEnteringEdges += 1;
    vertices[newEdge.endId].enteringEdgesId.push_back(id);
  }
}

Graph::Graph(int nbVertices, int nbEdges, int edgeArray[][5])
{
  src = -1;
  sink = -1;
  this->nbVertices = nbVertices;
  this->nbEdges = nbEdges;

  // création des sommets
  // les listes d'adjacences ne sont pas directement affectées
  for (int id = 0; id < nbVertices; id++)
  {
    Vertex newVertice(id);
    vertices.push_back(newVertice);
  }

  // création des arêtes
  for (int id = 0; id < nbEdges; id++)
  {

    int cost = edgeArray[id][0];
    int minCapacity = edgeArray[id][1];
    int maxCapacity = edgeArray[id][2];
    int startId = edgeArray[id][3];
    int endId = edgeArray[id][4];

    Edge newEdge(id, cost, minCapacity, maxCapacity, startId, endId);
    edges.push_back(newEdge);

    // affectation des listes d'adjacences des sommets
    vertices[newEdge.startId].nbLeavingEdges += 1;
    vertices[newEdge.startId].leavingEdgesId.push_back(id);

    vertices[newEdge.endId].nbEnteringEdges += 1;
    vertices[newEdge.endId].enteringEdgesId.push_back(id);
  }
}

Graph::Graph(int nbVertices) // même constructeur mais sans arêtes
{
  this->nbVertices = nbVertices;
  for (int id = 0; id < nbVertices; id++)
  {
    Vertex newVertice(id);
    vertices.push_back(newVertice);
  }
}

void Edge::print()
{
  std::cout << "Edge " << id << ": from V" << startId << " to V" << endId;
  std::cout << ", flow " << flow << ", minCap " << minCapacity << ", maxCap " << maxCapacity << ", resCap " << residualCapacity << ", cost " << cost << "\n";
}

void Vertex::print()
{
  std::cout << "Vertex " << id << ": ";
  if (exceedingFlow != 0)
  {
    std::cout << ", casting " << exceedingFlow << " units of flow";
  }
  std::cout << "\n";
}

void Graph::print()
{
  std::cout << "Graph with " << nbVertices << " vertices and " << nbEdges << " edges\n";
  std::cout << "Source: " << src << ", Sink: " << sink << "\n";
  std::cout << std::endl;
  for (Vertex vertex : vertices)
  {
    vertex.print();
    std::cout << std::endl;
    for (int edgeID : vertex.leavingEdgesId)
    {
      Edge edge = edges[edgeID];
      edge.print();
    }
    std::cout << std::endl;
  }
}
