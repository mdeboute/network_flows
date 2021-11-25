#include <vector>
#ifndef structs
#define structs



class Edge;

class Vertex
{
  public:
    int id;
    int nbEnteringEdges;
    int nbLeavingEdges;
    std::vector<Edge*> enteringEdges;
    std::vector<Edge*> leavingEdges;

    Vertex(int id);
    void printWithEdges();
    void printWithNeighbors();
};



class Edge
{
  public:
    int id;
    int weight;
    int capacity;
    int flow;
    Vertex* start;
    Vertex* end;
    Edge* pairedEdge;

    Edge(int id,int weight,int capacity,Vertex* start,Vertex* end);
};



class Graph
{
  public:
    int nbVertices;
    int nbEdges;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    Graph(int nbVertices,int nbEdges,int edgeArray[][4]);
    void print();
    void addEdge(Edge edge);
    Graph* getResidualGraph();
};



#endif
