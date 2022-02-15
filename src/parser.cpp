#include "parser.hpp"
#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const char delimiter = ' ';

namespace mincost
{
    void openFile(std::ifstream &file, std::string filePath)
    {
        file.open(filePath);
        if (file.is_open())
        {
            std::cout << "File opened successfully" << std::endl;
        }
        else
        {
            std::cerr << "File open failed\n"
                      << std::endl;
            exit(-1);
        }
    }

    Graph processFile(std::ifstream &file)
    {
        // data format example:
        // "c 20 msec" comment line, to skip
        // "p min 49 520" problem line where the first number is the number of nodes and the second number is the number of edges
        // "n 47 -769230" nodes line, the first number is the node id, the second number is the node flow
        // "a 1 5 0 769230 1132" edge line, the first number is the source node id, the second number is the destination node id,
        // the third number is the minimum flow capacity, the fourth number is the maximum flow capacity,
        // the fifth number is the cost of the edge

        std::string line;
        int nbNodes, nbEdges;
        int nodeId, nodeFlow;
        int sourceNodeId, destinationNodeId, minFlow, maxFlow, cost;
        std::vector<std::vector<int>> edgesArray;
        std::vector<std::vector<int>> flowsArray;

        // for all the line of the file parse the line and store the data to create the graph
        while (getline(file, line))
        {
            if (file.eof())
            {
                break;
            }
            if (line[0] == 'c')
            {
                // comment line, skip
            }
            else if (line[0] == 'p')
            {
                // problem line, get the number of nodes and the number of edges
                std::stringstream ss(line);
                std::string token;
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
                std::stringstream ss(line);
                std::string token;
                getline(ss, token, delimiter);
                getline(ss, token, delimiter);
                nodeId = stoi(token) - 1; // node id starts at 1
                getline(ss, token, delimiter);
                nodeFlow = stoi(token);
                std::vector<int> flows{nodeId, nodeFlow};
                flowsArray.push_back(flows);
            }
            else if (line[0] == 'a')
            {
                // edge line, get the source node id, the destination node id, the minimum flow capacity, the maximum flow capacity,
                // the cost of the edge
                std::stringstream ss(line);
                std::string token;
                getline(ss, token, delimiter);
                getline(ss, token, delimiter);
                sourceNodeId = stoi(token) - 1; // -1 to fit our data structure
                getline(ss, token, delimiter);
                destinationNodeId = stoi(token) - 1; // -1 to fit our data structure
                getline(ss, token, delimiter);
                minFlow = stoi(token);
                getline(ss, token, delimiter);
                maxFlow = stoi(token);
                getline(ss, token, delimiter);
                cost = stoi(token);

                std::vector<int> edges{cost, minFlow, maxFlow, sourceNodeId, destinationNodeId};
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

        std::cout << "Graph created!\n"
                  << std::endl;

        // set the flows
        for (int i = 0; i < flowsArray.size(); i++)
        {
            graph.vertices[flowsArray[i][0]].exceedingFlow = flowsArray[i][1];
        }

        return graph;
    }

    Graph parse(std::string filePath)
    {
        std::ifstream file;
        openFile(file, filePath);
        Graph graph = processFile(file);
        file.close();
        return graph;
    }
}

namespace maxflow
{
    void openFile(std::ifstream &file, std::string filePath)
    {
        file.open(filePath);
        if (file.is_open())
        {
            std::cout << "File opened successfully" << std::endl;
        }
        else
        {
            std::cerr << "File open failed\n"
                      << std::endl;
            exit(-1);
        }
    }

    Graph processFile(std::ifstream &file)
    {
        // data format example:
        // c Random Network, comment line to skip
        // p max    10      70, problem line, max flow, number of nodes, number of edges
        // n         1  s, node line, node number, node name (s for source)
        // n        10  t, node line, node number, node name (t for sink)
        // a       1       5    6694, edge line, from node, to node, the maximum flow capacity

        std::string line;
        int nbNodes, nbEdges;
        int src, sink;
        int sourceNodeId, destinationNodeId, maxFlow;
        std::vector<std::vector<int>> edgesArray;

        auto isEmptyOrBlank = [](const std::string &s)
        {
            return s.find_first_not_of(" \t") == std::string::npos;
        };

        // for all the line of the file parse the line and store the data to create the graph
        while (getline(file, line))
        {
            if (file.eof())
            {
                break;
            }
            if (line[0] == 'c')
            {
                // comment line, skip
            }
            else if (line[0] == 'p')
            {
                // problem line, get the number of nodes and the number of edges

                // Define the dynamic array variable of strings
                std::vector<std::string> outputArray;
                // Construct a stream from the string
                std::stringstream streamData(line);
                /*
                Declare string variable that will be used
                to store data after split
                */
                std::string val;
                /*
                The loop will iterate the splitted data and
                insert the data into the array
                */
                while (getline(streamData, val, delimiter))
                {
                    outputArray.push_back(val);
                }

                outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());

                nbNodes = stoi(outputArray[2]);
                nbEdges = stoi(outputArray[3]);
            }
            else if (line[0] == 'n')
            {
                if (line[line.length() - 1] == 's')
                {
                    std::vector<std::string> outputArray;
                    std::stringstream streamData(line);
                    std::string val;
                    while (getline(streamData, val, delimiter))
                    {
                        outputArray.push_back(val);
                    }
                    outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());
                    src = stoi(outputArray[1]) - 1; // -1 to fit our data structure
                }
                else if (line[line.length() - 1] == 't')
                {
                    std::vector<std::string> outputArray;
                    std::stringstream streamData(line);
                    std::string val;
                    while (getline(streamData, val, delimiter))
                    {
                        outputArray.push_back(val);
                    }
                    outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());
                    sink = stoi(outputArray[1]) - 1; // -1 to fit our data structure
                }
            }
            else if (line[0] == 'a')
            {
                // edge line, get the source node id, the destination node id, the maximum flow capacity
                std::vector<std::string> outputArray;
                std::stringstream streamData(line);
                std::string val;
                while (getline(streamData, val, delimiter))
                {
                    outputArray.push_back(val);
                }
                outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());

                sourceNodeId = stoi(outputArray[1]) - 1;      // -1 to fit our data structure
                destinationNodeId = stoi(outputArray[2]) - 1; // -1 to fit our data structure
                maxFlow = stoi(outputArray[3]);

                std::vector<int> edges{sourceNodeId, destinationNodeId, maxFlow};
                edgesArray.push_back(edges);
            }
        }

        // convert the vector to an array
        int infos[nbEdges][3];
        for (int i = 0; i < nbEdges; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                infos[i][j] = edgesArray[i][j];
            }
        }

        // create the graph
        Graph graph(nbNodes, nbEdges, src, sink, infos);

        std::cout << "Graph created!\n"
                  << std::endl;

        return graph;
    }

    Graph parse(std::string filePath)
    {
        std::ifstream file;
        openFile(file, filePath);
        Graph graph = processFile(file);
        file.close();
        return graph;
    }
}
