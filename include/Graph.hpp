#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"

class Graph
{
public:
    // attributs
    int nbVertices;
    int nbEdges;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    int src;
    int sink;

    // méthodes
    Graph(int nbVertices, int nbEdges, int src, int sink, int edgeArray[][3]);
    Graph(int nbVertices, int nbEdges, int edgeArray[][5]); // ancien constructeur
    Graph(int nbVertices);                                  // pour créer un graphe sans arêtes, utile lors de la création des graphes résiduels
    void print();
    void addVertex();
    void addEdge(Edge edge);
    void removeEdge(int edgeId);
    Graph *getResidualGraph();
    Graph *getResidualGraph(bool fuseParallelEdges);             // ne pas oublier de faire appel à delete pour éviter les fuites mémoires, (en vrai c'est pas grave)
    void increaseFlow(int edgeId, int increase);                 // augmente le flot de l'arête edgeId, les négatifs sont tolérés
    void setFlow(int edgeId, int newFlow);                       // change le flot de l'arête edgeId
    Edge &getEnteringEdge(int vertexId, int edgeId);             // retourne la n-ième arête entrante du sommet m (m=vertexId,n=edgeId)
    Edge &getLeavingEdge(int vertexId, int edgeId);              // retourne la n-ième arête sortante du sommet m (m=vertexId,n=edgeId)
    Vertex &getEnteringNeighbour(int vertexId, int neighbourId); // retourne le n-ième voisin entrant du sommet m (m=vertexId,n=neighbourId)
    Vertex &getLeavingNeighbour(int vertexId, int neighbourId);  // retourne le n-ième voisin sortant du sommet m (m=vertexId,n=neighbourId)
    Vertex &getStart(int edgeId);                                // retourne le sommet de départ de l'arête n (n=edgeId)
    Vertex &getEnd(int edgeId);                                  // retourne le sommet de d'arrivée de l'arête n (n=edgeId)
    Edge &getPairedEdge(int edgeId);                             // retourne l'arc associé de l'arête n (n=edgeId)
    Edge &getEdgeFromVerticesId(int vertexId1, int vertexId2);   // retourne l'arc associé à deux ID de sommets en paramètres
    int getValueObjMaxFlow();
    void fromMultipleToOne();
};

#endif