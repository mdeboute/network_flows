#include <iostream>
#include "algorithms.hpp"
#include "Structures.hpp"
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
void BellmanFord(Graph graph, int src)
{
    int V = graph.nbVertices;
    int E = graph.nbEdges;
    int dist[V];

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph.edges[j].startId;
            int v = graph.edges[j].endId;
            int weight = graph.edges[j].cost;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: check for negative-weight cycles.  The above
    // step guarantees shortest distances if graph doesn't
    // contain negative weight cycle.  If we get a shorter
    // path, then there is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph.edges[i].startId;
        int v = graph.edges[i].endId;
        int weight = graph.edges[i].cost;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle!\n");
            return; // If negative cycle is detected, simply
                    // return
        }
    }

    printf("Graph doesn't contain negative weight cycle!\n");
    std::cout << std::endl;
    printArr(dist, V);

    return;
}

void retreat(Graph graph, int i, int dist[]){
    int min = INT_MAX;
    for(int j = 0; j < graph.vertices[i].leavingEdgesId.size(); j++){
        if(graph.edges[graph.vertices[i].leavingEdgesId[j]].residualCapacity > 0 && min > dist[graph.vertices[i].getLeavingNeighbour(graph, j).id] + 1){
            min = dist[graph.vertices[i].getLeavingNeighbour(graph, j).id] + 1;
        }
    }
    dist[i] = min;
}

void augment(Graph graph, int pred[]){
    int vertexId = graph.sink;
    int min = graph.getEdgeFromVerticesId(vertexId, pred[vertexId]).residualCapacity;
    while(vertexId != graph.src){
        vertexId = pred[vertexId];
        if(min > graph.getEdgeFromVerticesId(vertexId, pred[vertexId]).residualCapacity){
            min = graph.getEdgeFromVerticesId(vertexId, pred[vertexId]).residualCapacity;
        }
    }
    vertexId = graph.sink;
    while(vertexId != graph.src){
        graph.getEdgeFromVerticesId(vertexId, pred[vertexId]).increaseResidualCapacity(min);
        vertexId = pred[vertexId];
    }
}

int[] distanceLabelling(Graph graph){
    bool marks[graph.nbVertices];
    for(int i = 0; i < graph.nbVertices; ++){
        marks[i] = false;
    }
    marks[graph.sink] = true;
    queue<int> List;
    List.push_back(graph.sink);
    while(List.size() > 0){
        bool hasAdmissibleArc = false;
        for(int i = 0; i < graph.vertices[List.front()].leavingEdgesId.size(); i++){
            if(marks[List.front().leavingEdgesId[j].endId] == false){
                hasAdmissibleArc = true;
                marks[List.front().leavingEdgesId[j].endId] = true;
                dist[List.front().leavingEdgesId[j].endId] = dist[List.front()] + 1;
                List.push_back(List.front().leavingEdgesId[j].endId);
            }
        }
        queue.pop();
    }
    return dist;
}

void shortestAugmentingPath(Graph graph){
    int dist[graph.nbVertices];
    
    bool marks[graph.nbEdges];
    int pred[graph.nbVertices];
    for(int i = 0; i < graph.nbVertices; i++){
        pred[i] = -1;
    }
    for(int i = 0; i < graph.nbEdges; i++){
        marks[i] = false;
    }

    int i = graph.src;
    while(dist[graph.src] < graph.nbVertices){
        bool hasAdmissibleArc = false;
        for(int j = 0; j < graph.vertices[i].leavingEdgesId.size(); j++){
            if(marks[graph.vertices[i].leavingEdgesId[j]] == false){
                hasAdmissibleArc = true;
                pred[graph.vertices[i].leavingEdgesId[j]] = j;  //advance(i) cf. pdf
                i = j;
                if(i == graph.sink){
                    augment(graph, pred);
                    i = graph.src;
                }
            }
        }
        if(hasAdmissibleArc == false){
            retreat(graph, i, dist);
            if(i != graph.src){
                i = pred[i];
            }
        }
    }
}