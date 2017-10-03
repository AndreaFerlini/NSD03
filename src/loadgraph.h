//
// Created by Andrea Ferlini on 03/10/2017.
//

#ifndef SRC_LOADGRAPH_H
#define SRC_LOADGRAPH_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <list>

using namespace std;

/// DATA STRUCTURES
struct GraphDegree{
    unsigned int* degree_array; // degree of every node
    unsigned int graph_size;    // number of vertices in the graph
    unsigned int graph_volume;  // number of edges

    /// DEFAULT CONSTRUCTOR
    GraphDegree(){
        degree_array = nullptr;
        graph_size = 0;
        graph_volume = 0;
    }
    /// DESTRUCTOR
    ~GraphDegree(){
        if (degree_array != nullptr){
            delete[] degree_array;
        }
    }

    /// PRINT METHOD
    void print(){
        for (unsigned int i=0; i<graph_size; i++){
            cout << "  " << i+1 << " " << degree_array[i] << endl;
        }
    }

};

struct AdjacencyList{
    unsigned int* neighbours_list;
    unsigned int* weights_list;
    unsigned int* list_beginning;
    unsigned int size_neighbour_list;
    unsigned int num_edges;
    unsigned int num_vertices;
    bool is_weighted;
    GraphDegree adjNodesDegree;

    /// DEFAULT CONSTRUCTOR
    AdjacencyList(){
        neighbours_list = nullptr;
        weights_list = nullptr;
        list_beginning = nullptr;
        size_neighbour_list = 0;
        num_vertices = 0;
        num_edges = 0;
        is_weighted = false;
    }
    /// DESTRUCTOR
    ~AdjacencyList(){
        if (neighbours_list != nullptr){
            delete[] neighbours_list;
        }
        if (list_beginning != nullptr){
            delete[] list_beginning;
        }
        if (weights_list != nullptr){
            delete[] weights_list;
        }
    }

    /// METHODS
    unsigned int getDegree(unsigned int vertex){
        return adjNodesDegree.degree_array[vertex];
    }
    unsigned int getFirstNeighbourId(unsigned int vertex){
        return list_beginning[vertex];
    }
    unsigned int getLastNeighbourId(unsigned int vertex){
        return list_beginning[vertex]+getDegree(vertex);
    }
    unsigned int getNeighbour(unsigned int vertex, unsigned int neighbour_number){
        return neighbours_list[list_beginning[vertex]+neighbour_number];
    }

    /// PRINT METHOD
    void print(bool debug){

        if (debug){
            cout << "[myAdj.print]" << endl;
            cout << "size_neighbour_list: " << size_neighbour_list << endl;
            cout << "num_vertices:        " << num_vertices << endl;
            cout << "num_edges:           " << num_edges << endl;
        }

        cout << "  Node      Neighbours" << endl;
        cout << "  --------------------------------------------------" << endl;
        for (unsigned int v_idx = 0; v_idx < num_vertices; v_idx++) {
            cout << v_idx + 1 << " -> ";
            for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.degree_array[v_idx]; neigh_index++) {
                cout << neighbours_list[list_beginning[v_idx] + neigh_index] << " ";
            }

            if (is_weighted) {
                cout << endl << "W:   ";
                for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.degree_array[v_idx]; neigh_index++) {
                    cout << weights_list[list_beginning[v_idx] + neigh_index] << " ";
                }
            }
            cout << endl ;
        }
        cout << endl ;
    }
};

/// FUNCTIONS
int loadAdjListContiguous(string filename, AdjacencyList& adjList, bool is_weighted, bool debug);
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool is_weighted, bool debug);
int computeDegree(string filename, GraphDegree &nodesDegree, bool is_weighted, bool debug);

#endif //SRC_LOADGRAPH_H
