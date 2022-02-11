#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

class Edge;
class Graph;

class Vertex
{
public:
    // attributs
    int id;
    int exceedingFlow;
    int nbEnteringEdges;
    int nbLeavingEdges;
    std::vector<int> enteringEdgesId;
    std::vector<int> leavingEdgesId;

    // méthodes
    Vertex(int id, int exceedingFlow);
    Vertex(int id);
    void print();
    Edge &getEnteringEdge(Graph &graph, int id);        // retourne la n-ième arête entrante (n=id)
    Edge &getLeavingEdge(Graph &graph, int id);         // retourne la n-ième arête sortante (n=id)
    Vertex &getEnteringNeighbour(Graph &graph, int id); // retourne le n-ième voisin entrant (n=id)
    Vertex &getLeavingNeighbour(Graph &graph, int id);  // retourne le n-ième voisin sortant (n=id)
};

#endif