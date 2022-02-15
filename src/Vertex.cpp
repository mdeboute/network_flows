#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Graph.hpp"

Vertex::Vertex(int id)
{
    this->id = id;
    exceedingFlow = 0;
    height = 0;
    nbEnteringEdges = 0;
    nbLeavingEdges = 0;
}

Vertex::Vertex(int id, int exceedingFlow)
{
    this->id = id;
    this->exceedingFlow = exceedingFlow;
    height = 0;
    nbEnteringEdges = 0;
    nbLeavingEdges = 0;
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

// getters de la classe Vertex
Edge &Vertex::getEnteringEdge(Graph &graph, int id) { return graph.edges[enteringEdgesId[id]]; }
Edge &Vertex::getLeavingEdge(Graph &graph, int id) { return graph.edges[leavingEdgesId[id]]; }
Vertex &Vertex::getEnteringNeighbour(Graph &graph, int id) { return graph.vertices[getEnteringEdge(graph, id).startId]; }
Vertex &Vertex::getLeavingNeighbour(Graph &graph, int id) { return graph.vertices[getLeavingEdge(graph, id).endId]; }
