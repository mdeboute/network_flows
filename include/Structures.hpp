#include <vector>
#ifndef structs
#define structs



class Edge;
class Graph;

class Vertex
{
  public:
    //attributs
    int id;
    int nbEnteringEdges;
    int nbLeavingEdges;
    std::vector<int> enteringEdgesId;
    std::vector<int> leavingEdgesId;

    //méthodes
    Vertex(int id);
    void print();
    Edge& getEnteringEdge(Graph& graph,int id); //retourne la n-ième arête entrante (n=id)
    Edge& getLeavingEdge(Graph& graph,int id); //retourne la n-ième arête sortante (n=id)
    Vertex& getEnteringNeighbour(Graph& graph,int id); //retourne le n-ième voisin entrant (n=id)
    Vertex& getLeavingNeighbour(Graph& graph,int id); //retourne le n-ième voisin sortant (n=id)
};



class Edge
{
  public:
    //attributs
    int id;
    int cost;
    int minCapacity;
    int maxCapacity;
    int flow;
    int startId;
    int endId;
    int pairedEdgeId;

    //méthodes
    Edge(int id,int cost,int minCapacity,int maxCapacity,int startId,int endId);
    void print();
    void increaseFlow(Graph& graph,int increase); //les négatifs sont tolérés
    void setFlow(Graph& graph,int newFlow);
    Vertex& getStart(Graph& graph);
    Vertex& getEnd(Graph& graph);
    Edge& getPairedEdge(Graph& graph);
};



class Graph
{
  public:
    //attributs
    static const int edgeInfoAmount = 5;
    int nbVertices;
    int nbEdges;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    //méthodes
    Graph(int nbVertices,int nbEdges,int edgeArray[][edgeInfoAmount]);
    Graph(int nbVertices); //pour créer un graphe sans arêtes, utile lors de la création des graphes résiduels
    void print();
    void addVertex();
    void addEdge(Edge edge);
    Graph* getResidualGraph(); //ne pas oublier de faire appel à delete pour éviter les fuites mémoires, (en vrai c'est pas grave)
    void increaseFlow(int edgeId,int increase); //augmente le flot de l'arête edgeId, les négatifs sont tolérés
    void setFlow(int edgeId,int newFlow); //change le flot de l'arête edgeId
    Edge& getEnteringEdge(int vertexId,int edgeId); //retourne la n-ième arête entrante du sommet m (m=vertexId,n=edgeId)
    Edge& getLeavingEdge(int vertexId,int edgeId); //retourne la n-ième arête sortante du sommet m (m=vertexId,n=edgeId)
    Vertex& getEnteringNeighbour(int vertexId,int neighbourId); //retourne le n-ième voisin entrant du sommet m (m=vertexId,n=neighbourId)
    Vertex& getLeavingNeighbour(int vertexId,int neighbourId); //retourne le n-ième voisin sortant du sommet m (m=vertexId,n=neighbourId)
    Vertex& getStart(int edgeId); //retourne le sommet de départ de l'arête n (n=edgeId)
    Vertex& getEnd(int edgeId); //retourne le sommet de d'arrivée de l'arête n (n=edgeId)
    Edge& getPairedEdge(int edgeId); //retourne l'arc associé de l'arête n (n=edgeId)
};



#endif
