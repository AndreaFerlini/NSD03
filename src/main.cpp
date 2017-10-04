#include <iostream>
#include "loadgraph.h"
#include "pagerank.h"

int main() {

    string filename = "../../graphs/wiki.txt";
    //string filename = "../../graphs/sample.graph";
    //string filename = "../../graphs/sample_weighted.graph";

    ifstream file(filename);

    bool debug = false;
    bool is_weighted = false;
    //bool is_weighted = true;

    AdjacencyList loadedGraph;

    double alpha = 0.15;
    double *page_rank_array;
    int th = 50;

    double max_rank = 0;
    unsigned int node_max_rank=0;


    if (!file.good())
        cout << "No such file... " << endl;

    // Load the Graph as AdjList
    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    //loadedGraph.print(debug);

    page_rank_array = new double [loadedGraph.num_vertices];

    computePageRank(page_rank_array, loadedGraph, alpha, th);

/*
 * for (unsigned int i=0; i < loadedGraph.num_vertices; i++){
        cout << page_rank_array[i] << " ";
    }
 *
 */

    for (unsigned int i=0; i < loadedGraph.num_vertices; i++){
        if (page_rank_array[i] > max_rank){
            max_rank = page_rank_array[i];
            node_max_rank = i;
        }
    }

    cout << endl;
    cout << "Node with highest rank: " << node_max_rank+1 << endl;
    cout << endl;

    delete[] page_rank_array;
    return 0;
}