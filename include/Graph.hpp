#ifndef GRAPH_H
#define GRAPH_H

template <typename V>
struct Vertex;

template <typename E>
struct Edge;

template <typename V, typename E>
class Graph
{
    public:
    Graph();
    Graph(Graph &G);
    virtual ~Graph();
    Graph operator=(const Graph &G);

    int getNbEdges() const;
    int getNbVertices() const;

    virtual void addVertex(const V &VertexData) = 0;
    virtual void removeVertex(const Vertex<V> &v) = 0;

    virtual void addEdge(const Vertex<V> &v1, const Vertex<V> &v2) = 0;
    virtual void removeEdge(const Edge<E> &e) = 0;

    //reset
    virtual void removeAll() = 0;

    virtual bool existEdge(const Vertex<V> &v1, const Vertex<V> &v2) const = 0;

    virtual Vertex<V> &getNthVertex(const int n) const = 0;
    virtual Edge<E> &getNthEdge(const Vertex<V> &v, const int n) const = 0;
    virtual Vertex<V> &getNthSuccOfV(const Vertex<V> &v, const int n) const = 0;
    virtual int getNbOfSuccOfV(const Vertex<V> &v) const = 0;

    void startVertexSearch();
    virtual bool existCurrVertex() const = 0;
    virtual Vertex<V> &getCurrVertex() const = 0;
    void goToNextVertex();

    void startEdgeSearchOfV(const Vertex<V> &v);
    virtual bool existCurrEdgeOfV(const Vertex<V> &v) const = 0;
    virtual Edge<E> &getCurrEdgeOfV(const Vertex<V> &v) const = 0;
    void goToNextEdgeOfV(const Vertex<V> &v);

    void startSuccSearchOfV(const Vertex<V> &v);
    virtual bool existSuccOfV(const Vertex<V> &v) const = 0;
    virtual Vertex<V> &getSuccOfV(const Vertex<V> &v) const = 0;

    std::string toString() const;
    template <typename VV, typename EE>
    friend std::ostream &operator<<(std::ostream &o, const Graph<VV, EE> &g);

    V &getValueOfV(const Vertex<V> &v);
    E &getValueOfE(const Edge<E> &e);
    void setValueOfV(const Vertex<V> &v, V *value);
    void setValueOfE(const Edge<E> &e, E *value);

    protected:
    int nbEdges;
    int nbVertices;
    int vertexCursos;
    int edgeCursor;
    void clone(Graph<V, E> &G);
};

#endif