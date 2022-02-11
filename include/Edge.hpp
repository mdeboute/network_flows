#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

class Graph;
class Vertex;

class Edge
{
public:
    // attributs
    int id;
    int cost;
    int minCapacity;
    int maxCapacity;
    int residualCapacity;
    int flow;
    int startId;
    int endId;
    int pairedEdgeId;

    // méthodes
    Edge(int id, int cost, int minCapacity, int maxCapacity, int startId, int endId);
    Edge(int id, int startId, int endId, int maxCapacity);
    void print();
    void increaseFlow(int increase); // les négatifs sont tolérés
    void setFlow(int newFlow);
    void increaseResidualCapacity(Graph &graph, int increase); // la capacité résiduelle de l'arc inverse est changée automatiquement, les négatifs sont tolérés
    void setResidualCapacity(Graph &graph, int newCap);        // la capacité résiduelle de l'arc inverse est changée automatiquement
    Vertex &getStart(Graph &graph);
    Vertex &getEnd(Graph &graph);
    Edge &getPairedEdge(Graph &graph);
};

#endif