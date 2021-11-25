#include <iostream>
#include <vector>
#include "Structures.hpp"



Vertex::Vertex(int id)
{
  this->id = id;
}



Edge::Edge(int id,int weight,int capacity,Vertex* start,Vertex* end)
{
  this->id = id;
  this->weight = weight;
  this->capacity = capacity;
  this->start = start;
  this->end = end;
}



Graph::Graph(int nbVertices,int nbEdges,int edgeArray[][4])
{
  this->nbVertices = nbVertices;
  this->nbEdges = nbEdges;

  //création des sommets
  //les listes d'adjacences ne sont pas directement affectées
  for(int id=0;id<nbVertices;id++){
    Vertex newVertice(id);
    vertices.push_back(newVertice);
  }

  //création des arêtes
  for(int id=0;id<nbEdges;id++){

    int weight = edgeArray[id][2];
    int capacity = edgeArray[id][3];
    Vertex* start = &vertices[edgeArray[id][0]];
    Vertex* end = &vertices[edgeArray[id][1]];

    Edge newEdge(id,weight,capacity,start,end);
    edges.push_back(newEdge);

    //affectation des listes d'adjacences des sommets
    start->nbLeavingEdges += 1;
    start->leavingEdges.push_back(&edges[id]);

    end->nbEnteringEdges += 1;
    end->enteringEdges.push_back(&edges[id]);
  }
}



void Vertex::printWithNeighbors()
{
  std::cout << "Vertex " << id << "\n";

  std::cout << "Entering neighbors: ";
  for(Edge* edge : enteringEdges){
    std::cout << edge->start->id << " ";
  }
  std::cout << "\n";

  std::cout << "Leaving neighbors: ";
  for(Edge* edge : leavingEdges){
    std::cout << edge->end->id << " ";
  }
  std::cout << "\n";
}




void Vertex::printWithEdges()
{
  std::cout << "Vertex " << id << "\n";

  std::cout << "Entering edges: ";
  for(Edge* edge : enteringEdges){
    std::cout << edge->id << " ";
  }
  std::cout << "\n";

  std::cout << "Leaving edges: ";
  for(Edge* edge : leavingEdges){
    std::cout << edge->id << " ";
  }
  std::cout << "\n";
}



void Graph::print()
{
  for(Vertex vertex : vertices){
    vertex.printWithNeighbors();
  }
}
