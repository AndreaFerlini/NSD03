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
    unsigned int* in_degree_array; // in degree of every node
    unsigned int* out_degree_array; // out degree of every node
    unsigned int graph_size;    // number of vertices in the graph
    unsigned int graph_volume;  // number of edges

    /// DEFAULT CONSTRUCTOR
    GraphDegree(){
        in_degree_array = nullptr;
        out_degree_array = nullptr;
        graph_size = 0;
        graph_volume = 0;
    }
    /// DESTRUCTOR
    ~GraphDegree(){
        if (in_degree_array != nullptr){
            delete[] in_degree_array;
        }
        if (out_degree_array != nullptr){
            delete[] out_degree_array;
        }
    }

    /// PRINT METHOD
    void print(){
        for (unsigned int i=0; i<graph_size; i++){
            cout << "In degree of  " << i+1 << " " << in_degree_array[i] << " ";
            cout << "Out degree of  " << i+1 << " " << out_degree_array[i] << endl;
        }
    }

};

struct AdjacencyList{
    unsigned int* in_neighbours_list;
    unsigned int* out_neighbours_list;
    unsigned int* in_list_beginning;
    unsigned int* out_list_beginning;

    unsigned int* weights_list_in;
    unsigned int* weights_list_out;

    unsigned int size_neighbour_list_in;
    unsigned int size_neighbour_list_out;

    unsigned int num_edges;
    unsigned int num_vertices;
    bool is_weighted;
    GraphDegree adjNodesDegree;

    /// DEFAULT CONSTRUCTOR
    AdjacencyList(){
        in_neighbours_list = nullptr;
        out_neighbours_list = nullptr;
        in_list_beginning = nullptr;
        out_list_beginning = nullptr;

        weights_list_in = nullptr;
        weights_list_out = nullptr;

        size_neighbour_list_in = 0;
        size_neighbour_list_out = 0;

        num_vertices = 0;
        num_edges = 0;
        is_weighted = false;
    }
    /// DESTRUCTOR
    ~AdjacencyList(){
        if (in_neighbours_list != nullptr){
            delete[] in_neighbours_list;
        }
        if (out_neighbours_list != nullptr){
            delete[] out_neighbours_list;
        }
        if (in_list_beginning != nullptr){
            delete[] in_list_beginning;
        }
        if (out_list_beginning != nullptr){
            delete[] out_list_beginning;
        }
        if (weights_list_in != nullptr){
            delete[] weights_list_in;
        }
        if (weights_list_out != nullptr){
            delete[] weights_list_out;
        }
    }

    /// METHODS
    unsigned int getDegreeIn(unsigned int vertex){
        return adjNodesDegree.in_degree_array[vertex];
    }
    unsigned int getDegreeOut(unsigned int vertex){
        return adjNodesDegree.out_degree_array[vertex];
    }
    unsigned int getFirstNeighbourIdIn(unsigned int vertex){
        return in_list_beginning[vertex];
    }
    unsigned int getFirstNeighbourIdOut(unsigned int vertex){
        return out_list_beginning[vertex];
    }
    unsigned int getLastNeighbourIdIn(unsigned int vertex){
        return in_list_beginning[vertex]+getDegreeIn(vertex);
    }
    unsigned int getLastNeighbourIdOut(unsigned int vertex){
        return out_list_beginning[vertex]+getDegreeOut(vertex);
    }
    unsigned int getNeighbourIn(unsigned int vertex, unsigned int neighbour_number){
        return in_neighbours_list[in_list_beginning[vertex]+neighbour_number];
    }
    unsigned int getNeighbourOut(unsigned int vertex, unsigned int neighbour_number){
        return out_neighbours_list[out_list_beginning[vertex]+neighbour_number];
    }

    /// PRINT METHOD
    void print(bool debug){

        if (debug){
            cout << "[myAdj.print]" << endl;
            cout << "size_neighbour_list_in: " << size_neighbour_list_in << endl;
            cout << "size_neighbour_list_out: " << size_neighbour_list_out << endl;
            cout << "num_vertices:        " << num_vertices << endl;
            cout << "num_edges:           " << num_edges << endl;
        }

        cout << "  Node      Neighbours" << endl;
        cout << "  --------------------------------------------------" << endl;
        for (unsigned int v_idx = 0; v_idx < num_vertices; v_idx++) {
            cout << v_idx + 1 << " -> ";
            for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.out_degree_array[v_idx]; neigh_index++) {
                cout << out_neighbours_list[out_list_beginning[v_idx] + neigh_index] << " ";
            }
            if (is_weighted) {
                cout << endl << "W:   ";
                for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.out_degree_array[v_idx]; neigh_index++) {
                    cout << weights_list_out[out_list_beginning[v_idx] + neigh_index] << " ";
                }
            }
            cout << endl ;

            cout << v_idx + 1 << " <- ";
            for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.in_degree_array[v_idx]; neigh_index++) {
                cout << in_neighbours_list[in_list_beginning[v_idx] + neigh_index] << " ";
            }
            cout << endl ;
            if (is_weighted) {
                cout << endl << "W:   ";
                for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.in_degree_array[v_idx]; neigh_index++) {
                    cout << weights_list_in[in_list_beginning[v_idx] + neigh_index] << " ";
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
