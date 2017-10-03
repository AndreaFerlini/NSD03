#include <iostream>
#include "loadgraph.h"

int main() {

    string filename = "../../graphs/sample.graph";
    //string filename = "../../graphs/sample_weighted.graph";

    ifstream file(filename);

    bool debug = false;
    bool is_weighted = false;
    //bool is_weighted = true;

    AdjacencyList loadedGraph;

    if (!file.good())
        cout << "No such file... " << endl;

    // Load the Graph as AdjList
    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    loadedGraph.print(debug);

    return 0;
}