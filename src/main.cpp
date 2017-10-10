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
    int th = 20;

    double max_rank = 0;
    unsigned int node_max_rank=0;

    double min_rank = 0;
    unsigned int node_min_rank = 0;

    cout << "STARTED" << endl;

    if (!file.good())
        cout << "No such file... " << endl;

    // Load the Graph as AdjList
    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    if(debug)
        loadedGraph.print(debug);

    page_rank_array = new double [loadedGraph.num_vertices];

    computePageRank(page_rank_array, loadedGraph, alpha, th, debug);

    if (debug){
        for (unsigned int i=0; i < loadedGraph.num_vertices; i++){
            cout << page_rank_array[i] << " ";
        }
    }

    /*for (unsigned int i=0; i < loadedGraph.num_vertices; i++){
        if (page_rank_array[i] > max_rank){
            max_rank = page_rank_array[i];
            node_max_rank = i;
        }
        if (page_rank_array[i] < min_rank){
            if (page_rank_array[i] != 0.0){
                min_rank = page_rank_array[i];
                node_min_rank = i;
            }
        }
    }

    cout << endl << endl;
    cout << "Node with highest rank: " << node_max_rank+1 << endl;
    cout << "Page Rank: " << page_rank_array[node_max_rank] << endl;
    cout << endl;

    cout << "Node with lowest rank: " << node_min_rank+1 << endl;
    cout << "Page Rank: " << page_rank_array[node_min_rank] << endl;
    cout << endl;*/

    delete[] page_rank_array;
    return 0;
}