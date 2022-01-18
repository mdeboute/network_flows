#include "Structures.hpp"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void openFile(ifstream&, string);
Graph processFile(ifstream&);

// this function parse an input file and return a network graph
// parameters: filepath
// return value: graph
Graph parse(std::string filePath)
{
    ifstream file;
    openFile(file, filePath);
    Graph graph = processFile(file);
    file.close();
    return graph;
}

void openFile(ifstream& file, string filePath)
{
    file.open(filePath);
    if (file.is_open())
    {
        cout << "File opened successfully" << endl;
    }
    else
    {
        cerr << "File open failed" << endl;
        exit(-1);
    }
}

Graph processFile(ifstream& file)
{
    // data format example:
    // "c 20 msec" comment line, to skip
    // "p min 49 520" problem line where the first number is the number of nodes and the second number is the number of edges
    // "n 47 -769230" nodes line, the first number is the node id, the second number is the node flow
    // "a 1 5 0 769230 1132" edge line, the first number is the source node id, the second number is the destination node id,
    // the third number is the minimum flow capacity, the fourth number is the maximum flow capacity,
    // the fifth number is the cost of the edge

    string line;
    int nbNodes, nbEdges;
    int nodeId, nodeFlow;
    int sourceNodeId, destinationNodeId, minFlow, maxFlow, cost;
    vector<vector<int>> edgesArray;

    // for all the line of the file parse the line and store the data to create the graph
    while (getline(file, line))
    {
        if(file.eof()) break;

        if (line[0] == 'c')
        {
            // comment line, skip
        }
        else if (line[0] == 'p')
        {
            // problem line, get the number of nodes and the number of edges
            stringstream ss(line);
            string token;
            char delimiter = ' ';
            getline(ss, token, delimiter);
            getline(ss, token, delimiter);
            getline(ss, token, delimiter);
            nbNodes = stoi(token);
            getline(ss, token, delimiter);
            nbEdges = stoi(token);
        }
        else if (line[0] == 'n')
        {
            // nodes line, get the node id and the node flow
            stringstream ss(line);
            string token;
            char delimiter = ' ';
            getline(ss, token, delimiter);
            getline(ss, token, delimiter);
            nodeId = stoi(token);
            getline(ss, token, delimiter);
            nodeFlow = stoi(token);
        }
        else if (line[0] == 'a')
        {
            // edge line, get the source node id, the destination node id, the minimum flow capacity, the maximum flow capacity,
            // the cost of the edge
            stringstream ss(line);
            string token;
            char delimiter = ' ';
            getline(ss, token, delimiter);
            getline(ss, token, delimiter);
            sourceNodeId = stoi(token);
            getline(ss, token, delimiter);
            destinationNodeId = stoi(token);
            getline(ss, token, delimiter);
            minFlow = stoi(token);
            getline(ss, token, delimiter);
            maxFlow = stoi(token);
            getline(ss, token, delimiter);
            cost = stoi(token);

            vector<int> edges{cost, minFlow, maxFlow, sourceNodeId, destinationNodeId};
            edgesArray.push_back(edges);
        }
    }

    // convert the vector to an array
    int infos[nbEdges][5];
    for (int i = 0; i < nbEdges; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            infos[i][j] = edgesArray[i][j];
        }
    }

    // create the graph
    Graph graph(nbNodes, nbEdges, infos);
    return graph;
}
