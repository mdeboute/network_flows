#include <iostream>
#include "algorithm.hpp"
#include "Graph.hpp"
#include <cstdio>
#include <limits.h>
#include <climits> // for INT_MAX
#include <queue>
#include <string.h>

// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.  The
// function also detects negative weight cycle
int BellmanFord(Graph *graph, int pred[])
{
    int V = graph->nbVertices;
    int E = graph->nbEdges;
    int dist[V];

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[graph->src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            if(graph->edges[j].residualCapacity == 0) continue;
            int u = graph->edges[j].startId;
            int v = graph->edges[j].endId;
            int weight = graph->edges[j].cost;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
                pred[v] = u;
        }
    }

    // Step 3: check for negative-weight cycles.  The above
    // step guarantees shortest distances if graph doesn't
    // contain negative weight cycle.  If we get a shorter
    // path, then there is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edges[i].startId;
        int v = graph->edges[i].endId;
        int weight = graph->edges[i].cost;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle!\n");
            return u; // If negative cycle is detected, simply
                    // return
        }
    }

    printf("Graph doesn't contain negative weight cycle!\n");
    std::cout << std::endl;
    printArr(dist, V);

    return -1;
}

void cycleCancelling(Graph *originGraph){
    Graph *graph = originGraph->getResidualGraph();
    graph->fromMultipleToOne();
    shortestAugmentingPath(graph);

    int pred[graph->vertices.size()];
    int probVertex = BellmanFord(graph, pred);

    int initialVertex = probVertex;
    while(probVertex != -1){
        std::vector<int> edgesToChange;
        int minResCap = 1;

        int idMinEdge;
        for(int i = 0; i < graph->vertices[probVertex].leavingEdgesId.size(); i++){
            if(graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].endId == pred[probVertex] 
                    && graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].residualCapacity != 0
                    && graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].cost < graph->edges[idMinEdge].cost){
                idMinEdge = graph->vertices[probVertex].leavingEdgesId[i];
            }
        }
        edgesToChange.push_back(idMinEdge);
        if(graph->edges[idMinEdge].residualCapacity < minResCap){
            minResCap = graph->edges[idMinEdge].residualCapacity;
        }
        probVertex = pred[probVertex];

        while(probVertex != initialVertex){
            int idMinEdge;
            for(int i = 0; i < graph->vertices[probVertex].leavingEdgesId.size(); i++){
                if(graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].endId == pred[probVertex] 
                        && graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].residualCapacity != 0
                        && graph->edges[graph->vertices[probVertex].leavingEdgesId[i]].cost < graph->edges[idMinEdge].cost){
                    idMinEdge = graph->vertices[probVertex].leavingEdgesId[i];
                }
            }
            if(graph->edges[idMinEdge].residualCapacity < minResCap){
                minResCap = graph->edges[idMinEdge].residualCapacity;
            }
            probVertex = pred[probVertex];
        }

        for(int i = 0; i < edgesToChange.size(); i++){
            graph->edges[edgesToChange[i]].increaseResidualCapacity(*graph, minResCap);
        }

        probVertex = BellmanFord(graph, pred);
    }
}

void retreat(Graph *graph, int i, int dist[]){
    int min = INT_MAX;
    for(int j = 0; j < graph->vertices[i].leavingEdgesId.size(); j++){
        if(graph->edges[graph->vertices[i].leavingEdgesId[j]].residualCapacity > 0 && min > dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1){
            min = dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1;
        }
    }
    dist[i] = min;
}

void augment(Graph *graph, int pred[]){
    int vertexId = graph->sink;
    int min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
    while(vertexId != graph->src){
        if(min > graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity){
            min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
        }
        vertexId = pred[vertexId];
    }
    vertexId = graph->sink;
    while(vertexId != graph->src){
        graph->getEdgeFromVerticesId(vertexId, pred[vertexId]).increaseResidualCapacity(*graph, min);
        vertexId = pred[vertexId];
    }
}

void distanceLabelling(Graph *graph, int dist[]){
    bool marks[graph->nbVertices];
    for(int i = 0; i < graph->nbVertices; i++){
        marks[i] = false;
        dist[i] = -1;
    }
    marks[graph->sink] = true;
    dist[graph->sink] = 0;
    std::queue<int> List;
    List.push(graph->sink);
    while(List.size() > 0){
        bool hasAdmissibleArc = false;
        for(int i = 0; i < graph->vertices[List.front()].leavingEdgesId.size(); i++){
            if(marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] == false){
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

void shortestAugmentingPath(Graph *graph){
    int dist[graph->nbVertices];
    distanceLabelling(graph, dist);
    int pred[graph->nbVertices];
    for(int i = 0; i < graph->nbVertices; i++){
        pred[i] = -1;
    }

    int i = graph->src;
    while(dist[graph->src] < graph->nbVertices){
        bool hasAdmissibleArc = false;
        for(int p = 0; p < graph->vertices[i].leavingEdgesId.size(); p++){
            int j = graph->edges[graph->vertices[i].leavingEdgesId[p]].endId;
            if(graph->getEdgeFromVerticesId(i,j).residualCapacity > 0 && dist[i] == dist[j] + 1){
                hasAdmissibleArc = true;
                pred[j] = i;  //advance(i) cf. pdf
                i = j;
                if(i == graph->sink){
                    augment(graph, pred);
                    i = graph->src;
                }
                break;
            }
        }
        if(hasAdmissibleArc == false){
            retreat(graph, i, dist);
            if(i != graph->src){
                i = pred[i];
            }
        }
    }
}