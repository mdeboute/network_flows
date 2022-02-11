#include <iostream>
#include <vector>
#include "Graph.hpp"

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

//à ajouter le booléen qui indique la fusion des arcs parallèles
Graph *Graph::getResidualGraph()
{
    Graph *residualGraph = new Graph(nbVertices);
    residualGraph->src = src;
    residualGraph->sink = sink;

    for (Edge &edge : edges)
    { // usage d'une référence sinon on itère sur des copies

        // arc résiduel
        int id = residualGraph->nbEdges;
        int cost = edge.cost;
        int startId = edge.startId;
        int endId = edge.endId;

        Edge residualEdge(id, cost, 0, 0, startId, endId);
        residualEdge.residualCapacity = edge.maxCapacity - edge.flow;
        residualEdge.pairedEdgeId = id + 1;

        // arc résiduel inverse
        int invId = id + 1;
        int invCost = -edge.cost;
        int invStartId = edge.endId;
        int invEndId = edge.startId;

        Edge inverseEdge(invId, invCost, 0, 0, invStartId, invEndId);
        inverseEdge.residualCapacity = edge.flow;
        inverseEdge.pairedEdgeId = id;

        residualGraph->addEdge(residualEdge);
        residualGraph->addEdge(inverseEdge);
    }
    return residualGraph;
}

void Graph::increaseFlow(int edgeId, int increase) { edges[edgeId].increaseFlow(increase); }
void Graph::setFlow(int edgeId, int newFlow) { edges[edgeId].setFlow(newFlow); }

void Graph::addVertex()
{
    Vertex newVertex(nbVertices);
    vertices.push_back(newVertex);
    nbVertices += 1;
}

void Graph::addEdge(Edge edge)
{
    edges.push_back(edge);

    vertices[edge.startId].nbLeavingEdges += 1;
    vertices[edge.startId].leavingEdgesId.push_back(nbEdges);

    vertices[edge.endId].nbEnteringEdges += 1;
    vertices[edge.endId].enteringEdgesId.push_back(nbEdges);

    nbEdges += 1;
}

// getters de la classe Graph
Edge &Graph::getEnteringEdge(int vertexId, int edgeId) { return vertices[vertexId].getEnteringEdge(*this, edgeId); }
Edge &Graph::getLeavingEdge(int vertexId, int edgeId) { return vertices[vertexId].getLeavingEdge(*this, edgeId); }
Vertex &Graph::getEnteringNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getEnteringNeighbour(*this, neighbourId); }
Vertex &Graph::getLeavingNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getLeavingNeighbour(*this, neighbourId); }
Vertex &Graph::getStart(int edgeId) { return edges[edgeId].getStart(*this); }
Vertex &Graph::getEnd(int edgeId) { return edges[edgeId].getEnd(*this); }
Edge &Graph::getPairedEdge(int edgeId) { return edges[edgeId].getPairedEdge(*this); }
