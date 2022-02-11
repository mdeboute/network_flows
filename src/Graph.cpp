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
    this->nbEdges = 0;
    this->src = -1;
    this->sink = -1;
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

Graph *Graph::getResidualGraph()
{
    return getResidualGraph(false);
}

//à ajouter le booléen qui indique la fusion des arcs parallèles
Graph *Graph::getResidualGraph(bool fuseParallelEdges)
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

    // fusion des arc parralèles (pour les problèmes de flot maximum)
    if (fuseParallelEdges)
    {
        for (int vertexIndex = 0; vertexIndex < residualGraph->nbVertices; vertexIndex++)
        {
            for (int edgeIndex1 = 0; edgeIndex1 < residualGraph->vertices[vertexIndex].nbLeavingEdges; edgeIndex1++)
            {
                int edgeId1 = residualGraph->vertices[vertexIndex].leavingEdgesId[edgeIndex1];
                for (int edgeIndex2 = edgeIndex1 + 1; edgeIndex2 < residualGraph->vertices[vertexIndex].nbLeavingEdges; edgeIndex2++)
                {
                    int edgeId2 = residualGraph->vertices[vertexIndex].leavingEdgesId[edgeIndex2];
                    if (residualGraph->edges[edgeId1].startId == residualGraph->edges[edgeId2].startId and residualGraph->edges[edgeId1].endId == residualGraph->edges[edgeId2].endId)
                    {
                        residualGraph->edges[residualGraph->vertices[vertexIndex].leavingEdgesId[edgeIndex1]].residualCapacity += residualGraph->edges[residualGraph->vertices[vertexIndex].leavingEdgesId[edgeIndex2]].residualCapacity;
                        residualGraph->removeEdge(residualGraph->vertices[vertexIndex].leavingEdgesId[edgeIndex2]);
                        edgeIndex2--;
                        //éventuellment gérer les pairedEdgeId
                    }
                }
            }
        }
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

void Graph::removeEdge(int edgeId)
{

    for (int vertexIndex = 0; vertexIndex < nbVertices; vertexIndex++)
    {

        for (int edgeIndex = 0; edgeIndex < vertices[vertexIndex].nbLeavingEdges; edgeIndex++)
        {

            if (vertices[vertexIndex].leavingEdgesId[edgeIndex] == edgeId)
            {
                vertices[vertexIndex].leavingEdgesId.erase(vertices[vertexIndex].leavingEdgesId.begin() + edgeIndex);
                edges[edgeId].getStart(*this).nbLeavingEdges += -1;
                edgeIndex += -1;
            }
            else if (vertices[vertexIndex].leavingEdgesId[edgeIndex] > edgeId)
            {
                vertices[vertexIndex].leavingEdgesId[edgeIndex] += -1;
            }
        }

        for (int edgeIndex = 0; edgeIndex < vertices[vertexIndex].nbEnteringEdges; edgeIndex++)
        {

            if (vertices[vertexIndex].enteringEdgesId[edgeIndex] == edgeId)
            {
                vertices[vertexIndex].enteringEdgesId.erase(vertices[vertexIndex].enteringEdgesId.begin() + edgeIndex);
                edges[edgeId].getEnd(*this).nbEnteringEdges += -1;
                edgeIndex += -1;
            }
            else if (vertices[vertexIndex].enteringEdgesId[edgeIndex] > edgeId)
            {
                vertices[vertexIndex].enteringEdgesId[edgeIndex] += -1;
            }
        }
    }

    for (int edgeIndex = 0; edgeIndex < nbEdges; edgeIndex++)
    {
        if (edges[edgeIndex].id == edgeId)
        {
            edges.erase(edges.begin() + edgeIndex);
            nbEdges += -1;
            edgeIndex += -1;
        }
        else
        {
            if (edges[edgeIndex].id > edgeId)
            {
                edges[edgeIndex].id += -1;
            }
            if (edges[edgeIndex].pairedEdgeId > edgeId)
            {
                edges[edgeIndex].pairedEdgeId += -1;
            }
        }
    }
}
Edge &Graph::getEdgeFromVerticesId(int vertexId1, int vertexId2){
  for(int i = 0; i < this->vertices[vertexId1].leavingEdgesId.size(); i++){
    if(this->edges[this->vertices[vertexId1].leavingEdgesId[i]].endId == vertexId2){
      return this->edges[this->vertices[vertexId1].leavingEdgesId[i]];
    }
  }
  return this->edges[0];  //Ne fait jamais ce return, la boucle for implique un return à chaque fois si le code qui appelle la fonction est le bon. 
                          //C'est là pour évite un message d'erreur
}

int Graph::getValueObjMaxFlow(){
    int sumFlows = 0;
    for(int i = 0; i < this->vertices[this->src].enteringEdgesId.size(); i++){
        sumFlows += this->edges[this->vertices[this->src].enteringEdgesId[i]].residualCapacity;
    }
    return sumFlows + 1;
}

void Graph::fromMultipleToOne(){
    std::vector<int> srcNodes;
    std::vector<int> sinkNodes;

    for(int i = 0; i < this->vertices.size(); i++){
        if(this->vertices[i].exceedingFlow > 0){
            srcNodes.push_back(i);
        }
        if(this->vertices[i].exceedingFlow < 0){
            sinkNodes.push_back(i);
        }
    }

    if(srcNodes.size() > 1){
        this->src = this->vertices.size();
        this->addVertex();
        for(int i = 0; i < srcNodes.size(); i++){
            Edge newEdge(this->edges.size(), this->src, srcNodes[i], this->vertices[srcNodes[i]].exceedingFlow);
            this->addEdge(newEdge);
        }
    }

    if(sinkNodes.size() > 1){
        this->sink = this->vertices.size();
        this->addVertex();
        for(int i = 0; i < sinkNodes.size(); i++){
            Edge newEdge(this->edges.size(), this->sink, sinkNodes[i], this->vertices[sinkNodes[i]].exceedingFlow);
            this->addEdge(newEdge);
        }
    }
}

// getters de la classe Graph
Edge &Graph::getEnteringEdge(int vertexId, int edgeId) { return vertices[vertexId].getEnteringEdge(*this, edgeId); }
Edge &Graph::getLeavingEdge(int vertexId, int edgeId) { return vertices[vertexId].getLeavingEdge(*this, edgeId); }
Vertex &Graph::getEnteringNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getEnteringNeighbour(*this, neighbourId); }
Vertex &Graph::getLeavingNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getLeavingNeighbour(*this, neighbourId); }
Vertex &Graph::getStart(int edgeId) { return edges[edgeId].getStart(*this); }
Vertex &Graph::getEnd(int edgeId) { return edges[edgeId].getEnd(*this); }
Edge &Graph::getPairedEdge(int edgeId) { return edges[edgeId].getPairedEdge(*this); }
