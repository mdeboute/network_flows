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
    int startId = edgeArray[id][0];
    int endId = edgeArray[id][1];

    Edge newEdge(id,edgeArray[id][2],edgeArray[id][3],&vertices[startId],&vertices[endId]);
    edges.push_back(newEdge);

    //affectation des listes d'adjacences des sommets
    vertices[startId].nbLeavingEdges += 1;
    vertices[startId].leavingEdges.push_back(&edges[id]);

    vertices[endId].nbEnteringEdges += 1;
    vertices[endId].enteringEdges.push_back(&edges[id]);
  }
}




void Vertex::print()
{
  std::cout << "Vertex " << id << "\n";
}



void Graph::print()
{
  for(Vertex vertex : vertices){
    vertex.print();
  }
}
