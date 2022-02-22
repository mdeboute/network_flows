#include <iostream>
#include "algorithm.hpp"
#include "Graph.hpp"
#include "checker.hpp"
#include <cstdio>
#include <limits.h>
#include <climits> // for INT_MAX
#include <queue>
#include <string.h>
#include <ctime>

// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm. The
// function also detects negative weight cycle
int BellmanFord(Graph *graph, int pred[])
{
    int V = graph->nbVertices;
    int E = graph->nbEdges;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[graph->src] = 0;

    for (int i = 1; i < V ; i++)
    {
        for (int j = 0; j < E; j++)
        {
            if (graph->edges[j].residualCapacity == 0)
                continue;
            int u = graph->edges[j].startId;
            int v = graph->edges[j].endId;
            int weight = graph->edges[j].cost;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        }
    }

    // for(int i = 0; i < V; i++){
    //     std::cout << pred[i];
    // }
    // std::cout << std::endl;

    for (int i = 0; i < E; i++)
    {
        if (graph->edges[i].residualCapacity == 0)
            continue;
        int u = graph->edges[i].startId;
        int v = graph->edges[i].endId;
        int weight = graph->edges[i].cost;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle!\n");
            return u;
        }
    }

    printf("Graph doesn't contain negative weight cycle!\n");
    // graph->print();
    return -1;
}

void cycleCancelling(Graph *originGraph)
{
    originGraph->fromMultipleToOne();
    
    originGraph->removeLonelyNodes();
    
    Graph noParallelGraph(originGraph->nbVertices);

    originGraph->switchOffParallel(&noParallelGraph);
    
    shortestAugmentingPath(&noParallelGraph);

    originGraph->switchOnParallel(&noParallelGraph);

    Graph *graph = originGraph->getResidualGraph(false);

    int pred[graph->vertices.size()];
    int probVertex = BellmanFord(graph, pred);

    int initialVertex = probVertex;
    int a = 0;
    while (probVertex != -1)
    {
        //std::cout << "nb rounds :" << a << std::endl;
        a ++;
        std::vector<int> edgesToChange;

        int idMinEdge = -1;
        for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
        {
            int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
            int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
            int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
            if (idStartVertex == pred[probVertex] && resCapEdge != 0 && (costEdge < graph->edges[idMinEdge].cost || idMinEdge == -1))
            {
                idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
            }
        }
        if (idMinEdge == -1)
        {
            std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
        }
        edgesToChange.push_back(idMinEdge);
        int minResCap = graph->edges[idMinEdge].residualCapacity;
        probVertex = pred[probVertex];

        while (probVertex != initialVertex)
        {
            int idMinEdge = -1;
            for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
            {
                int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
                int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
                int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
                if (idStartVertex == pred[probVertex] && resCapEdge != 0 && (costEdge < graph->edges[idMinEdge].cost || idMinEdge == -1))
                {
                    idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
                }
            }
            if (idMinEdge == -1)
            {
                std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
            }
            if (graph->edges[idMinEdge].residualCapacity < minResCap)
            {
                minResCap = graph->edges[idMinEdge].residualCapacity;
            }
            edgesToChange.push_back(idMinEdge);
            probVertex = pred[probVertex];
        }

        for (int i = 0; i < edgesToChange.size(); i++)
        {
            graph->edges[edgesToChange[i]].increaseResidualCapacity(*graph, -minResCap);
        }

        probVertex = BellmanFord(graph, pred);
    }
    std::cout << "wazai" << std::endl;
    originGraph->fillGraphFromResidual(graph);
    std::cout << "wazai" << std::endl;
    std::cout << validFlow(originGraph) << std::endl;

}

void retreat(Graph *graph, int i, int dist[])
{
    int min = INT_MAX;
    for (int j = 0; j < graph->vertices[i].leavingEdgesId.size(); j++)
    {
        if (graph->edges[graph->vertices[i].leavingEdgesId[j]].residualCapacity > 0 && min > dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1)
        {
            min = dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1;
        }
    }
    dist[i] = min;
}

void augment(Graph *graph, int pred[])
{
    int vertexId = graph->sink;
    int min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
    while (vertexId != graph->src)
    {
        if (min > graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity)
        {
            min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
        }
        vertexId = pred[vertexId];
    }
    vertexId = graph->sink;
    while (vertexId != graph->src)
    {
        graph->getEdgeFromVerticesId(vertexId, pred[vertexId]).increaseResidualCapacity(*graph, min);
        vertexId = pred[vertexId];
    }
}

void distanceLabelling(Graph *graph, int dist[])
{
    bool marks[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        marks[i] = false;
        dist[i] = -1;
    }
    marks[graph->sink] = true;
    dist[graph->sink] = 0;
    std::queue<int> List;
    List.push(graph->sink);
    while (List.size() > 0)
    {
        bool hasAdmissibleArc = false;
        for (int i = 0; i < graph->vertices[List.front()].leavingEdgesId.size(); i++)
        {
            if (marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] == false)
            {
                hasAdmissibleArc = true;
                marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] = true;
                dist[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] = dist[List.front()] + 1;
                List.push(graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId);
            }
        }
        List.pop();
    }
    return;
}

void shortestAugmentingPath(Graph *originGraph)
{

    originGraph->removeLonelyNodes();

    Graph *graph = originGraph->getResidualGraph(true);
    int dist[graph->nbVertices];
    distanceLabelling(graph, dist);
    int pred[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        pred[i] = -1;
    }

    int i = graph->src;
    while (dist[graph->src] < graph->nbVertices)
    {
        bool hasAdmissibleArc = false;
        for (int p = 0; p < graph->vertices[i].leavingEdgesId.size(); p++)
        {
            int j = graph->edges[graph->vertices[i].leavingEdgesId[graph->vertices[i].height]].endId;
            graph->vertices[i].height += 1;
            if (graph->vertices[i].height == graph->vertices[i].nbLeavingEdges)
                graph->vertices[i].height = 0;
            if (graph->getEdgeFromVerticesId(i, j).residualCapacity > 0 && dist[i] == dist[j] + 1)
            {
                hasAdmissibleArc = true;
                pred[j] = i; // advance(i) cf. pdf
                i = j;
                if (i == graph->sink)
                {
                    augment(graph, pred);
                    i = graph->src;
                }
                break;
            }
        }

        if (hasAdmissibleArc == false)
        {
            retreat(graph, i, dist);
            if (i != graph->src)
            {
                i = pred[i];
            }
        }
    }
    originGraph->fillGraphFromResidual(graph);
}
