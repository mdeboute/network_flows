#include <iostream>
#include <vector>
#include "Structures.hpp"

Vertex::Vertex(int id)
{
  this->id = id;
}

Edge::Edge(int id, int cost, int minCapacity, int maxCapacity, int startId, int endId)
{
  this->id = id;
  this->cost = cost;
  this->minCapacity = minCapacity;
  this->maxCapacity = maxCapacity;
  this->startId = startId;
  this->endId = endId;
  this->flow = 0; // normalement pas nécessaire mais c++ l'initialise à 1 sinon (??)
}

Graph::Graph(int nbVertices, int nbEdges, int edgeArray[][edgeInfoAmount])
{
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
  std::cout << ", flow " << flow << ", minCap " << minCapacity << ", maxCap " << maxCapacity << ", cost " << cost << "\n";
}

void Vertex::print()
{
  std::cout << "Vertex " << id << "\n";
}

void Graph::print()
{
  for (Vertex vertex : vertices)
  {
    vertex.print();
    for (int edgeID : vertex.leavingEdgesId)
    {
      Edge edge = edges[edgeID];
      edge.print();
    }
  }
}
