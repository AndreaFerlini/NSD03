//
// Created by Andrea Ferlini on 03/10/2017.
//

#include "loadgraph.h"

// Calculate the number of nodes and edges
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool is_weighted, bool debug){
    if (debug) cout << time(nullptr) << "[Graph graph_size] Begin..." << endl;

    fstream graph;
    num_nodes = 0;
    num_edges = 0;

    if(debug) cout << time(nullptr) <<  "[Graph graph_size] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) <<  "[Graph graph_size] Succeed! Counting..." << endl;

        unsigned int node, neighbour, weight;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;
            weight = 0;

            if (is_weighted){
                graph >> node >> neighbour >> weight;
            }else{
                graph >> node >> neighbour;
            }
            if (debug) cout << node << " " << neighbour << " " << weight << endl;

            num_edges++;
            if (node > num_nodes){
                num_nodes = node;
            }
            if (neighbour > num_nodes){
                num_nodes = neighbour;
            }
        }

        if(debug) cout << time(nullptr) << "[Graph graph_size] Done!" << endl;
        graph.close();
    }else{
        cout << "[Graph graph_size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}

// Calculate the degree of each node
// This function build an degree_array in which stores the number of neighbours per node. At index 0 there is the first node (ID=1)
int computeDegree(string filename, GraphDegree &nodesDegree, bool is_weighted, bool debug){
    if (debug) cout << time(nullptr) << "[Graph Degree] Begin..." << endl;

    unsigned int num_edges;
    int node, neighbour, weight;
    fstream graph;

    // Compute the size of the graph
    if (graphSize(filename, nodesDegree.graph_size, nodesDegree.graph_volume, is_weighted, debug))
        return -1;

    nodesDegree.degree_array = new unsigned int[nodesDegree.graph_size]();

    if (debug) cout << time(nullptr) << "[Graph Degree] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Graph Degree] Succeed! Counting neighbours..." << endl;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            if (is_weighted){
                graph >> node >> neighbour >> weight;
            }else{
                graph >> node >> neighbour;
            }

            // Increase the degree of the node
            if (node)
                nodesDegree.degree_array[node-1]++;
            // Increase the degree of the neighbour
            if (neighbour)
                nodesDegree.degree_array[neighbour-1]++;
        }
        /// DEBUG
        if (debug){
            cout << time(nullptr) << "[Graph Degree] Finished! Output:" << endl;
            cout << "  ID\tDegree" << endl;
            cout << "  ---------------------------" << endl;
            nodesDegree.print();
        }
        graph.close();
    }else{
        cout << time(nullptr) << "[Graph Degree] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}

// Loading the adjacency list & store it in memory
int loadAdjListContiguous(string filename, AdjacencyList& adjList, bool is_weighted, bool debug){
    fstream graph;
    unsigned int cursor = 0;

    /// -------- STRUCTURE INIT -----------
    // Compute the degree of the graph, and link it to the structure, updating size and volume
    computeDegree(filename, adjList.adjNodesDegree, is_weighted, debug);

    adjList.num_vertices = adjList.adjNodesDegree.graph_size;
    adjList.num_edges =  adjList.adjNodesDegree.graph_volume;
    adjList.is_weighted = is_weighted;

    // Sum the degree of every node
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        adjList.size_neighbour_list += adjList.adjNodesDegree.degree_array[i];
    }

    // update total number of entry in the neighbours list
    adjList.neighbours_list = new unsigned int[adjList.size_neighbour_list];   // List of neighbours in a compact way

    // Contains the index of the neighbours_list where the list of neighbours (of the i node) starts
    adjList.list_beginning = new unsigned int[adjList.num_vertices]();

    // Contains the list of the weight per edge
    if (is_weighted)
        adjList.weights_list = new unsigned int[adjList.size_neighbour_list]();


    // Initialize list_beginning to point at the beginning of their list
    for (unsigned int node_idx=0; node_idx < adjList.num_vertices; node_idx++){
        adjList.list_beginning[node_idx] = cursor;
        cursor += adjList.adjNodesDegree.degree_array[node_idx];
    }

    if(debug) cout << time(nullptr) <<  "[Compact Adjacency List] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Compact Adjacency List] Succeed! Building Adjacency List..." << endl;

        unsigned int node,
                neighbour,
                weight;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;
            weight = 0;

            if (is_weighted){
                graph >> node >> neighbour >> weight;
            }else{
                graph >> node >> neighbour;
            }

            if(node) {
                adjList.neighbours_list[adjList.list_beginning[node - 1]] = neighbour;

                // Load weight only if it is weighted
                if (is_weighted)
                    adjList.weights_list[adjList.list_beginning[node - 1]] = weight;
                // Increase cursor to write the next neighbour in the correct location
                adjList.list_beginning[node-1]++;

            }

            if(neighbour) {
                adjList.neighbours_list[adjList.list_beginning[neighbour - 1]] = node;

                // Load weight only if it is weighted
                if (is_weighted)
                    adjList.weights_list[adjList.list_beginning[neighbour - 1]] = weight;
                // Increase cursor to write the next neighbour in the correct location
                adjList.list_beginning[neighbour-1]++;
            }
        }

        // Reset beginning position (going backwards of a nr of steps equal to the degree of the node)
        for (unsigned int node_idx=0; node_idx < adjList.num_vertices; node_idx++){
            adjList.list_beginning[node_idx] -= adjList.adjNodesDegree.degree_array[node_idx];
        }
        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug){
            cout << time(nullptr) << "[Compact Adjacency List] print Adj List..." << endl;
            adjList.print(debug);
        }
        graph.close();
    }else{
        cout << "[Compact Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}


