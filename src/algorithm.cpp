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

// A special BFS version that returns true if there's a path from source to sink.
bool bfs(Graph *rgraph, int source, int sink, int parent[])
{
    // Create an array for all nodes we visited. Initialized to false.
    int n = rgraph->nbVertices;
    bool visited[n];
    memset(visited, 0, sizeof(visited));

    // Create a queue to check each node.
    std::queue<int> q;

    // Push our source into the queue and mark it as visited. It has no parent.
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    // Keep visiting vertices.
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // Check all of u's friends.
        for (Vertex v : rgraph->vertices)
        {
            for (int e : v.leavingEdgesId)
            {
                // We find a neighbor that hasn't been visited, and the capacity is bigger than 0.
                if (visited[v.id] == false && rgraph->edges[e].maxCapacity > 0)
                {
                    if (v.id == sink)
                    {
                        parent[v.id] = u;
                        return true;
                    }
                    // Push the neighbor onto the queue, mark it's parent, and mark it as visited.
                    q.push(v.id);
                    parent[v.id] = u;
                    visited[v.id] = true;
                }
            }
        }
    }
    return false;
}